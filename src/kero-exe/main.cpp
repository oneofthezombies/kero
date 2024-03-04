#include <iostream>
#include <string_view>
#include <vector>

[[nodiscard]]
auto parse_args(int argc, char** argv) -> std::vector<std::string_view> {
  return std::vector<std::string_view>(argv, argv + argc);
}

auto main(int argc, char* argv[]) -> int {
  auto args = parse_args(argc, argv);
  for (const auto& arg : args) {
    std::cout << arg << '\n';
  }
  return 0;
}
