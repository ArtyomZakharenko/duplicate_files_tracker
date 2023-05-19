#include "hash_generator.h"

std::string HashGenerator::calculate_md5(const std::string& filepath) {
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    if (!md_ctx) {
        return "";
    }

    const EVP_MD* md = EVP_md5();
    if (!md) {
        EVP_MD_CTX_free(md_ctx);
        return "";
    }

    if (EVP_DigestInit_ex(md_ctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(md_ctx);
        return "";
    }

    FILE* file = fopen(filepath.c_str(), "rb");
    if (!file) {
        EVP_MD_CTX_free(md_ctx);
        return "";
    }

    unsigned char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) != 0) {
        if (EVP_DigestUpdate(md_ctx, buffer, bytes_read) != 1) {
            EVP_MD_CTX_free(md_ctx);
            fclose(file);
            return "";
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(md_ctx, hash, &hash_len) != 1) {
        EVP_MD_CTX_free(md_ctx);
        fclose(file);
        return "";
    }

    EVP_MD_CTX_free(md_ctx);
    fclose(file);

    char md5_string[EVP_MAX_MD_SIZE * 2 + 1];
    for (unsigned int i = 0; i < hash_len; ++i) {
        sprintf(&md5_string[i * 2], "%02x", static_cast<unsigned int>(hash[i]));
    }

    return md5_string;
}
