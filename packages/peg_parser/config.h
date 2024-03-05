#ifndef PEG_PARSER_CONFIG_H
#define PEG_PARSER_CONFIG_H

#include <ostream>

namespace peg_parser {

class Config {
public:
private:
  Config() = default;
  ~Config() = default;
  Config(const Config&) = delete;
  Config& operator=(const Config&) = delete;

  std::ostream& out;
};

} // namespace peg_parser

#endif // PEG_PARSER_CONFIG_H
