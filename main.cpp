#include <iostream>
#include "logger.h"

int main() {
    Logger logger;
    logger.set_log_file_name("log.txt");
    logger.log("Hello, world!");
    return 0;
}