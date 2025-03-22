#include "lockfile.hpp"

#include <fstream>

std::string readFileToString(const std::filesystem::path &filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open lockfile");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

Directory::Directory(const std::filesystem::path &path) {
    std::string raw = readFileToString(path);

    _j = json::parse(raw);
    _path = path;

    for (const auto &version : _j["versions"]) {
        versions.emplace_back(Version{
            .name = version["name"],
            .timestamp = version["timestamp"].get<std::time_t>(),
            .path = version["path"]});
    }

    active = _j["active"].get<uint>();
}

LockFile::LockFile(const std::filesystem::path &path) {
    std::string raw = readFileToString(path);

    _j = json::parse(raw);
    _path = path;

    directories = _j["directories"].get<std::vector<std::filesystem::path>>();
}

void LockFile::push_directory(const std::filesystem::path &path) {
    directories.emplace_back(std::filesystem::absolute(path).string());
}

void LockFile::save() {
    _j["directories"] = directories;

    std::ofstream file(_path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open lockfile");
    }
    file << _j;
    file.close();
}
