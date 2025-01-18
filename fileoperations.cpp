#include "fileoperations.h"

bool FileOperations::Control(std::string file_path)
{
    bool result = false;
    const char* c_file_path = file_path.c_str();
    FILE* file = fopen(c_file_path, "r");
    if (file) {
        result = true;
        fclose(file);
    } else {
        result = false;
    }

    return result;
}

bool FileOperations::Create(std::string file_path)
{
    std::ofstream file;
    file.open(file_path.c_str());
    file.close();
    bool result = true;

    return result;
}

long long int FileOperations::Size(std::string file_path)
{
    std::ifstream f_ptr(file_path, std::ios::binary);
    f_ptr.seekg(0, std::ios::end);
    long long int file_size = f_ptr.tellg();

    return file_size;
}

void FileOperations::Rename(std::string file_name_old, std::string file_name)
{
    rename(file_name_old.c_str(), file_name.c_str());
}

void FileOperations::Remove(std::string file_path)
{
    remove(file_path.c_str());
}

void FileOperations::WriteWithDateInfo(std::string file_path, std::string text)
{
    std::string dt = utility.DateTimeNow();
    std::string line = dt + " " + text;
    Write(file_path, line);
}

void FileOperations::Write(std::string file_path, std::string text)
{
    std::ofstream f_ptr;
    f_ptr.open(file_path, std::ofstream::out | std::ofstream::app);
    if (f_ptr.is_open())
        f_ptr << text << std::endl;
    f_ptr.close();
}

std::vector<std::string> FileOperations::Read(std::string file_path)
{
    std::vector<std::string> lines;
    std::ifstream f_ptr;
    std::string tmp;

    f_ptr.open(file_path);
    if (!f_ptr.is_open()) {
        lines.clear();
    } else {
        while (getline(f_ptr, tmp))
            lines.push_back(tmp);
    }
    f_ptr.close();

    return lines;
}
