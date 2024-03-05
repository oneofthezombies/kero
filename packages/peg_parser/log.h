#ifndef PEG_PARSER_LOG_H
#define PEG_PARSER_LOG_H

#include <iostream>
#include <streambuf>

namespace peg_parser {

class Transport {
public:
  virtual ~Transport() {}

  virtual auto out() -> std::ostream& = 0;
};

class ConsoleTransport : public Transport {
public:
  auto out() -> std::ostream& override { return std::cout; }
};

enum class LogLevel : int8_t {
  Error = 0,
  Warning,
  Info,
  Debug,
};

class Logger {
public:
  class Stream {
  public:
    Stream(std::vector<std::unique_ptr<Transport>>& transports)
        : transports_{transports} {}

    template <typename T> auto operator<<(const T& value) -> Stream& {
      for (auto& transport : transports_) {
        transport->out() << value;
      }
      return *this;
    }

  private:
    std::vector<std::unique_ptr<Transport>>& transports_;
  };

  Logger() {}

  auto set_level(LogLevel level) -> Logger& {
    level_ = level;
    return *this;
  }

  auto level() const -> LogLevel { return level_; }

  auto add_transport(std::unique_ptr<Transport>&& transport) -> Logger& {
    transports_.push_back(std::move(transport));
    return *this;
  }

  auto log(LogLevel level) -> Stream {
    if (level <= level_) {
      return Stream{transports_};
    }

    static std::vector<std::unique_ptr<Transport>> null_transports_{};
    return Stream{null_transports_};
  }

private:
  std::vector<std::unique_ptr<Transport>> transports_{};
  LogLevel level_{LogLevel::Info};
};

void example() {
  Logger logger{};
  logger.set_level(LogLevel::Debug)
      .add_transport(std::make_unique<ConsoleTransport>());
  logger.log(LogLevel::Debug) << "Debug message" << std::endl;
  std::cout << "Done" << std::endl;
}

} // namespace peg_parser

#endif // PEG_PARSER_LOG_H