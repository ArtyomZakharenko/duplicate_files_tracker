#ifndef DUBLICATE_FILE_TRACKER_FILE_HASHER_H
#define DUBLICATE_FILE_TRACKER_FILE_HASHER_H


#include <openssl/evp.h>
#include <string>

class FileHasher {
public:
    static std::string calculate_md5(const std::string& filepath);
};

#endif //DUBLICATE_FILE_TRACKER_FILE_HASHER_H
