#include <argparse/argparse.hpp>
#include <iostream>

#include "commands/commands.hpp"
#include "fs.hpp"

int main(const int argc, char *argv[]) {
    argparse::ArgumentParser program("dt");

    argparse::ArgumentParser init_command("init");
    init_command.add_description("Initialize the dt database");

    argparse::ArgumentParser add_command("add");
    add_command.add_argument("directory");
    add_command.add_description("Add a directory to the database");

    program.add_subparser(init_command);
    program.add_subparser(add_command);

    try {
        program.parse_args(argc, argv);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << program;
        return EXIT_FAILURE;
    }

    if (program.is_subcommand_used("init")) {
        return Commands::Init();
    } else if (program.is_subcommand_used("add")) {
        std::cout << program.at<argparse::ArgumentParser>("add").get("directory") << std::endl;
    }

    LockFile lockfile("../lockfile.json");

    // lockfile.push_directory("../buildDir");

    // lockfile.save();

    Directory directory(lockfile.directories[0].append("directory.json"));

    return EXIT_SUCCESS;
}
