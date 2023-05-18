#ifndef DUBLICATE_FILE_TRACKER_FILE_HANDLER_H
#define DUBLICATE_FILE_TRACKER_FILE_HANDLER_H

#include "logger.h"
#include "file_hasher.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <ctime>


class FileHandler {
public:
    void run(int argc, char* argv[]);

private:
    static void print_usage() ;
    void find_files(const std::string& directory, bool recursive);
    void find_duplicates();
    static std::string get_log_file_name() ;

    Logger logger;
    std::unordered_map<std::string, std::vector<std::string>> files_by_hash;

    void replace_duplicates(const std::vector<std::string> &files);
};


#endif //DUBLICATE_FILE_TRACKER_FILE_HANDLER_H
