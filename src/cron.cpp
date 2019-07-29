#include "cron.hpp"

void fetch_cron(){
    std::string action = "cron";
    std::string data = "";
    std::cout << action << data << std::endl;
    std::string dda = "id="+std::to_string(machine_id)+"&pass="+auth_key+"&action="+action+"&data="+data;
    std::string curlbuff = db_send_post(dda, api_address);
    json jrarr;
    try {
        jrarr = json::parse(curlbuff);
        std::cout << jrarr << std::endl;
    } catch(json::parse_error){
        std::cout << "HTTPS err:" << curlbuff << std::endl;
    }
    if (jrarr["auth"]==true){
        if (jrarr["status"]==true){
            if(jrarr["cron"]["action"]=="config"){
                WaterCost = jrarr["cron"]["vars"]["water_cost"];
                PulsePerLiter = jrarr["cron"]["vars"]["pulse_per_liter"];
                machine_id = jrarr["cron"]["vars"]["machine_id"];
                auth_key = jrarr["cron"]["vars"]["auth_key"];
                api_address = jrarr["cron"]["vars"]["api_address"];
                db_name = jrarr["cron"]["vars"]["db_name"];
                write_config();
            } else if (jrarr["cron"]["action"]=="set_run_mode"){

            } else if (jrarr["cron"]["action"]=="unlock_door"){

            } else if (jrarr["cron"]["action"]=="reboot"){

            } else if (jrarr["cron"]["action"]=="set_liters"){
                addCoins((float(jrarr["cron"]["vars"]["quantity"])*WaterCost));

            }

        }
    }


}
