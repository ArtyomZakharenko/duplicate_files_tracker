#include <iostream>
#include "../include/duplicates_handler.h"

void print_usage();

int main(int argc, char* argv[]) {
    bool recursive = false;
    std::string directory;

    if (argc >= 2) {
        std::string arg = argv[1];
        if (arg == "-r" || arg == "--recursive") {
            // Если передан флаг -r или --recursive
            recursive = true;
            if (argc >= 3) {
                // Если задан дополнительный аргумент, установить значение каталога
                directory = argv[2];
            }
            else {
                // Если дополнительного аргумента нет, вывести информацию о использовании
                print_usage();
                return 0;
            }
        }
        else if (arg == "-h" || arg == "--help") {
            // Если передан флаг -h или --help
            print_usage();
            return 0;
        }
        else {
            // В противном случае, установить значение каталога из первого аргумента
            directory = argv[1];
        }
    }
    else {
        // Если нет аргументов, вывести информацию о использовании
        print_usage();
        return 0;
    }

    DuplicatesHandler duplicates_handler;
    duplicates_handler.run(directory, recursive);
    return 0;
}

void print_usage() {
    std::cout << "Использование: ./dft [-r] <directory>" << std::endl;
    std::cout << "Опции:" << std::endl;
    std::cout << "  -r, --recursive  рекурсивный режим" << std::endl;
    std::cout << "  -h, --help       вывести информацию о использовании" << std::endl;
}
