#ifndef DUPLICATE_FILE_TRACKER_LOGGER_H
#define DUPLICATE_FILE_TRACKER_LOGGER_H

#include <string>
#include <fstream>

class Logger { // класс для логирования
public:
    explicit Logger(); // конструктор
    void log(const std::string& message); // логирование сообщения

private:
    std::ofstream file_stream; // поток для записи в файл
    static std::string get_log_file_name(); // получить имя файла для логирования
};

#endif //DUPLICATE_FILE_TRACKER_LOGGER_H
