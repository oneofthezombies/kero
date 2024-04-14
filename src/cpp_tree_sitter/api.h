#ifndef KERO_CPP_TREE_SITTER_API_H
#define KERO_CPP_TREE_SITTER_API_H

#include <memory>
#include <ostream>
#include <string_view>

#include "tree_sitter/api.h"

namespace kero::ts {

// CStringDeleter
// --------

class CStringDeleter {
public:
  void operator()(char *str) const noexcept;
};

using CStringPtr = std::unique_ptr<char, CStringDeleter>;

// String
// --------

class String {
public:
  explicit String(CStringPtr &&c_str) noexcept;
  String(const String &) = delete;
  String(String &&) noexcept = default;
  ~String() noexcept = default;

  auto operator=(const String &) -> String & = delete;
  auto operator=(String &&) noexcept -> String & = default;

  auto is_null() const noexcept -> bool;
  auto string_view() const noexcept -> std::string_view;

private:
  CStringPtr c_str_;
};

// Point
// --------

struct Point : public TSPoint {
  Point(const TSPoint &ts_point) noexcept;
  Point(const Point &) noexcept = default;
  Point(Point &&) noexcept = default;
  ~Point() noexcept = default;

  auto operator=(const Point &) noexcept -> Point & = default;
  auto operator=(Point &&) noexcept -> Point & = default;
};

auto operator<<(std::ostream &os, const Point &point) -> std::ostream &;

// Node
// --------

class Node {
public:
  explicit Node(TSNode &&node) noexcept;
  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  ~Node() noexcept = default;

  auto operator=(const Node &) -> Node & = delete;
  auto operator=(Node &&) noexcept -> Node & = default;

  auto start_byte() const noexcept -> uint32_t;
  auto start_point() const noexcept -> Point;
  auto end_byte() const noexcept -> uint32_t;
  auto end_point() const noexcept -> Point;
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
  auto field_name_for_child(uint32_t index) const noexcept -> std::string_view;
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
  auto descendant_for_point_range(Point start, Point end) const noexcept
      -> Node;
  auto named_descendant_for_point_range(Point start, Point end) const noexcept
      -> Node;

  auto as_raw() noexcept -> TSNode;

private:
  TSNode node_;
};

auto operator<<(std::ostream &os, const Node &node) -> std::ostream &;

// TSTreeDeleter
// --------

class TSTreeDeleter {
public:
  void operator()(TSTree *tree) const noexcept;
};

using TSTreePtr = std::unique_ptr<TSTree, TSTreeDeleter>;

// Tree
// --------

class Tree {
public:
  explicit Tree(TSTreePtr &&tree) noexcept;
  Tree(const Tree &) = delete;
  Tree(Tree &&) noexcept = default;
  ~Tree() noexcept = default;

  auto operator=(const Tree &) -> Tree & = delete;
  auto operator=(Tree &&) noexcept -> Tree & = default;

  auto root_node() const noexcept -> Node;

  auto is_null() const noexcept -> bool;

  // Consumes the `TSTreePtr` and returns a unique pointer to it.
  auto into_raw() noexcept -> TSTreePtr;

  static auto null() noexcept -> Tree;

private:
  TSTreePtr tree_;
};

auto operator<<(std::ostream &os, const Tree &tree) -> std::ostream &;

// TSParserDeleter
// --------

class TSParserDeleter {
public:
  void operator()(TSParser *parser) const noexcept;
};

using TSParserPtr = std::unique_ptr<TSParser, TSParserDeleter>;

// Parser
// --------

class Parser {
public:
  Parser() noexcept;
  Parser(const Parser &) = delete;
  Parser(Parser &&) noexcept = default;
  ~Parser() noexcept = default;

  auto operator=(const Parser &) -> Parser & = delete;
  auto operator=(Parser &&) noexcept -> Parser & = default;

  auto set_language(const TSLanguage *language) const noexcept -> bool;

  // if `timeout_micros` is 0, there is no timeout.
  auto set_timeout_micros(const uint64_t timeout_micros) const noexcept -> void;

  auto set_cancellation_flag(
      const std::unique_ptr<size_t> &cancellation_flag) const noexcept -> void;
  auto parse_string(Tree &&old_tree,
                    const std::string_view string) const noexcept -> Tree;

  auto is_null() const noexcept -> bool;

private:
  TSParserPtr parser_;
};

} // namespace kero::ts

#endif // KERO_CPP_TREE_SITTER_API_H
