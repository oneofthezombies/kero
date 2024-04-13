#include "compiler/parser.h"

#include "tree-sitter-kero.h"

using namespace kero::compiler;

void kero::compiler::TSParserDeleter::operator()(
    TSParser *parser) const noexcept {
  ts_parser_delete(parser);
}

void kero::compiler::TSTreeDeleter::operator()(TSTree *tree) const noexcept {
  ts_tree_delete(tree);
}

void kero::compiler::CStringDeleter::operator()(char *str) const noexcept {
  if (str == nullptr) {
    return;
  }
  free(str);
}

kero::compiler::String::String(CStringPtr &&c_str) noexcept
    : c_str_{std::move(c_str)} {}

auto kero::compiler::String::string_view() const noexcept -> std::string_view {
  return std::string_view{c_str_.get()};
}

kero::compiler::Node::Node(TSNode &&node) noexcept : node_{std::move(node)} {}

auto kero::compiler::Node::start_byte() const noexcept -> uint32_t {
  return ts_node_start_byte(node_);
}

auto kero::compiler::Node::start_point() const noexcept -> TSPoint {
  return ts_node_start_point(node_);
}

auto kero::compiler::Node::end_byte() const noexcept -> uint32_t {
  return ts_node_end_byte(node_);
}

auto kero::compiler::Node::end_point() const noexcept -> TSPoint {
  return ts_node_end_point(node_);
}

auto kero::compiler::Node::symbol() const noexcept -> TSSymbol {
  return ts_node_symbol(node_);
}

auto kero::compiler::Node::type() const noexcept -> std::string_view {
  return std::string_view{ts_node_type(node_)};
}

auto kero::compiler::Node::grammar_symbol() const noexcept -> TSSymbol {
  return ts_node_grammar_symbol(node_);
}

auto kero::compiler::Node::grammar_type() const noexcept -> std::string_view {
  return std::string_view{ts_node_grammar_type(node_)};
}

auto kero::compiler::Node::string() const noexcept -> String {
  return String{CStringPtr{ts_node_string(node_)}};
}

auto kero::compiler::Node::eq(const Node &other) const noexcept -> bool {
  return ts_node_eq(node_, other.node_);
}

auto kero::compiler::Node::is_null() const noexcept -> bool {
  return ts_node_is_null(node_);
}

auto kero::compiler::Node::is_extra() const noexcept -> bool {
  return ts_node_is_extra(node_);
}

auto kero::compiler::Node::is_named() const noexcept -> bool {
  return ts_node_is_named(node_);
}

auto kero::compiler::Node::is_missing() const noexcept -> bool {
  return ts_node_is_missing(node_);
}

auto kero::compiler::Node::has_changes() const noexcept -> bool {
  return ts_node_has_changes(node_);
}

auto kero::compiler::Node::has_error() const noexcept -> bool {
  return ts_node_has_error(node_);
}

auto kero::compiler::Node::is_error() const noexcept -> bool {
  return ts_node_is_error(node_);
}

auto kero::compiler::Node::descendant_count() const noexcept -> uint32_t {
  return ts_node_descendant_count(node_);
}

auto kero::compiler::Node::parse_state() const noexcept -> TSStateId {
  return ts_node_parse_state(node_);
}

auto kero::compiler::Node::next_parse_state() const noexcept -> TSStateId {
  return ts_node_next_parse_state(node_);
}

auto kero::compiler::Node::parent() const noexcept -> Node {
  return Node{ts_node_parent(node_)};
}

auto kero::compiler::Node::child(const uint32_t index) const noexcept -> Node {
  return Node{ts_node_child(node_, index)};
}

auto kero::compiler::Node::named_child(const uint32_t index) const noexcept
    -> Node {
  return Node{ts_node_named_child(node_, index)};
}

auto kero::compiler::Node::child_by_field_id(
    const TSFieldId field_id) const noexcept -> Node {
  return Node{ts_node_child_by_field_id(node_, field_id)};
}

auto kero::compiler::Node::child_by_field_name(
    const std::string_view field_name) const noexcept -> Node {
  return Node{
      ts_node_child_by_field_name(node_, field_name.data(), field_name.size())};
}

auto kero::compiler::Node::child_count() const noexcept -> uint32_t {
  return ts_node_child_count(node_);
}

auto kero::compiler::Node::named_child_count() const noexcept -> uint32_t {
  return ts_node_named_child_count(node_);
}

auto kero::compiler::Node::next_sibling() const noexcept -> Node {
  return Node{ts_node_next_sibling(node_)};
}

auto kero::compiler::Node::next_named_sibling() const noexcept -> Node {
  return Node{ts_node_next_named_sibling(node_)};
}

auto kero::compiler::Node::prev_sibling() const noexcept -> Node {
  return Node{ts_node_prev_sibling(node_)};
}

auto kero::compiler::Node::prev_named_sibling() const noexcept -> Node {
  return Node{ts_node_prev_named_sibling(node_)};
}

auto kero::compiler::Node::first_child_for_byte(
    const uint32_t byte) const noexcept -> Node {
  return Node{ts_node_first_child_for_byte(node_, byte)};
}

auto kero::compiler::Node::first_named_child_for_byte(
    const uint32_t byte) const noexcept -> Node {
  return Node{ts_node_first_named_child_for_byte(node_, byte)};
}

auto kero::compiler::Node::descendant_for_byte_range(
    const uint32_t start, const uint32_t end) const noexcept -> Node {
  return Node{ts_node_descendant_for_byte_range(node_, start, end)};
}

auto kero::compiler::Node::named_descendant_for_byte_range(
    const uint32_t start, const uint32_t end) const noexcept -> Node {
  return Node{ts_node_named_descendant_for_byte_range(node_, start, end)};
}

auto kero::compiler::Node::descendant_for_point_range(
    const TSPoint start, const TSPoint end) const noexcept -> Node {
  return Node{ts_node_descendant_for_point_range(node_, start, end)};
}

auto kero::compiler::Node::named_descendant_for_point_range(
    const TSPoint start, const TSPoint end) const noexcept -> Node {
  return Node{ts_node_named_descendant_for_point_range(node_, start, end)};
}

kero::compiler::Tree::Tree(TSTreePtr &&tree) noexcept
    : tree_{std::move(tree)} {}

auto kero::compiler::Tree::empty() const noexcept -> bool { return !tree_; }

auto kero::compiler::Tree::take() noexcept -> TSTreePtr {
  return std::move(tree_);
}

auto kero::compiler::Tree::root_node() const noexcept -> std::optional<Node> {
  if (empty()) {
    return std::nullopt;
  }
  return Node{ts_tree_root_node(tree_.get())};
}

auto kero::compiler::Tree::null() noexcept -> Tree {
  return Tree{TSTreePtr{nullptr}};
}

auto kero::compiler::Parser::Builder::set_timeout_micros(
    const uint64_t timeout_micros) noexcept -> Builder & {
  timeout_micros_ = timeout_micros;
  return *this;
}

std::optional<Parser> kero::compiler::Parser::Builder::build() const noexcept {
  auto parser = TSParserPtr{ts_parser_new()};
  if (!ts_parser_set_language(parser.get(), tree_sitter_kero())) {
    return std::nullopt;
  }

  ts_parser_set_timeout_micros(parser.get(), timeout_micros_);
  auto cancellation_flag = std::make_unique<size_t>(0);
  ts_parser_set_cancellation_flag(parser.get(), cancellation_flag.get());
  return Parser{std::move(parser), std::move(cancellation_flag)};
}

kero::compiler::Parser::Parser(
    TSParserPtr &&parser, std::unique_ptr<size_t> &&cancellation_flag) noexcept
    : parser_{std::move(parser)},
      cancellation_flag_{std::move(cancellation_flag)} {}

kero::compiler::Parser::~Parser() noexcept {}

auto kero::compiler::Parser::parse(const std::string_view source) const noexcept
    -> std::optional<Tree> {
  return parse_incremental(source, Tree::null());
}

auto kero::compiler::Parser::parse_incremental(const std::string_view source,
                                               Tree &&old_tree) const noexcept
    -> std::optional<Tree> {
  auto ts_old_tree = old_tree.take();
  auto tree = ts_parser_parse_string(parser_.get(), ts_old_tree.get(),
                                     source.data(), source.size());
  if (tree == nullptr) {
    return std::nullopt;
  }

  return Tree{TSTreePtr{tree}};
}
