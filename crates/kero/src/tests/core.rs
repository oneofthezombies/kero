use crate::{KeroParser, Rule};
use pest::Parser;

pub(crate) fn ok(input: &str) {
    KeroParser::parse(Rule::module, input).unwrap();
}

pub(crate) fn err(input: &str) {
    KeroParser::parse(Rule::module, input).unwrap_err();
}
