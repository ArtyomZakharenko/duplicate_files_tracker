#ifndef DUPLICATE_FILE_TRACKER_FILE_HANDLER_H
#define DUPLICATE_FILE_TRACKER_FILE_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "logger.h"

class DuplicateFinder {
private:
    std::unordered_map<std::string, std::vector<std::string>> files_by_hash;
    Logger logger;

public:
    void run(const std::string& directory, bool recursive);
    static void print_usage();

private:
    void find_files(const std::string& folder, bool recursive_mode);
    void find_duplicates();
    void replace_duplicates();

};


#endif //DUPLICATE_FILE_TRACKER_FILE_HANDLER_H
