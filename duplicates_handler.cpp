#include "duplicates_handler.h"
#include "hash_generator.h"

#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <algorithm>

void DuplicatesHandler::run(const std::string &directory, bool recursive) {
    find_files(directory, recursive);
    sort_by_creation_time();
    find_duplicates();
    replace_duplicates();
}

void DuplicatesHandler::find_files(const std::string &folder, bool recursive_mode) {
    DIR *dir = opendir(folder.c_str());
    if (!dir) {
        std::cerr << "Error opening folder: " << folder << std::endl;
        return;
    }

    dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            if (recursive_mode && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                std::string sub_directory = folder + "/" + entry->d_name;
                find_files(sub_directory, recursive_mode);
            }
        } else if (entry->d_type == DT_REG) {
            std::string filename = folder + "/" + entry->d_name;
            std::string hash = HashGenerator::calculate_md5(filename);

            if (!hash.empty()) {
                files_by_hash[hash].push_back(filename);
            } else {
                std::cerr << "Error calculating hash for file: " << filename << std::endl;
            }
        }
    }
    closedir(dir);
}

void DuplicatesHandler::sort_by_creation_time() {
    for (auto &pair: files_by_hash) {
        std::vector<std::string> &files = pair.second;
        std::sort(files.begin(), files.end(), [](const std::string &file1, const std::string &file2) {
            struct stat file1_stat{}, file2_stat{};
            if (stat(file1.c_str(), &file1_stat) != 0 || stat(file2.c_str(), &file2_stat) != 0) {
                return false;
            }
            return file1_stat.st_ctime < file2_stat.st_ctime;
        });
    }
}

void DuplicatesHandler::find_duplicates() {
    for (const auto &pair: files_by_hash) {
        const std::vector<std::string> &files = pair.second;
        if (files.size() > 1) {
            logger.log("Duplicate files with hash " + pair.first + ":");

            for (size_t i = 1; i < files.size(); ++i) {
                logger.log(files[i]);
            }

            logger.log("");
        }
    }
}

void DuplicatesHandler::replace_duplicates() {
    for (const auto &pair: files_by_hash) {
        const std::vector<std::string> &files = pair.second;
        if (files.size() > 1) {
            for (size_t i = 1; i < files.size(); ++i) {
                remove_duplicate(files[i]);
                create_hard_link(files[0], files[i]);
            }
        }
    }
}

void DuplicatesHandler::remove_duplicate(const std::string &path) {
    if (unlink(path.c_str()) == 0) {
        logger.log("Removed duplicate file: " + path);
    } else {
        std::cerr << "Error removing duplicate file: " << path << std::endl;
    }
}

void DuplicatesHandler::create_hard_link(const std::string &path_from, const std::string &path_to) {
    if (link(path_from.c_str(), path_to.c_str()) != 0) {
        std::cerr << "Error creating hard link for file: " << path_to << std::endl;
    } else {
        logger.log("Created hard link for file: " + path_to+ " -> " + path_from);
    }
}
