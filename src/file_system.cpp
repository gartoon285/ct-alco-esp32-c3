#include <file_system.h>
void FileSystem::init()
{
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    if (!EEPROM.begin(64))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
    byte chek1 = EEPROM.readByte(10);
    byte chek2 = EEPROM.readByte(12);
    if(chek1 != 55 && chek2 != 38){
        EEPROM.writeByte(10,55);
        EEPROM.writeByte(12,38);
        EEPROM.writeByte(0,0);
        EEPROM.commit();
    }
    esp_read_mac(baseMac, ESP_MAC_BT);
    hwid = String(baseMac[0], HEX) + " " + String(baseMac[1], HEX) + " " + String(baseMac[2], HEX) + " " + String(baseMac[3], HEX) + " " + String(baseMac[4], HEX) + " " + String(baseMac[5], HEX);
}

void FileSystem::Print(String time,String ledcode)
{
    String s;
    byte index = EEPROM.readInt(0) + 1;
    byte numLog = EEPROM.readInt(5)+1;
    doc["hwid"] = hwid;
    doc["time"] = time;
    doc["alco"] = sensor.sgp30getEthanol();
    doc["Co2"] = sensor.sgp30getCo2();
    doc["ledcode"] = ledcode;
    serializeJson(doc, s);
    String filename = "/"+String(index)+".txt";
    file = SPIFFS.open(filename, FILE_WRITE); // เปิดไฟล์ในโหมด Write
  if (!file) {
    Serial.println("There was an error opening the file for appending");
    return;
  }
  // แทรกข้อความใหม่ลงไปในไฟล์
  file.println(s);
  file.close();
  if(index>=100){
    index =0;
  }
  if(numLog>=100){
    numLog=100;
  }
  Serial.println(index);
  EEPROM.writeByte(0,index);
  EEPROM.writeByte(5,numLog);
  EEPROM.commit();
}
std::array<String, 100> FileSystem::Read()
{
    byte index = EEPROM.readInt(0);
    int count = 0;
    std::array<String, 100> messages;
        for (int k = index ; k <= 100; k++)
        {
            String s = "/"+String(k)+".txt";
            messages[count]=readFile(s);
            count++;
        }
        for (int j = 1; j <= index; j++)
        {
            String s = "/"+String(j)+".txt";
            messages[count]=readFile(s);
            count++;
        }
    return messages;
}
String FileSystem::readFile(String name){
 file = SPIFFS.open(name, FILE_READ);
String s;
  if (!file) {
    Serial.println("There was an error opening the file for reading");
    return s;
  }

  while (file.available()) {
    s=file.readString();
  }
  file.close();
 return s;
}