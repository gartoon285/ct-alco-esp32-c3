#include <file_system.h>
void FileSystem::init(String filename)
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }
    if (SPIFFS.exists(filename) == false)
    { // เช็คถ้าไม่มีไฟล์ให้สร้างไฟล์ใหม่
        file = SPIFFS.open(filename, FILE_WRITE);
        if (!file)
        {
            Serial.println("There was an error opening the file for writing");
            return;
        }
        file.close();
    }
    esp_read_mac(baseMac, ESP_MAC_BT);
}

void FileSystem::Print(String filename, String time, float alco, float pressure, int8_t ledcode, float battV, float battSoc, bool battCharge)
{
    String message = time + "," + String(alco) + "," + String(pressure) + "," + String(ledcode) + "," + String(battV) + "," + String(battSoc) + "," + String(battCharge);
    file = SPIFFS.open(filename, FILE_APPEND);
    if (!file)
    {
        Serial.println("There was an error opening the file for writing");
        return;
    }
    file.println(message);
    file.close();

    file = SPIFFS.open(filename, FILE_READ);
    int count = 0;
    String s[101];
    while (file.available())
    {
        s[count] = file.readStringUntil('\n');
        count++;
    }
    file.close();

    if (count > 100)
    {
        file = SPIFFS.open(filename, FILE_WRITE);
        if (!file)
        {
            Serial.println("Failed to open file for writing");
            return;
        }
        for (int i = 1; i < 101; i++)
        {
            file.println(s[i]);
        }
        file.close();
    }
}
std::array<String, 100> FileSystem::Read(String filename)
{
    file = SPIFFS.open(filename, FILE_READ);
    std::array<String, 100> messages;
    if (!file)
    {
        Serial.println("There was an error opening the file for reading");
        return messages;
    }

    // อ่านและแสดงข้อมูลจากไฟล์
    int count = 0;
    Serial.println("Contents of data.txt:");
    while (file.available() && count < 100)
    {
        messages[count] = file.readStringUntil('\n');
        count++;
    }
    file.close();
    return messages;
}
std::array<String, 100> FileSystem::readJson(String filename)
{
    std::array<String, 100> messages;
    int count = 0;
    int id = 1;
    // String time,alco,pressure,ledcode,battV,battSoc,battCharge;
    file = SPIFFS.open(filename, FILE_READ);
    String s[101];
    while (file.available())
    {
        file.readStringUntil('\n');
        count += 1;
    }
    file.close();
    file = SPIFFS.open(filename, FILE_READ);
    if (!file)
    {
        Serial.println("There was an error opening the file for reading");
        return messages;
    }
    while (file.available() && count > 0)
    {
        String data = file.readStringUntil('\n');
        int index = 0;
        String dataArray[7]; // สร้างอาร์เรย์เพื่อเก็บข้อมูลที่แยกแล้ว time,alco,pressure,ledcode,battV,battSoc,battCharge
        while (data.length() > 0)
        {
            int commaIndex = data.indexOf(','); // หาตำแหน่งของคอมมา (,)
            if (commaIndex == -1)
            {                              // ถ้าไม่พบคอมมา (,) ในสตริงอีกแล้ว
                dataArray[index++] = data; // เก็บข้อมูลที่เหลือลงในอาร์เรย์
                break;                     // ออกจากลูป
            }
            dataArray[index++] = data.substring(0, commaIndex); // แยกข้อมูลและเก็บในอาร์เรย์
            data = data.substring(commaIndex + 1);              // ตัดข้อมูลที่แยกแล้วออกจากสตริง
        }
        String hwid = String(baseMac[0])+" "+String(baseMac[1])+" "+String(baseMac[2])+" "+String(baseMac[3])+" "+String(baseMac[4])+" "+String(baseMac[5]);
        messages[id - 1] = "{\"ID\":\"" + String(id) + "\",\"hwid\":\"" + hwid +"\",\"time\":\"" + dataArray[0] + "\",\"alco\":" + dataArray[1] + ",\"pressure\":" + dataArray[2] + ",\"ledcode\":\"" + dataArray[3] + "\",\"batt\":[" + dataArray[4] + "," + dataArray[5] + "," + dataArray[6] + "]}";
        count -= 1;
        id++;
    }
    file.close();
    return messages;
}