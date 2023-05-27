#include "../include/hash_generator.h"

std::string HashGenerator::calculate_md5(const std::string& filepath) { // реализация метода вычисления хеша
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new(); // создание контекста
    if (!md_ctx) { // если контекст не создан
        return ""; // возвращаем пустую строку
    }

    const EVP_MD* md = EVP_md5(); // создание объекта для хранения хеша
    if (!md) { // если объект не создан
        EVP_MD_CTX_free(md_ctx); // освобождаем память
        return ""; // возвращаем пустую строку
    }

    if (EVP_DigestInit_ex(md_ctx, md, nullptr) != 1) { // инициализация контекста
        EVP_MD_CTX_free(md_ctx); // освобождаем память
        return ""; // возвращаем пустую строку
    }

    FILE* file = fopen(filepath.c_str(), "rb"); // открываем файл в бинарном режиме для чтения
    if (!file) { // если файл не открыт
        EVP_MD_CTX_free(md_ctx); // освобождаем память
        return ""; // возвращаем пустую строку
    }

    unsigned char buffer[1024]; // буфер для чтения файла
    size_t bytes_read; // количество прочитанных байт
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) != 0) { // пока не достигнут конец файла
        if (EVP_DigestUpdate(md_ctx, buffer, bytes_read) != 1) { // обновляем контекст
            EVP_MD_CTX_free(md_ctx); // освобождаем память
            fclose(file); // закрываем файл
            return ""; // возвращаем пустую строку
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE]; // хеш
    unsigned int hash_len; // длина хеша
    if (EVP_DigestFinal_ex(md_ctx, hash, &hash_len) != 1) { // получаем хеш
        EVP_MD_CTX_free(md_ctx); // освобождаем память
        fclose(file); // закрываем файл
        return ""; // возвращаем пустую строку
    }

    EVP_MD_CTX_free(md_ctx); // освобождаем память
    fclose(file); // закрываем файл

    char md5_string[EVP_MAX_MD_SIZE * 2 + 1]; // строка для хранения хеша
    for (unsigned int i = 0; i < hash_len; ++i) { // переводим хеш в строку
        sprintf(&md5_string[i * 2], "%02x", static_cast<unsigned int>(hash[i])); // переводим хеш в строку
    }

    return md5_string; // возвращаем хеш
}
