#include <iostream>
#include "logger.h"

Logger::Logger() = default;

void Logger::set_log_file_name(const std::string &filename) {
    file_stream.open(filename);
    if (!file_stream.is_open()) {
        std::cerr << "Error opening log file: " << filename << std::endl;
    }
}

void Logger::log(const std::string& message) {
    std::cout << message << std::endl;
    if (file_stream.is_open()) {
        file_stream.write(message.c_str(), message.size());
    }
}
