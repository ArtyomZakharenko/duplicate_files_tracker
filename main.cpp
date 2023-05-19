#include <iostream>
#include "duplicates_handler.h"

void print_usage(); // Вывести информацию о том, как пользоваться программой

int main(int argc,
         char *argv[]) { // argc - количество аргументов командной строки, argv - массив строк, содержащий аргументы командной строки
    bool recursive = false; // Рекурсивный режим
    std::string directory; // Директория, в которой нужно искать дубликаты

    if (argc == 3 && std::string(argv[1]) == "-r") { // Если передано 3 аргумента и первый аргумент -r
        recursive = true; // Включаем рекурсивный режим
        directory = argv[2]; // Второй аргумент - директория, в которой нужно искать дубликаты
    } else if (argc == 2) { // Если передано 2 аргумента
        directory = argv[1]; // Первый аргумент - директория, в которой нужно искать дубликаты
    } else { // Если передано неверное количество аргументов
        print_usage(); // Выводим информацию о том, как пользоваться программой
        return 0; // Завершаем программу
    }

    DuplicatesHandler duplicates_handler; // Создаем объект класса DuplicatesHandler
    file_handler.run(directory, recursive); // Запускаем поиск дубликатов
    return 0; // Завершаем программу
}

void print_usage() { // Вывести информацию о том, как пользоваться программой
    std::cout << "Usage: ./Duplicate_File_Tracker [-r] <directory>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-r\t\tRecursive mode. Search for duplicates in all subdirectories of the given directory."
              << std::endl;
}