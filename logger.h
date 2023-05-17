
#ifndef DUBLICATE_FILE_TRACKER_LOGGER_H
#define DUBLICATE_FILE_TRACKER_LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    Logger();
    void set_log_file_name(const std::string& filename);
    void log(const std::string& message);

private:
    std::ofstream file_stream;

};


#endif //DUBLICATE_FILE_TRACKER_LOGGER_H
