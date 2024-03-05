#include "./cli.h"

namespace peg_parser {

Cli::self_ptr Cli::from_args(Cli::args&& args) { return self_ptr{}; }

} // namespace peg_parser
