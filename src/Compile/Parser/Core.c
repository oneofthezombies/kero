#include "Core.h"

const char *KCParserEventToString(const KCParserEvent Event) {
  switch (Event) {
  case KCParserEvent_Evaluate:
    return "Evaluate";
  case KCParserEvent_Match:
    return "Match";
  case KCParserEvent_NoMatch:
    return "NoMatch";
  default:
    return "Unknown";
  }
}
