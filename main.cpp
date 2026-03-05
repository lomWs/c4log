#include "src/Logger.h"
#include <iostream>

int main() {
    Logger::Options opts;
    opts.directory = "logFiles";
    opts.append = true;

    Logger log("my_app", opts);

    log.write(Logger::Level::Info, "Hello log!");
    log.write(Logger::Level::Error, "Something went wrong.");

    std::cout << log.readAll() << "\n";

    // Delete (optional)
    // std::error_code ec;
    // log.remove(ec);

    return 0;
}