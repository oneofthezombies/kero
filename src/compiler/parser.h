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

class CStringDeleter {
public:
  void operator()(char *str) const noexcept;
};

using CStringPtr = std::unique_ptr<char, CStringDeleter>;

class String {
public:
  explicit String(CStringPtr &&c_str) noexcept;
  String(const String &) = delete;
  String(String &&) noexcept = default;
  ~String() noexcept = default;

  auto operator=(const String &) -> String & = delete;
  auto operator=(String &&) noexcept -> String & = default;

  auto string_view() const noexcept -> std::string_view;

private:
  CStringPtr c_str_;
};

class Node {
public:
  explicit Node(TSNode &&node) noexcept;
  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  ~Node() noexcept = default;

  auto operator=(const Node &) -> Node & = delete;
  auto operator=(Node &&) noexcept -> Node & = default;

  auto start_byte() const noexcept -> uint32_t;
  auto start_point() const noexcept -> TSPoint;
  auto end_byte() const noexcept -> uint32_t;
  auto end_point() const noexcept -> TSPoint;
  auto symbol() const noexcept -> TSSymbol;
  auto type() const noexcept -> std::string_view;
  auto grammar_symbol() const noexcept -> TSSymbol;
  auto grammar_type() const noexcept -> std::string_view;
  auto string() const noexcept -> String;
  auto eq(const Node &other) const noexcept -> bool;
  auto is_null() const noexcept -> bool;
  auto is_extra() const noexcept -> bool;
  auto is_named() const noexcept -> bool;
  auto is_missing() const noexcept -> bool;
  auto has_changes() const noexcept -> bool;
  auto has_error() const noexcept -> bool;
  auto is_error() const noexcept -> bool;
  auto descendant_count() const noexcept -> uint32_t;
  auto parse_state() const noexcept -> TSStateId;
  auto next_parse_state() const noexcept -> TSStateId;
  auto parent() const noexcept -> Node;
  auto child(uint32_t index) const noexcept -> Node;
  auto named_child(uint32_t index) const noexcept -> Node;
  auto child_by_field_id(TSFieldId field_id) const noexcept -> Node;
  auto child_by_field_name(std::string_view field_name) const noexcept -> Node;
  auto child_count() const noexcept -> uint32_t;
  auto named_child_count() const noexcept -> uint32_t;
  auto next_sibling() const noexcept -> Node;
  auto next_named_sibling() const noexcept -> Node;
  auto prev_sibling() const noexcept -> Node;
  auto prev_named_sibling() const noexcept -> Node;
  auto first_child_for_byte(uint32_t byte) const noexcept -> Node;
  auto first_named_child_for_byte(uint32_t byte) const noexcept -> Node;
  auto descendant_for_byte_range(uint32_t start, uint32_t end) const noexcept
      -> Node;
  auto named_descendant_for_byte_range(uint32_t start,
                                       uint32_t end) const noexcept -> Node;
  auto descendant_for_point_range(TSPoint start, TSPoint end) const noexcept
      -> Node;
  auto named_descendant_for_point_range(TSPoint start,
                                        TSPoint end) const noexcept -> Node;

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
