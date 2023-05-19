#include "duplicates_handler.h"

void print_usage();

int main(int argc, char* argv[]) {
    bool recursive = false;
    std::string directory;

    if (argc == 3 && std::string(argv[1]) == "-r") {
        recursive = true;
        directory = argv[2];
    } else if (argc == 2) {
        directory = argv[1];
    } else {
        print_usage();
        return 0;
    }

    DuplicatesHandler file_handler;
    file_handler.run(directory, recursive);
    return 0;
}

void print_usage() {
    std::cout << "Usage: ./Duplicate_File_Tracker [-r] <directory>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-r\t\tRecursive mode. Search for duplicates in all subdirectories of the given directory." << std::endl;
}