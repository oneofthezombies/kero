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

class String {
public:
  explicit String(char *data) noexcept;
  String(const String &) = delete;
  String(String &&) noexcept;
  ~String() noexcept;

  auto operator=(const String &) -> String & = delete;
  auto operator=(String &&) noexcept -> String &;

  auto string_view() const noexcept -> std::string_view;

private:
  char *data_;
};

class Node {
public:
  explicit Node(TSNode &&node) noexcept;
  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  ~Node() noexcept = default;

  auto operator=(const Node &) -> Node & = delete;
  auto operator=(Node &&) noexcept -> Node & = default;

  auto string() const noexcept -> String;

private:
  TSNode node_;
};

class Tree {
public:
  explicit Tree(TSTreePtr &&tree) noexcept;
  Tree(const Tree &) = delete;
  Tree(Tree &&) noexcept = default;
  ~Tree() noexcept = default;

  auto operator=(const Tree &) -> Tree & = delete;
  auto operator=(Tree &&) noexcept -> Tree & = default;

  auto empty() const noexcept -> bool;
  auto take() noexcept -> TSTreePtr;

  auto root_node() const noexcept -> std::optional<Node>;

  static auto null() noexcept -> Tree;

private:
  TSTreePtr tree_;
};

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
  Parser(Parser &&) noexcept = default;
  ~Parser() noexcept;

  auto operator=(const Parser &) -> Parser & = delete;
  auto operator=(Parser &&) noexcept -> Parser & = default;

  auto parse(const std::string_view source) const noexcept
      -> std::optional<Tree>;
  auto parse_incremental(const std::string_view source,
                         Tree &&old_tree) const noexcept -> std::optional<Tree>;

private:
  explicit Parser(TSParserPtr &&parser,
                  std::unique_ptr<size_t> &&cancellation_flag) noexcept;

  TSParserPtr parser_;
  std::unique_ptr<size_t> cancellation_flag_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_PARSER_H
