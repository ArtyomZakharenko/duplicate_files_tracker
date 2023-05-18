#ifndef DUPLICATE_FILE_TRACKER_FILE_HANDLER_H
#define DUPLICATE_FILE_TRACKER_FILE_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "logger.h"

class DuplicatesHandler {
private:
    std::unordered_map<std::string, std::vector<std::string>> files_by_hash;
    Logger logger;

public:
    void run(const std::string& directory, bool recursive);
    static void print_usage();

private:
    void find_files(const std::string& folder, bool recursive_mode);
    void sort_by_creation_time();
    void find_duplicates();
    void replace_duplicates();

    void remove_duplicate(const std::string &path);
    void create_hard_link(const std::string &path_from, const std::string &path_to);
};

#endif //DUPLICATE_FILE_TRACKER_FILE_HANDLER_H
