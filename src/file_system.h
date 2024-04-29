#ifndef file_system_h
#define file_system_h
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <FS.h>
    class FileSystem
{
public:
  void init(String filename);
  void Print(String filename,String time, float alco, float pressure, int8_t ledcode,float battV, float battSoc,bool battCharge);
  std::array<String, 100> Read(String filename);
  std::array<String, 100> readJson(String filename);
private:
  File file;
  uint8_t baseMac[6];
};
#endif