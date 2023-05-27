#include "../include/duplicates_handler.h"
#include "../include/hash_generator.h"

#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <algorithm>

void DuplicatesHandler::run(const std::string &directory, bool recursive) { // реализация метода run
    find_files(directory, recursive); // найти файлы
    sort_by_creation_time(); // отсортировать по времени создания
    find_duplicates(); // найти дубликаты
    replace_duplicates(); // заменить дубликаты
}

void DuplicatesHandler::find_files(const std::string &folder, bool recursive_mode) { // реализация метода find_files
    DIR *dir = opendir(folder.c_str()); // открыть папку
    if (!dir) { // если не удалось открыть папку
        std::cerr << "Error opening folder: " << folder << std::endl; // вывести сообщение об ошибке
        return; // завершить метод
    }

    dirent *entry; // запись в папку
    while ((entry = readdir(dir)) != nullptr) { // пока есть записи в папке
        if (entry->d_type == DT_DIR) { // если запись - папка
            if (recursive_mode && strcmp(entry->d_name, ".") != 0 &&
                strcmp(entry->d_name, "..") != 0) { // если рекурсивный режим и запись не является . или ..
                std::string sub_directory = folder + "/" + entry->d_name; // подпапка
                find_files(sub_directory, recursive_mode); // найти файлы в подпапке
            }
        } else if (entry->d_type == DT_REG) { // если запись - файл
            std::string filename = folder + "/" + entry->d_name; // имя файла
            std::string hash = HashGenerator::calculate_md5(filename); // хеш файла

            if (!hash.empty()) { // если хеш не пустой
                files_by_hash[hash].push_back(filename); // добавить файл в список файлов с таким же хешем
            } else { // если хеш пустой
                std::cerr << "Error calculating hash for file: " << filename
                          << std::endl; // вывести сообщение об ошибке
            }
        }
    }
    closedir(dir); // закрыть папку
}

void DuplicatesHandler::sort_by_creation_time() { // реализация метода sort_by_creation_time
    for (auto &pair: files_by_hash) { // для каждой пары в списке файлов по хешу
        std::vector <std::string> &files = pair.second; // список файлов
        std::sort(files.begin(), files.end(),
                  [](const std::string &file1, const std::string &file2) { // отсортировать по времени создания
                      struct stat file1_stat{}, file2_stat{}; // информация о файлах
                      if (stat(file1.c_str(), &file1_stat) != 0 ||
                          stat(file2.c_str(), &file2_stat) != 0) { // если не удалось получить информацию о файлах
                          return false; // вернуть false
                      }
                      return file1_stat.st_ctime <
                             file2_stat.st_ctime; // вернуть результат сравнения времени создания файлов
                  });
    }
}

void DuplicatesHandler::find_duplicates() { // реализация метода find_duplicates
    for (const auto &pair: files_by_hash) { // для каждой пары в списке файлов по хешу
        const std::vector <std::string> &files = pair.second; // список файлов
        if (files.size() > 1) { // если файлов больше одного
            logger.log("Duplicate files with hash " + pair.first + ":"); // вывести сообщение о дубликатах

            for (size_t i = 1; i < files.size(); ++i) { // для каждого файла, кроме первого
                logger.log(files[i]); // вывести путь к файлу
            }

            logger.log(""); // вывести пустую строку
        }
    }
}

void DuplicatesHandler::replace_duplicates() { // реализация метода replace_duplicates
    for (const auto &pair: files_by_hash) { // для каждой пары в списке файлов по хешу
        const std::vector <std::string> &files = pair.second; // список файлов
        if (files.size() > 1) { // если файлов больше одного
            for (size_t i = 1; i < files.size(); ++i) { // для каждого файла, кроме первого
                remove_duplicate(files[i]); // удалить дубликат
                create_hard_link(files[0], files[i]); // создать жесткую ссылку
            }
        }
    }
}

void DuplicatesHandler::remove_duplicate(const std::string &path) { // реализация метода remove_duplicate
    if (unlink(path.c_str()) == 0) { // удалить файл
        logger.log("Removed duplicate file: " + path); // вывести сообщение об удалении файла
    } else { // если не удалось удалить файл
        std::cerr << "Error removing duplicate file: " << path << std::endl; // вывести сообщение об ошибке
    }
}

void DuplicatesHandler::create_hard_link(const std::string &path_from,
                                         const std::string &path_to) { // реализация метода create_hard_link
    if (link(path_from.c_str(), path_to.c_str()) != 0) { // создать жесткую ссылку
        std::cerr << "Error creating hard link for file: " << path_to << std::endl; // вывести сообщение об ошибке
    } else { // если удалось создать жесткую ссылку
        logger.log("Created hard link for file: " + path_to + " -> " +
                   path_from); // вывести сообщение о создании жесткой ссылки
    }
}
