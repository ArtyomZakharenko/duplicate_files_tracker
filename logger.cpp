#include <iostream>
#include <sys/stat.h>
#include "logger.h"

Logger::Logger() {
    mkdir("Logs", 0777);
    std::string log_file_name = get_log_file_name();
    file_stream.open("Logs/" + log_file_name, std::ios::out | std::ios::app);
if (!file_stream.is_open()) {
        std::cerr << "Could not open log file: " << log_file_name << std::endl;
    }
}

Logger::~Logger() {
    if (file_stream.is_open()) {
        file_stream.close();
    }
}

void Logger::log(const std::string& message) {
    std::cout << message << std::endl;
    if (file_stream.is_open()) {
        file_stream.write(message.c_str(), message.size());
        file_stream.write("\n", 1);
    }
}

std::string Logger::get_log_file_name() {
    time_t raw_time;
    struct tm *time_info;
    char buffer[80];

    time(&raw_time);
    time_info = localtime(&raw_time);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", time_info);
    std::string time_string(buffer);

    return "Duplicate_File_Tracker_" + time_string + ".log";
}

