#include "peg_parser.h"
#include "./log.h"

#include <fstream>

namespace peg_parser {

auto example() -> void {
  struct FileTransport : Transport {
    FileTransport(std::ostream& ostream) : ostream_{ostream} {}

    auto ostream() -> std::ostream& override { return ostream_; }

  private:
    std::ostream& ostream_;
  };

  Logger logger;
  logger.set_level(LogLevel::Debug);
  logger.add_transport(std::make_unique<ConsoleTransport>());

  std::fstream file("/Users/hunhoekim/repo/kero/log.txt", std::ios::out);
  logger.add_transport(std::make_unique<FileTransport>(file));

  ERROR(logger) << "Hello, world! error" << std::endl;
  WARN(logger) << "Hello, world! warn" << std::endl;
  INFO(logger) << "Hello, world! info" << std::endl;
  DEBUG(logger) << "Hello, world! debug" << std::endl;
}

} // namespace peg_parser