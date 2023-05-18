#include "file_handler.h"

void FileHandler::run(int argc, char *argv[]) {
    bool recursive = false;
    std::string directory;

    if (argc == 3 && std::string(argv[1]) == "-r") {
        recursive = true;
        directory = argv[2];
    } else if (argc == 2) {
        directory = argv[1];
    } else {
        print_usage();
        return;
    }

    logger.set_log_file_name(get_log_file_name());

    find_files(directory, recursive);
    find_duplicates();
}

void FileHandler::print_usage() {
    std::cerr << "Usage: ./duplicate_finder [-r] <directory>" << std::endl;
}

void FileHandler::find_files(const std::string &directory, bool recursive) {
    DIR *dir = opendir(directory.c_str());
    if (!dir) {
        std::cerr << "Error opening directory: " << directory << std::endl;
        return;
    }

    dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            if (recursive && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                std::string sub_directory = directory + "/" + entry->d_name;
                find_files(sub_directory, recursive);
            }
        } else if (entry->d_type == DT_REG) {
            std::string filename = directory + "/" + entry->d_name;
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

void FileHandler::find_duplicates() {
    for (const auto& pair : files_by_hash) {
        const std::vector<std::string>& files = pair.second;
        if (files.size() > 1) {
            logger.log("Duplicate files with hash " + pair.first + ":");

            for (size_t i = 1; i < files.size(); ++i) {
                logger.log(files[i]);
            }

            logger.log("");
        }

        replace_duplicates(files);
    }
}

void FileHandler::replace_duplicates(const std::vector<std::string> &files) {
     if (files.empty()) {
        return;
    }

    const std::string& first_file = files[0];

    // Получение прав доступа первого файла
    struct stat file_stat;
    if (stat(first_file.c_str(), &file_stat) != 0) {
        std::cerr << "Error getting file permissions: " << first_file << std::endl;
        return;
    }
    mode_t permissions = file_stat.st_mode;

    // Удаление каждого дубликата, кроме первого файла, и создание жесткой ссылки
    for (size_t i = 1; i < files.size(); ++i) {
        const std::string& duplicate_path = files[i];

        if (unlink(duplicate_path.c_str()) == 0) {
            logger.log("Removed duplicate file: " + duplicate_path);

            if (link(first_file.c_str(), duplicate_path.c_str()) != 0) {
                std::cerr << "Error creating hard link for file: " << duplicate_path << std::endl;
            } else {
                // Установка прав доступа для созданной жесткой ссылки
                if (chmod(duplicate_path.c_str(), permissions) != 0) {
                    std::cerr << "Error setting file permissions: " << duplicate_path << std::endl;
                }
                logger.log("Added hard link: " + duplicate_path);
            }
        } else {
            std::cerr << "Error removing duplicate file: " << duplicate_path << std::endl;
        }
    }
}

std::string FileHandler::get_log_file_name() {
    std::time_t now = std::time(nullptr);
    std::tm *time_info = std::localtime(&now);

    char filename[64];
    std::strftime(filename, sizeof(filename), "Log_%Y-%m-%d.%H:%M:%S.txt", time_info);

    return std::string(filename);
}