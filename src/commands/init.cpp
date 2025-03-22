#include "commands.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

int Commands::Init() {
    std::filesystem::path path = getenv("HOME");
    path.append(".dt");

    if (std::filesystem::is_directory(path)) {
        std::cerr << path << " already exists" << std::endl;
        return EXIT_FAILURE;
    }

    std::filesystem::create_directory(path);
    return EXIT_SUCCESS;
}