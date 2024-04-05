#ifndef KERO_GRAMMAR_PARSER_CORE_H
#define KERO_GRAMMAR_PARSER_CORE_H

#include "tao/pegtl.hpp"

namespace pegtl = tao::pegtl;

namespace kero {
struct prefix : pegtl::string<'H', 'e', 'l', 'l', 'o', ',', ' '> {};
struct name : pegtl::plus<pegtl::alpha> {};
struct grammar : pegtl::must<prefix, name, pegtl::one<'!'>, pegtl::eof> {};
template <typename Rule> struct action {};
template <> struct action<name> {
  template <typename ParseInput>
  static void apply(const ParseInput& in, std::string& v) {
    v = in.string();
  }
};

auto Test() -> bool {
  std::string source = "Hello, World!";
  std::string result;
  pegtl::string_input<> input(source, "");
  pegtl::parse<grammar, action>(input, result);
  return result == "World";
}

} // namespace kero

#endif // KERO_GRAMMAR_PARSER_CORE_H
