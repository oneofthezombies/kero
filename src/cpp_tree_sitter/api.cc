#include "api.h"

#include <cassert>
#include <iostream>

using namespace kero::ts;

// CStringDeleter
// --------

void kero::ts::CStringDeleter::operator()(char *str) const noexcept {
  if (str == nullptr) {
    return;
  }
  free(str);
}

// String
// --------

kero::ts::String::String(CStringPtr &&c_str) noexcept
    : c_str_{std::move(c_str)} {}

auto kero::ts::String::is_null() const noexcept -> bool {
  return c_str_.get() == nullptr;
}

auto kero::ts::String::string_view() const noexcept -> std::string_view {
  if (is_null()) {
    return std::string_view{};
  }
  return std::string_view{c_str_.get()};
}

// Point
// --------

kero::ts::Point::Point(const TSPoint &ts_point) noexcept
    : TSPoint{ts_point.row, ts_point.column} {}

auto kero::ts::operator<<(std::ostream &os, const Point &point)
    -> std::ostream & {
  os << "Point{";
  os << "row=" << point.row;
  os << ", ";
  os << "column=" << point.column;
  os << "}";
  return os;
}

// Node
// --------

kero::ts::Node::Node(TSNode &&node) noexcept : node_{std::move(node)} {}

auto kero::ts::Node::start_byte() const noexcept -> uint32_t {
  return ts_node_start_byte(node_);
}

auto kero::ts::Node::start_point() const noexcept -> Point {
  return ts_node_start_point(node_);
}

auto kero::ts::Node::end_byte() const noexcept -> uint32_t {
  return ts_node_end_byte(node_);
}

auto kero::ts::Node::end_point() const noexcept -> Point {
  return ts_node_end_point(node_);
}

auto kero::ts::Node::symbol() const noexcept -> TSSymbol {
  return ts_node_symbol(node_);
}

auto kero::ts::Node::type() const noexcept -> std::string_view {
  return std::string_view{ts_node_type(node_)};
}

auto kero::ts::Node::grammar_symbol() const noexcept -> TSSymbol {
  return ts_node_grammar_symbol(node_);
}

auto kero::ts::Node::grammar_type() const noexcept -> std::string_view {
  return std::string_view{ts_node_grammar_type(node_)};
}

auto kero::ts::Node::string() const noexcept -> String {
  return String{CStringPtr{ts_node_string(node_)}};
}

auto kero::ts::Node::eq(const Node &other) const noexcept -> bool {
  return ts_node_eq(node_, other.node_);
}

auto kero::ts::Node::is_null() const noexcept -> bool {
  return ts_node_is_null(node_);
}

auto kero::ts::Node::is_extra() const noexcept -> bool {
  return ts_node_is_extra(node_);
}

auto kero::ts::Node::is_named() const noexcept -> bool {
  return ts_node_is_named(node_);
}

auto kero::ts::Node::is_missing() const noexcept -> bool {
  return ts_node_is_missing(node_);
}

auto kero::ts::Node::has_changes() const noexcept -> bool {
  return ts_node_has_changes(node_);
}

auto kero::ts::Node::has_error() const noexcept -> bool {
  return ts_node_has_error(node_);
}

auto kero::ts::Node::is_error() const noexcept -> bool {
  return ts_node_is_error(node_);
}

auto kero::ts::Node::descendant_count() const noexcept -> uint32_t {
  return ts_node_descendant_count(node_);
}

auto kero::ts::Node::parse_state() const noexcept -> TSStateId {
  return ts_node_parse_state(node_);
}

auto kero::ts::Node::next_parse_state() const noexcept -> TSStateId {
  return ts_node_next_parse_state(node_);
}

auto kero::ts::Node::parent() const noexcept -> Node {
  return Node{ts_node_parent(node_)};
}

auto kero::ts::Node::child(const uint32_t index) const noexcept -> Node {
  return Node{ts_node_child(node_, index)};
}

auto kero::ts::Node::named_child(const uint32_t index) const noexcept -> Node {
  return Node{ts_node_named_child(node_, index)};
}

auto kero::ts::Node::child_by_field_id(const TSFieldId field_id) const noexcept
    -> Node {
  return Node{ts_node_child_by_field_id(node_, field_id)};
}

auto kero::ts::Node::field_name_for_child(const uint32_t index) const noexcept
    -> std::string_view {
  const auto field_name = ts_node_field_name_for_child(node_, index);
  return std::string_view{field_name != nullptr ? field_name : ""};
}

auto kero::ts::Node::child_by_field_name(
    const std::string_view field_name) const noexcept -> Node {
  return Node{
      ts_node_child_by_field_name(node_, field_name.data(), field_name.size())};
}

auto kero::ts::Node::child_count() const noexcept -> uint32_t {
  return ts_node_child_count(node_);
}

auto kero::ts::Node::named_child_count() const noexcept -> uint32_t {
  return ts_node_named_child_count(node_);
}

auto kero::ts::Node::next_sibling() const noexcept -> Node {
  return Node{ts_node_next_sibling(node_)};
}

auto kero::ts::Node::next_named_sibling() const noexcept -> Node {
  return Node{ts_node_next_named_sibling(node_)};
}

auto kero::ts::Node::prev_sibling() const noexcept -> Node {
  return Node{ts_node_prev_sibling(node_)};
}

auto kero::ts::Node::prev_named_sibling() const noexcept -> Node {
  return Node{ts_node_prev_named_sibling(node_)};
}

auto kero::ts::Node::first_child_for_byte(const uint32_t byte) const noexcept
    -> Node {
  return Node{ts_node_first_child_for_byte(node_, byte)};
}

auto kero::ts::Node::first_named_child_for_byte(
    const uint32_t byte) const noexcept -> Node {
  return Node{ts_node_first_named_child_for_byte(node_, byte)};
}

auto kero::ts::Node::descendant_for_byte_range(
    const uint32_t start, const uint32_t end) const noexcept -> Node {
  return Node{ts_node_descendant_for_byte_range(node_, start, end)};
}

auto kero::ts::Node::named_descendant_for_byte_range(
    const uint32_t start, const uint32_t end) const noexcept -> Node {
  return Node{ts_node_named_descendant_for_byte_range(node_, start, end)};
}

auto kero::ts::Node::descendant_for_point_range(const Point start,
                                                const Point end) const noexcept
    -> Node {
  return Node{ts_node_descendant_for_point_range(node_, start, end)};
}

auto kero::ts::Node::named_descendant_for_point_range(
    const Point start, const Point end) const noexcept -> Node {
  return Node{ts_node_named_descendant_for_point_range(node_, start, end)};
}

auto kero::ts::Node::as_raw() const noexcept -> TSNode { return node_; }

auto kero::ts::operator<<(std::ostream &os, const Node &node)
    -> std::ostream & {
  os << "Node{";
  os << "start_byte=" << node.start_byte();
  os << ", ";
  os << "start_point=" << node.start_point();
  os << ", ";
  os << "end_byte=" << node.end_byte();
  os << ", ";
  os << "end_point=" << node.end_point();
  os << ", ";
  os << "symbol=" << node.symbol();
  os << ", ";
  os << "type=" << node.type();
  os << ", ";
  os << "grammar_symbol=" << node.grammar_symbol();
  os << ", ";
  os << "grammar_type=" << node.grammar_type();
  os << ", ";
  os << "is_null=" << node.is_null();
  os << ", ";
  os << "is_extra=" << node.is_extra();
  os << ", ";
  os << "is_named=" << node.is_named();
  os << ", ";
  os << "is_missing=" << node.is_missing();
  os << ", ";
  os << "has_changes=" << node.has_changes();
  os << ", ";
  os << "has_error=" << node.has_error();
  os << ", ";
  os << "is_error=" << node.is_error();
  os << ", ";
  os << "descendant_count=" << node.descendant_count();
  os << ", ";
  os << "parse_state=" << node.parse_state();
  os << ", ";
  os << "next_parse_state=" << node.next_parse_state();
  os << "}";
  return os;
}

// TSTreeDeleter
// --------

void kero::ts::TSTreeDeleter::operator()(TSTree *tree) const noexcept {
  ts_tree_delete(tree);
}

// Tree
// --------

kero::ts::Tree::Tree(TSTreePtr &&tree) noexcept : tree_{std::move(tree)} {}

auto kero::ts::Tree::is_null() const noexcept -> bool {
  return tree_.get() == nullptr;
}

auto kero::ts::Tree::into_raw() noexcept -> TSTreePtr {
  return std::move(tree_);
}

auto kero::ts::Tree::root_node() const noexcept -> Node {
  assert(!is_null() && "Tree::root_node: tree is null");
  return Node{ts_tree_root_node(tree_.get())};
}

auto kero::ts::Tree::print_dot_graph(const int file_descriptor) const noexcept
    -> void {
  assert(!is_null() && "Tree::print_dot_graphs: tree is null");
  ts_tree_print_dot_graph(tree_.get(), file_descriptor);
}

auto printRec(std::ostream &os, const Node &parent,
              const uint32_t current_index, const uint32_t depth) -> void {
  for (uint32_t i = 0; i < depth; ++i) {
    os << "  ";
  }
  const auto field_name = parent.field_name_for_child(current_index);
  os << "Child{";
  os << "index=";
  os << current_index;
  os << ", ";
  if (!field_name.empty()) {
    os << "field_name=";
    os << field_name;
    os << ", ";
  }
  os << "node=";
  const auto current_node = parent.child(current_index);
  os << current_node << "}\n";
  const auto child_count = current_node.child_count();
  for (uint32_t i = 0; i < child_count; ++i) {
    printRec(os, current_node, i, depth + 1);
  }
};

auto kero::ts::operator<<(std::ostream &os, const Tree &tree)
    -> std::ostream & {
  os << "Tree{";
  if (tree.is_null()) {
    os << "null";
    os << "}";
    return os;
  }

  os << "root_node=";
  const auto root_node = tree.root_node();
  os << root_node << "}";
  const auto child_count = root_node.child_count();
  if (child_count == 0) {
    return os;
  }

  os << '\n';
  for (uint32_t i = 0; i < child_count; ++i) {
    printRec(os, root_node, i, 1);
  }

  return os;
}

auto kero::ts::Tree::null() noexcept -> Tree {
  return Tree{TSTreePtr{nullptr}};
}

// Logger
// --------

auto logger_log(void *logger, TSLogType log_type, const char *buffer) noexcept
    -> void {
  assert(logger != nullptr && "logger_log: logger is null");
  static_cast<Logger *>(logger)->log(log_type, buffer != nullptr ? buffer : "");
}

kero::ts::Logger::Logger() noexcept : ts_logger_{this, logger_log} {}

auto kero::ts::Logger::as_raw() const noexcept -> const TSLogger {
  return ts_logger_;
}

auto kero::ts::Logger::null_ts_logger() noexcept -> TSLogger {
  return TSLogger{nullptr, nullptr};
}

// ConsoleLogger
// --------

auto kero::ts::ConsoleLogger::log(const TSLogType log_type,
                                  const std::string_view buffer) const noexcept
    -> void {
  std::cout << "Log{";
  std::cout << "log_type=";
  switch (log_type) {
  case TSLogTypeParse:
    std::cout << "Parse";
    break;
  case TSLogTypeLex:
    std::cout << "Lex";
    break;
  }
  std::cout << ", ";
  std::cout << "buffer=\"";
  std::cout << buffer;
  std::cout << "\"}\n";
}

// TSParserDeleter
// --------

void kero::ts::TSParserDeleter::operator()(TSParser *parser) const noexcept {
  ts_parser_print_dot_graphs(parser, Parser::close_file_descriptor);
  ts_parser_delete(parser);
}

// Parser
// --------

kero::ts::Parser::Parser() noexcept : parser_{ts_parser_new()} {}

auto kero::ts::Parser::language() const noexcept -> const TSLanguage * {
  assert(!is_null() && "Parser::language: parser is null");
  return ts_parser_language(parser_.get());
}

auto kero::ts::Parser::set_language(const TSLanguage *language) const noexcept
    -> bool {
  assert(!is_null() && "Parser::set_language: parser is null");
  return ts_parser_set_language(parser_.get(), language);
}

auto kero::ts::Parser::parse_string(
    Tree &&old_tree, const std::string_view string) const noexcept -> Tree {
  assert(!is_null() && "Parser::parse_string: parser is null");
  const auto old_tree_raw = old_tree.into_raw();
  const auto new_tree = ts_parser_parse_string(
      parser_.get(), old_tree_raw.get(), string.data(), string.size());
  return Tree{TSTreePtr{new_tree}};
}

auto kero::ts::Parser::set_timeout_micros(
    const uint64_t timeout_micros) const noexcept -> void {
  assert(!is_null() && "Parser::set_timeout_micros: parser is null");
  ts_parser_set_timeout_micros(parser_.get(), timeout_micros);
}

auto kero::ts::Parser::timeout_micros() const noexcept -> uint64_t {
  assert(!is_null() && "Parser::timeout_micros: parser is null");
  return ts_parser_timeout_micros(parser_.get());
}

auto kero::ts::Parser::enable_cancellation() noexcept -> void {
  assert(!is_null() && "Parser::enable_cancellation: parser is null");
  if (cancellation_flag_.get() != nullptr) {
    return;
  }
  cancellation_flag_ = std::make_unique<size_t>(0);
  ts_parser_set_cancellation_flag(parser_.get(), cancellation_flag_.get());
}

auto kero::ts::Parser::cancel() noexcept -> void {
  assert(!is_null() && "Parser::cancel: parser is null");
  assert(cancellation_flag_.get() != nullptr &&
         "Parser::cancel: cancellation_flag is null. Please enable "
         "cancellation before canceling.");
  *cancellation_flag_ = 1;
}

auto kero::ts::Parser::disable_cancellation() noexcept -> void {
  assert(!is_null() && "Parser::disable_cancellation: parser is null");
  if (cancellation_flag_.get() == nullptr) {
    return;
  }
  ts_parser_set_cancellation_flag(parser_.get(), nullptr);
  cancellation_flag_.reset();
}

auto kero::ts::Parser::set_logger(LoggerPtr &&logger) noexcept -> void {
  assert(!is_null() && "Parser::set_logger: parser is null");
  assert(logger.get() != nullptr && "Parser::set_logger: logger is null");
  logger_ = std::move(logger);
  ts_parser_set_logger(parser_.get(), logger_->as_raw());
}

auto kero::ts::Parser::access_logger() const noexcept -> const LoggerPtr & {
  assert(!is_null() && "Parser::access_logger: parser is null");
  assert(logger_.get() != nullptr && "Parser::access_logger: logger is null");
  return logger_;
}

auto kero::ts::Parser::take_logger() noexcept -> LoggerPtr {
  assert(!is_null() && "Parser::take_logger: parser is null");
  assert(logger_.get() != nullptr && "Parser::take_logger: logger is null");
  ts_parser_set_logger(parser_.get(), Logger::null_ts_logger());
  return std::move(logger_);
}

auto kero::ts::Parser::print_dot_graphs(
    const int file_descriptor) const noexcept -> void {
  assert(!is_null() && "Parser::print_dot_graphs: parser is null");
  assert(file_descriptor != 0 &&
         "Parser::print_dot_graphs: You cannot use the stdin file descriptor "
         "directly. Close file descriptor when parser is deleted. Please use "
         "it after replication.");
  assert(file_descriptor != 1 &&
         "Parser::print_dot_graphs: You cannot use the stdout file descriptor "
         "directly. Close file descriptor when parser is deleted. Please use "
         "it after replication.");
  assert(file_descriptor != 2 &&
         "Parser::print_dot_graphs: You cannot use the stderr file descriptor "
         "directly. Close file descriptor when parser is deleted. Please use "
         "it after replication.");
  ts_parser_print_dot_graphs(parser_.get(), file_descriptor);
}

auto kero::ts::Parser::is_null() const noexcept -> bool {
  return parser_.get() == nullptr;
}
