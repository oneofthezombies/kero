#ifndef PEG_PARSER_CLI_H
#define PEG_PARSER_CLI_H

#include <memory>
#include <string_view>

namespace peg_parser {

class Cli {
public:
  using self = Cli;
  using self_ptr = std::unique_ptr<self>;
  using args = std::vector<std::string_view>;

  static self_ptr from_args(args&& args);

private:
  Cli() = default;
  ~Cli() = default;
  Cli(const Cli&) = delete;
  Cli& operator=(const Cli&) = delete;
};

} // namespace peg_parser

#endif // PEG_PARSER_CLI_H