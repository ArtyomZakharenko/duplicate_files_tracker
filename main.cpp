#include <iostream>
#include "logger.h"
#include "file_hasher.h"

int main() {
    Logger logger;
    logger.set_log_file_name("log.txt");
    logger.log("Hello, world!\n");
    logger.log(FileHasher::calculate_md5("/home/artsem/Загрузки/Telegram Desktop/2023-03-17_21-15-03.png"));
    return 0;
}