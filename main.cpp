#include "duplicates_handler.h"

int main(int argc, char* argv[]) {
    bool recursive = false;
    std::string directory;

    if (argc == 3 && std::string(argv[1]) == "-r") {
        recursive = true;
        directory = argv[2];
    } else if (argc == 2) {
        directory = argv[1];
    } else {
        DuplicatesHandler::print_usage();
        return 0;
    }

    DuplicatesHandler file_handler;
    file_handler.run(directory, recursive);
    return 0;
}