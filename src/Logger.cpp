#include "Logger.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>

using namespace std;

static std::filesystem::path ensureLogExtension(std::filesystem::path p) {
    if (p.extension() != ".log") p.replace_extension(".log");
    return p;
}

Logger::Logger(std::string_view fileName, Options opts)
    : opts_(std::move(opts)) {

    // sanitize filename stem (remove invalid chars, remove extension)
    const std::string stem = sanitizeFileStem(fileName);

    // Build path: <directory>/<stem>_<random>.log
    std::filesystem::path dir = opts_.directory;
    std::filesystem::path full = dir / (stem + "_" + randomSuffix() + ".log");
    filePath_ = full;

    if (opts_.autoCreateDirectory) {
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        // If it fails, we still try to open and let the stream show failure.
    }

    std::ios::openmode mode = std::ios::out;
    mode |= (opts_.append ? std::ios::app : std::ios::trunc);

    std::ofstream out(filePath_, mode);
    if (!out) {
        throw std::runtime_error("Logger: failed to open log file: " + filePath_.string());
    }

    // Optional header
    out << "Logging started at: " << nowISO8601() << opts_.lineEnding;
    out << "File: " << filePath_.string() << opts_.lineEnding;
    out << "----------------------------------------" << opts_.lineEnding;
}

void Logger::write(std::string_view message) {
    write(Level::Info, message);
}

void Logger::write(Level level, std::string_view message) {
    std::ios::openmode mode = std::ios::out | std::ios::app;
    std::ofstream out(filePath_, mode);
    if (!out) {
        throw std::runtime_error("Logger: failed to write log file: " + filePath_.string());
    }

    if (opts_.includeTimestamp) {
        out << "[" << nowISO8601() << "] ";
    }

    out << "[" << levelToString(level) << "] " << message << opts_.lineEnding;
}

std::string Logger::readAll() const {
    std::ifstream in(filePath_, std::ios::in);
    if (!in) {
        throw std::runtime_error("Logger: failed to read log file: " + filePath_.string());
    }

    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

bool Logger::remove(std::error_code& ec) const noexcept {
    return std::filesystem::remove(filePath_, ec);
}

bool Logger::removeFile(const std::filesystem::path& file, std::error_code& ec) noexcept {
    return std::filesystem::remove(file, ec);
}

std::string Logger::sanitizeFileStem(std::string_view name) {
    // Remove extension if present and strip invalid characters across platforms.
    std::string s(name);

    // If user passes something like "mylog.txt" -> keep only stem
    std::filesystem::path p(s);
    s = p.stem().string();

    // Replace invalid / risky characters with '_'
    // (Windows invalid: <>:"/\|?*  plus control chars; also avoid spaces if you want)
    for (char& c : s) {
        const bool bad =
            (c < 32) ||
            c == '<' || c == '>' || c == ':' || c == '"' ||
            c == '/' || c == '\\' || c == '|' || c == '?' || c == '*' ||
            c == '\t' || c == '\n' || c == '\r';
        if (bad) c = '_';
    }

    // Fallback if empty
    if (s.empty()) s = "log";

    return s;
}

std::string Logger::randomSuffix() {
    // good enough uniqueness without srand/time pitfalls
    static thread_local std::mt19937_64 rng{std::random_device{}()};
    std::uniform_int_distribution<unsigned long long> dist;
    auto v = dist(rng);

    std::ostringstream ss;
    ss << std::hex << v;
    return ss.str();
}

std::string Logger::nowISO8601() {
    using clock = std::chrono::system_clock;
    auto now = clock::now();
    std::time_t t = clock::to_time_t(now);

    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return ss.str();
}

std::string Logger::levelToString(Level level) {
    switch (level) {
        case Level::Debug:   return "DEBUG";
        case Level::Info:    return "INFO";
        case Level::Warning: return "WARN";
        case Level::Error:   return "ERROR";
    }
    return "INFO";
}