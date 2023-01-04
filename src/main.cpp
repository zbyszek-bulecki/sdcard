#include "Arduino.h"

#include "FS.h"
#include "SD.h"
#include "FileOperations.h"
#include <iostream>
#include <fstream>
#include <string>

const char *WIFI_CONFIG_PATH = "/config/wifi.txt";

void setup()
{
    Serial.begin(115200);

    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

        if (!SD.exists(WIFI_CONFIG_PATH))
    {
        char wifiConfig[] = "ssid=password";
        createDir(SD, "/config");
        writeFile(SD, WIFI_CONFIG_PATH, wifiConfig);
        Serial.println("Blank WiFi config data created.");
    }
    else
    {
        File myfile = SD.open(WIFI_CONFIG_PATH);
        std::string wifiConfig;
        if(myfile){
            while(myfile.available()){
               wifiConfig += (myfile.read());
            }
            myfile.close();
        }
        else
        {
            Serial.println("Error opening WiFi config file.");
        }
        Serial.println(wifiConfig.c_str());
        char *p;
        p = strchr(wifiConfig.c_str(), '=');
        std::string wifiPassword;
        wifiPassword.append(p+1);
        Serial.println(wifiPassword.c_str());

        int b;
        std::string ssid;
        b = (wifiConfig.length() - wifiPassword.length() - 1);
        for(int i = 0; i < b; i++){
            ssid += wifiConfig[i];
        }

        Serial.println(ssid.c_str());
    }
}

void loop()
{

}