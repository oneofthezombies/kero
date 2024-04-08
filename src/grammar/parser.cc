#include "parser.h"

using namespace kero::grammar;

int kero::grammar::Parser::pccGetChar() noexcept { return 0; }

void kero::grammar::Parser::pccError() noexcept {}

void kero::grammar::Parser::pccDebug(int event, const char *rule, size_t level,
                                     size_t pos, const char *buffer,
                                     size_t length) noexcept {}
