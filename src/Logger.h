#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <system_error>

class Logger {
public:
    enum class Level { Debug, Info, Warning, Error };

    struct Options {
        std::filesystem::path directory = "logFiles"; // relative to CWD
        bool append = true;                            // append vs truncate
        bool includeTimestamp = true;                  // add timestamps
        bool autoCreateDirectory = true;               // create directory if missing
        std::string lineEnding = "\n";
    };

    explicit Logger(std::string_view fileName, Options opts = {});

    void write(std::string_view message);
    void write(Level level, std::string_view message);

    std::string readAll() const;

    bool remove(std::error_code& ec) const noexcept;
    static bool removeFile(const std::filesystem::path& file, std::error_code& ec) noexcept;

    const std::filesystem::path& filePath() const noexcept { return filePath_; }
    const Options& options() const noexcept { return opts_; }

private:
    Options opts_;
    std::filesystem::path filePath_;

    static std::string sanitizeFileStem(std::string_view name);
    static std::string randomSuffix();     // small random string to avoid collisions
    static std::string nowISO8601();       // "YYYY-MM-DDTHH:MM:SS"
    static std::string levelToString(Level level);
};