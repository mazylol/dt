#ifndef LOCKFILE_HPP
#define LOCKFILE_HPP
#include <ctime>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

std::string readFileToString(const std::filesystem::path &filePath);

struct Version {
    std::string name;
    std::time_t timestamp;
    std::filesystem::path path;
};

struct Directory {
    std::vector<Version> versions;
    uint active;

    std::filesystem::path _path;
    json _j;

    explicit Directory(const std::filesystem::path &path);
};

struct LockFile {
    std::vector<std::filesystem::path> directories;

    std::filesystem::path _path;
    json _j;

    explicit LockFile(const std::filesystem::path &path);
    void push_directory(const std::filesystem::path &path);
    void save();
};

#endif // LOCKFILE_HPP
