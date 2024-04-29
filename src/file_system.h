#ifndef file_system_h
#define file_system_h
#include <SPIFFS.h>
#include <FS.h>
    class FileSystem
{
public:
  void init(String filename);
  void Print(String filename, String message);
  std::array<String, 100> Read(String filename);

private:
  File file;
};
#endif