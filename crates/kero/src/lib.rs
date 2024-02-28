use pest::Parser;
use pest_derive::Parser;

/// The parser for the Kero language.
#[derive(Parser)]
#[grammar = "kero.pest"]
pub struct KeroParser;

mod arithmetic;

#[cfg(test)]
mod tests;
