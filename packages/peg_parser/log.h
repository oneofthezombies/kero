#ifndef PEG_PARSER_LOG_H
#define PEG_PARSER_LOG_H

#include <iostream>

namespace peg_parser {

struct Transport {
  virtual ~Transport() {}

  virtual auto ostream() -> std::ostream& = 0;
};

struct ConsoleTransport : Transport {
  virtual auto ostream() -> std::ostream& override { return std::cout; }
};

enum class LogLevel : int8_t {
  Error = 0,
  Warning,
  Info,
  Debug,
};

struct Logger {
  using Transports = std::vector<std::unique_ptr<Transport>>;

  struct Stream {
    Stream(Transports& transports, LogLevel filter_level, LogLevel log_level,
           const std::string_view& file, int32_t line)
        : transports_{transports}, filter_level_{filter_level},
          log_level_{log_level}, file_{file}, line_{line} {}

    Stream(Stream&& other)
        : transports_{other.transports_}, filter_level_{other.filter_level_},
          log_level_{other.log_level_}, file_{other.file_}, line_{other.line_} {
    }

    template <typename T> auto operator<<(T&& value) -> Stream& {
      if (log_level_ < filter_level_) {
        return *this;
      }

      for (auto& transport : transports_) {
        transport->ostream() << std::forward<T>(value);
      }
      return *this;
    }

    auto operator<<(std::ostream& (*endl)(std::ostream&)) -> Stream& {
      for (auto& transport : transports_) {
        transport->ostream() << endl;
      }
      return *this;
    }

    Stream(const Stream&) = delete;
    auto operator=(const Stream&) -> Stream& = delete;
    auto operator=(Stream&&) -> Stream& = delete;

  private:
    Transports& transports_;
    LogLevel filter_level_;
    LogLevel log_level_;
    const std::string_view& file_;
    int32_t line_;
  };

  Logger() {}

  auto set_level(LogLevel level) -> Logger& {
    filter_level_ = level;
    return *this;
  }

  auto level() const -> LogLevel { return filter_level_; }

  auto add_transport(std::unique_ptr<Transport>&& transport) -> Logger& {
    transports_.push_back(std::move(transport));
    return *this;
  }

  auto stream(LogLevel log_level, const std::string_view& file, int32_t line)
      -> Stream {
    return Stream{transports_, filter_level_, log_level, file, line};
  }

private:
  std::vector<std::unique_ptr<Transport>> transports_{};
  LogLevel filter_level_{LogLevel::Info};
};

#define ERROR(logger) logger.stream(LogLevel::Error, __FILE__, __LINE__)
#define WARN(logger) logger.stream(LogLevel::Warning, __FILE__, __LINE__)
#define INFO(logger) logger.stream(LogLevel::Info, __FILE__, __LINE__)
#define DEBUG(logger) logger.stream(LogLevel::Debug, __FILE__, __LINE__)

} // namespace peg_parser

#endif // PEG_PARSER_LOG_H