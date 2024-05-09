#ifndef file_system_h
#define file_system_h
#include "EEPROM.h"
#include <ArduinoJson.h>
#include "FS.h"
#include "SPIFFS.h"

 class FileSystem{
public:
  void init();
  void Print(String time, float alco, float pressure, String ledcode);
  std::array<String, 100> Read();
private:
  StaticJsonDocument<192> doc;
  uint8_t baseMac[6];
  String hwid;
  File file;
  String readFile(String name);
};
#endif