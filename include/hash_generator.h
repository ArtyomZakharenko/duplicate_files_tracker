#ifndef DUPLICATE_FILE_TRACKER_FILE_HASHER_H
#define DUPLICATE_FILE_TRACKER_FILE_HASHER_H

#include <openssl/evp.h>
#include <string>

class HashGenerator { // класс для генерации хеша
public:
    static std::string calculate_md5(const std::string &filepath); // вычислить хеш файла
};

#endif //DUPLICATE_FILE_TRACKER_FILE_HASHER_H
