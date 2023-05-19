#include <iostream>
#include <sys/stat.h>
#include "logger.h"

Logger::Logger() { // реализация конструктора
    mkdir("Logs", 0777); // создание папки Logs
    std::string log_file_name = get_log_file_name(); // получение имени файла для логирования
    file_stream.open("Logs/" + log_file_name, std::ios::out | std::ios::app); // открытие файла для логирования
if (!file_stream.is_open()) { // если файл не открылся
        std::cerr << "Could not open log file: " << log_file_name << std::endl; // выводим сообщение об ошибке
    }
}

Logger::~Logger() { // реализация деструктора
    if (file_stream.is_open()) { // если файл открыт
        file_stream.close(); // закрываем файл
    }
}

void Logger::log(const std::string& message) { // реализация метода логирования
    std::cout << message << std::endl; // выводим сообщение в консоль
    if (file_stream.is_open()) { // если файл открыт
        file_stream.write(message.c_str(), message.size()); // записываем сообщение в файл
        file_stream.write("\n", 1); // записываем перенос строки в файл
    }
}

std::string Logger::get_log_file_name() { // реализация метода получения имени файла для логирования
    time_t raw_time; // получаем текущее время
    struct tm *time_info; // структура для хранения времени
    char buffer[80]; // буфер для хранения времени

    time(&raw_time); // получаем текущее время
    time_info = localtime(&raw_time); // получаем локальное время

    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", time_info); // форматируем время
    std::string time_string(buffer); // преобразуем время в строку

    return "Duplicate_File_Tracker_" + time_string + ".log"; // возвращаем имя файла для логирования
}

