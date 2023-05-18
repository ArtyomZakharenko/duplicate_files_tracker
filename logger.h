#ifndef DUPLICATE_FILE_TRACKER_LOGGER_H
#define DUPLICATE_FILE_TRACKER_LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    explicit Logger();
    void log(const std::string& message);
    ~Logger();

private:
    std::ofstream file_stream;
    static std::string get_log_file_name();
};

#endif //DUPLICATE_FILE_TRACKER_LOGGER_H
