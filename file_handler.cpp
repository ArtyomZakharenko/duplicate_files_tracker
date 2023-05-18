#include "file_handler.h"
#include "file_hasher.h"

#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <algorithm>
#include <utility>

void DuplicateFinder::run(const std::string& directory, bool recursive) {
    find_files(directory, recursive);
    find_duplicates();
    replace_duplicates();
}

void DuplicateFinder::print_usage() {
    std::cerr << "Usage: ./Duplicate_File_Tracker [-r] <directory>" << std::endl;
}

void DuplicateFinder::find_files(const std::string& folder, bool recursive_mode) {
    DIR* dir = opendir(folder.c_str());
    if (!dir) {
        std::cerr << "Error opening folder: " << folder << std::endl;
        return;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            if (recursive_mode && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                std::string sub_directory = folder + "/" + entry->d_name;
                find_files(sub_directory, recursive_mode);
            }
        } else if (entry->d_type == DT_REG) {
            std::string filename = folder + "/" + entry->d_name;
            std::string hash = FileHasher::calculate_md5(filename);

            if (!hash.empty()) {
                files_by_hash[hash].push_back(filename);
            } else {
                std::cerr << "Error calculating hash for file: " << filename << std::endl;
            }
        }
    }

    closedir(dir);
}

void DuplicateFinder::find_duplicates() {
    for (const auto& pair : files_by_hash) {
        const std::vector<std::string>& files = pair.second;
        if (files.size() > 1) {
            logger.log("Duplicate files with hash " + pair.first + ":");

            for (size_t i = 1; i < files.size(); ++i) {
                logger.log(files[i]);
            }

            logger.log("");
        }
    }
}

void DuplicateFinder::replace_duplicates() {
    for (const auto& pair : files_by_hash) {
        const std::vector<std::string>& files = pair.second;
        if (files.size() > 1) {
            // Получение времени последней модификации для каждого файла
            std::vector<std::pair<std::string, time_t>> file_times;
            for (const std::string& file : files) {
                struct stat file_stat;
                if (stat(file.c_str(), &file_stat) != 0) {
                    std::cerr << "Error getting file information: " << file << std::endl;
                    continue;
                }
                file_times.emplace_back(file, file_stat.st_mtime);
            }

            // Сортировка файлов по времени последней модификации в порядке возрастания
            std::sort(file_times.begin(), file_times.end(),
                      [](const auto& a, const auto& b) {
                          return a.second < b.second;
                      });

            const std::string& oldest_file = file_times.front().first;

            // Удаление каждого дубликата, кроме самого старого файла, и создание жесткой ссылки
            for (size_t i = 1; i < file_times.size(); ++i) {
                const std::string& duplicate_path = file_times[i].first;

                if (unlink(duplicate_path.c_str()) == 0) {
                    logger.log("Removed duplicate file: " + duplicate_path);

                    if (link(oldest_file.c_str(), duplicate_path.c_str()) != 0) {
                        std::cerr << "Error creating hard link for file: " << duplicate_path << std::endl;
                    } else {
                        // Установка прав доступа для созданной жесткой ссылки
                        struct stat oldest_file_stat;
                        if (stat(oldest_file.c_str(), &oldest_file_stat) != 0) {
                            std::cerr << "Error getting file permissions: " << oldest_file << std::endl;
                            continue;
                        }
                        mode_t permissions = oldest_file_stat.st_mode;

                        if (chmod(duplicate_path.c_str(), permissions) != 0) {
                            std::cerr << "Error setting file permissions: " << duplicate_path << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error removing duplicate file: " << duplicate_path << std::endl;
                }
            }
        }
    }
}