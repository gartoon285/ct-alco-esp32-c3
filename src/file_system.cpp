#include <file_system.h>
void FileSystem::init(String filename)
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  file = SPIFFS.open(filename, FILE_READ); // อ่านไฟล์
  bool file_exist = file.available();      // ตัวแปร boolean เก็บค่า true false ถ้ามีไฟล์และมีข้อมูลจะเป็น True
  file.close();
  if (file_exist == false)
  { // เช็คถ้าไม่มีไฟล์ให้สร้างไฟล์ใหม่
    file = SPIFFS.open(filename, FILE_WRITE);
    if (!file)
    {
      Serial.println("There was an error opening the file for writing");
      return;
    }
    file.close();
  }
}

void FileSystem::Print(String filename, String message)
{
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
    for (int i = 0; i < 100; i++)
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