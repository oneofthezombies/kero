// TODO: temporary allow empty_docs
#![allow(clippy::empty_docs)]

use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "kero.pest"]
pub struct KeroParser;

mod arithmetic;

#[cfg(test)]
mod tests;
