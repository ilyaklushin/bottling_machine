#include "db.hpp"

bool db_query(char *db_name, std::string db_execstr, int (*callback)(void*,int,char**,char**), void *data){
    if (busydb==true){
        for(;;){
            delay(10);
            if (busydb==false){
                break;
            }
        }
    }
    busydb=true;
    sqlite3 *db;
    char *zErrMsg = 0;
    int db_conn_stat;
    /* Open database */
    db_conn_stat = sqlite3_open(db_name, &db);

    if( db_conn_stat ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    }
    else{
        fprintf(stdout, "Opened database successfully\n");
        std::cout<< "Query: " << db_execstr << std::endl;
    }

    /* Execute SQL statement */
    db_conn_stat = sqlite3_exec(db, db_execstr.c_str(), *callback, data, &zErrMsg);

    if( db_conn_stat != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else{
        std::cout<< "Query exec successfully" << std::endl;
    }
    sqlite3_close(db);
    busydb=false;
    if( db_conn_stat != SQLITE_OK ){
        return false;
    }
    else{
        return true;
    }
}

void db_add_bottling(float volume, int coins, unsigned int duration, unsigned int timestamp){
    json jarr;
    jarr["volume"] = volume;
    jarr["coins"] =  coins;
    jarr["duration"] = duration;
    jarr["time"] = timestamp;

    std::string db_execstr;
    db_execstr = "INSERT INTO HISTORY (action,data) VALUES ('bottling', '"+ jarr.dump() +"');";
    db_query("test.db", db_execstr, NULL, 0);
}

void db_add_filtration(bool minS, bool midS, bool maxS){
    json jarr;
    jarr["min"]=minS;
    jarr["mid"]=midS;
    jarr["max"]=maxS;
    jarr["time"]=std::time(nullptr);

    std::string db_execstr;
    db_execstr = "INSERT INTO HISTORY (action, data) VALUES ('tank', '"+ jarr.dump() +"');";
    db_query("test.db", db_execstr, NULL, 0);
}

size_t db_send_post_writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string db_send_post(std::string &strr, auto server){
    //char strr[]="name=daniel&project=curl";
    std::string readBuffer;
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, server);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, db_send_post_writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strr.c_str());

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);


#ifdef SKIP_HOSTNAME_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return readBuffer;
}

static int callback_fetchrow(void *xdata, int argc, char **argv, char **azColName){
    std::string action = argv[1];
    std::string data = argv[2];
    std::cout << action << data << std::endl;
    std::string dda = "action="+action+"&data="+data;
    std::string *ptr_xdata = (std::string *)xdata;
    *ptr_xdata=db_send_post(dda, "https://water.ufmc.xyz/test.php");
    return 0;
}

static int callback_lexists(void *data, int argc, char **argv, char **azColName){
    if (*argv[0]=='1'){
        std::cout << "exists" << std::endl;
        bool *ptr_data= (bool *)data;
        *ptr_data=true;
    }
    else{
        bool *ptr_data= (bool *)data;
        *ptr_data=false;
        std::cout << "don'n exists" << std::endl;
    }
    return 0;
}
void db_send(){
    bool lexists = false;
    for(;;){
        db_query("test.db", std::string("SELECT EXISTS (SELECT * FROM HISTORY LIMIT 1)"), callback_lexists, &lexists);
        if (lexists){
            std::cout << "lex:" << lexists << std::endl;
            std::string curlbuff;
            for (;;){
                db_query("test.db", std::string("SELECT * FROM HISTORY LIMIT 1"), callback_fetchrow, &curlbuff);
                std::cout << curlbuff << std::endl;
                if (curlbuff==std::string("ok")){
                    std::cout << "HTTPS ok" << std::endl;
                    db_query("test.db", std::string("DELETE FROM HISTORY LIMIT 1"), NULL, 0);
                    break;
                }
                else {
                    std::cout << "HTTPS err:" << curlbuff << std::endl;
                    sleep(5);
                }
            }
            std::cout << "Hello world!" << std::endl;
        }
        else{
            break;
        }
    }
    //    std::cout << stat << std::endl;
}
