#ifndef KERO_COMPILER_PARSER_H
#define KERO_COMPILER_PARSER_H

#include <memory>
#include <optional>
#include <string_view>

#include "tree_sitter/api.h"

namespace kero::compiler {

class TSParserDeleter {
public:
  void operator()(TSParser *parser) const noexcept;
};

using TSParserPtr = std::unique_ptr<TSParser, TSParserDeleter>;

class TSTreeDeleter {
public:
  void operator()(TSTree *tree) const noexcept;
};

using TSTreePtr = std::unique_ptr<TSTree, TSTreeDeleter>;

class Parser {
public:
  class Builder {
  public:
    explicit Builder() noexcept = default;
    Builder(const Builder &) = delete;
    Builder(Builder &&) = delete;
    ~Builder() noexcept = default;

    auto operator=(const Builder &) -> Builder & = delete;
    auto operator=(Builder &&) -> Builder & = delete;

    // 0 means no timeout.
    auto set_timeout_micros(const size_t timeout_micros) noexcept -> Builder &;

    std::optional<Parser> build() const noexcept;

  private:
    size_t timeout_micros_{0};
  };

  Parser(const Parser &) = delete;
  Parser(Parser &&) = default;
  ~Parser() noexcept;

  auto operator=(const Parser &) -> Parser & = delete;
  auto operator=(Parser &&) -> Parser & = default;

  auto parse(const std::string_view source,
             TSTreePtr &&old_tree = nullptr) const noexcept -> TSTreePtr;

private:
  explicit Parser(TSParserPtr &&parser,
                  std::unique_ptr<size_t> &&cancellation_flag) noexcept;

  TSParserPtr parser_;
  std::unique_ptr<size_t> cancellation_flag_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_PARSER_H
