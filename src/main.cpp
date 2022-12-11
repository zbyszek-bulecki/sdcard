#include "Arduino.h"

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "FileOperations.h"
#include "ArduinoJson-v6.19.4.h"


void setup(){
    Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

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

    DynamicJsonDocument doc(1024);

    doc["sensor"] = "gps";
    doc["time"]   = 1351824120;
    doc["data"][0] = 48.756080;
    doc["data"][1] = 2.302038;
    
    String data;
    serializeJson(doc, data);

    writeFile(SD, "/sensorData.txt", data.c_str());

    readFile(SD, "/sensorData.txt");
}

void loop(){

}