#include "Arduino.h"

#include "FS.h"
#include "SD.h"
#include "ArduinoJson-v6.19.4.h"
#include "WiFi.h"
#include "FileOperations.h"
#include <iostream>
#include <fstream>
#include <string>

const char *WIFI_CONFIG_PATH = "/config/wifi.txt";

void setup()
{
    Serial.begin(115200);
    std::string ssid;
    std::string wifiPassword;

    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

    // DynamicJsonDocument doc(1024);

    // doc["sensor"] = "gps";
    // doc["time"] = 1351824120;
    // doc["data"][0] = 48.756080;
    // doc["data"][1] = 2.302038;

    // String data;
    // serializeJson(doc, data);

    // if (SD.exists("/logs/sensorData.txt"))
    // {
    //     appendFile(SD, "/logs/sensorData.txt", data.c_str());
    // }
    // else
    // {
    //     createDir(SD, "/logs");
    //     writeFile(SD, "/logs/sensorData.txt", data.c_str());
    //     Serial.println("Logs folder created.");
    // }

    // readFile(SD, "/logs/sensorData.txt");

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
        if (myfile)
        {
            while (myfile.available())
            {
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
        wifiPassword.append(p + 1);
        Serial.println(wifiPassword.c_str());

        int b;
        b = (wifiConfig.length() - wifiPassword.length() - 1);
        for (int i = 0; i < b; i++)
        {
            ssid += wifiConfig[i];
        }
        Serial.println(ssid.c_str());
    }
    
    WiFi.begin(ssid.c_str(), wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
}