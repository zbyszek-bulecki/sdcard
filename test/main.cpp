#include "Arduino.h"

#include "FS.h"
#include "SD.h"
#include "FileOperations.h"
#include "ArduinoJson-v6.19.4.h"
#include "WiFi.h"
#include <iostream>
#include <fstream>
#include <string>

// const char *SSID = "Pancernik";
// const char *PASSWORD = "KawkaKawusia@2k21";

void setup()
{
    Serial.begin(115200);

    // WiFi.begin(SSID, PASSWORD);
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     delay(500);
    //     Serial.println("Connecting to WiFi..");
    // }
    // Serial.println("");
    // Serial.println("WiFi connected");
    // Serial.println("IP address: ");
    // Serial.println(WiFi.localIP());

    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

    // -== EXAMPLE USES ==-
    // listDir(SD, "/", 0);
    // createDir(SD, "/mydir");
    // listDir(SD, "/", 0);
    // removeDir(SD, "/mydir");
    // listDir(SD, "/", 2);
    // writeFile(SD, "/hello.txt", "Hello ");
    // appendFile(SD, "/hello.txt", "World!\n");
    // readFile(SD, "/hello.txt");
    // deleteFile(SD, "/foo.txt");
    // renameFile(SD, "/hello.txt", "/foo.txt");
    // readFile(SD, "/foo.txt");
    // testFileIO(SD, "/test.txt");
    // Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    // Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));

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


        if (!SD.exists("/config/wifi.txt"))
    {
        char wifiConfig[] = "ssid=password";
        createDir(SD, "/config");
        writeFile(SD, "/config/wifi.txt", wifiConfig);
        Serial.println("WiFi config data created.");
    }
    else
    {
        std::ifstream myfile("config/wifi/txt");
        std::string myString;
        if(myfile.is_open()){
            myfile >> myString;
            Serial.println(myString.c_str());

        }
    }
}

void loop()
{
}