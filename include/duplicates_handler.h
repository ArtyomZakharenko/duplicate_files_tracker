#ifndef DUPLICATE_FILE_TRACKER_FILE_HANDLER_H
#define DUPLICATE_FILE_TRACKER_FILE_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "logger.h"

class DuplicatesHandler { // класс для обработки дубликатов
private:
    std::unordered_map<std::string, std::vector<std::string>> files_by_hash; // файлы по хешу
    Logger logger; // логгер

public:
    void run(const std::string& directory, bool recursive); // запустить поиск дубликатов

private:
    void find_files(const std::string& folder, bool recursive_mode); // найти файлы
    void sort_by_creation_time(); // отсортировать по времени создания
    void find_duplicates(); // найти дубликаты
    void replace_duplicates(); // заменить дубликаты

    void remove_duplicate(const std::string &path); // удалить дубликат
    void create_hard_link(const std::string &path_from, const std::string &path_to); // создать жесткую ссылку
};

#endif //DUPLICATE_FILE_TRACKER_FILE_HANDLER_H
