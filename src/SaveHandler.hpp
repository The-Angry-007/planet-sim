#pragma once
namespace SaveHandler
{
void CreateSave(std::string name);
bool SaveExists(std::string name);
bool dirExists(std::string& path);
extern std::string workingDir;
bool createDir(std::string& path);
void UpdateModified();
void UpdateTimePlayed(int seconds);
int64_t getSeconds();
std::vector<std::string> getLines(std::string path);
void WriteLines(std::vector<std::string> lines, std::string path);
}