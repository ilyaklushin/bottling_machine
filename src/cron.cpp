#include "cron.hpp"

void fetch_cron(int previous_id=-1, bool previous_status=false){
    std::cout << "fetch_cron()" << std::endl;
    std::string action = "cron";
    std::string data = "";
    std::string dda;
    if (previous_id!=-1){
        if (previous_status){
            dda = "id="+std::to_string(machine_id)+"&pass="+auth_key+"&action="+action+"&previous_id="+std::to_string(previous_id)+"&previous_status=true";
        } else {
            dda = "id="+std::to_string(machine_id)+"&pass="+auth_key+"&action="+action+"&previous_id="+std::to_string(previous_id)+"&previous_status=false";
        }
    } else {
        dda = "id="+std::to_string(machine_id)+"&pass="+auth_key+"&action="+action;
    }
    std::string curlbuff = db_send_post(dda, api_address);
    json jrarr;
    try {
        jrarr = json::parse(curlbuff);
        std::cout << jrarr << std::endl;
    } catch(json::parse_error){
        std::cout << "HTTPS err:" << curlbuff << std::endl;
    }
    if (jrarr["auth"]==true){
        renew_cron=jrarr["renew"];
        if (jrarr["status"]==true){
            if(jrarr["cron"]["action"]=="config"){
                WaterCost = jrarr["cron"]["vars"]["water_cost"];
                PulsePerLiter = jrarr["cron"]["vars"]["pulse_per_liter"];
                machine_id = jrarr["cron"]["vars"]["machine_id"];
                auth_key = jrarr["cron"]["vars"]["auth_key"];
                api_address = jrarr["cron"]["vars"]["api_address"];
                db_name = jrarr["cron"]["vars"]["db_name"];
                if (write_config()==1){
                    fetch_cron(jrarr["cron"]["id"], true);
                } else {
                    fetch_cron(jrarr["cron"]["id"], false);
                }
            } else if (jrarr["cron"]["action"]=="set_run_mode"){
                if (jrarr["cron"]["vars"]["mode"]=="maintenance"){maintenanceMode=true;}
                else {maintenanceMode=false;}
                if (jrarr["cron"]["vars"]["mode"]=="remote_control"){remote_controlMode=true;}
                else {remote_controlMode=false;}
                if (jrarr["cron"]["vars"]["run_mode"]=="normal"){
                    db_send_delay=30;
                    fetch_cron(jrarr["cron"]["id"], true);
                }
                if (jrarr["cron"]["vars"]["run_mode"]=="remote_control"){
                    db_send_delay=1;
                    fetch_cron(jrarr["cron"]["id"], true);
                }
                if (jrarr["cron"]["vars"]["run_mode"]=="maintenance"){
                    db_send_delay=1;
                    fetch_cron(jrarr["cron"]["id"], true);
                }
            } else if (jrarr["cron"]["action"]=="unlock_door"){
                openSolenoidLock();
                fetch_cron(jrarr["cron"]["id"], true);
            } else if (jrarr["cron"]["action"]=="reboot"){
                fetch_cron(jrarr["cron"]["id"], true);
                sync();
                setuid(0);
                reboot(RB_AUTOBOOT);
            } else if (jrarr["cron"]["action"]=="set_litters"){
                addCoins((float(jrarr["cron"]["vars"]["quantity"])*WaterCost));
                fetch_cron(jrarr["cron"]["id"], true);

            }
        }
    }
    else{
        renew_cron=false;
    }
}


