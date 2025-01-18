#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>
#include "utility.h"

class FileOperations
{
public:
    bool Control(std::string file_path);
    bool Create(std::string file_path);
    long long int Size(std::string file_path);
    void Rename(std::string file_name_old, std::string file_name);
    void Remove(std::string file_path);
    void WriteWithDateInfo(std::string file_path, std::string text);
    void Write(std::string file_path, std::string text);
    std::vector<std::string> Read(std::string file_path);

private:
    Utility utility;
};

#endif // FILEOPERATIONS_H
