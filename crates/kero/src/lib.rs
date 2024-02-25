use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "kero.pest"]
pub struct KeroParser;

fn parse() {
    KeroParser::parse(Rule::module, "").unwrap();
    KeroParser::parse(Rule::decimal_integer, "0").unwrap();
    KeroParser::parse(Rule::decimal_integer, "1").unwrap();
    KeroParser::parse(Rule::decimal_integer, "12").unwrap();
    KeroParser::parse(Rule::decimal_integer, "01").unwrap_err();
    // KeroParser::parse(Rule::decimal_integer, "1_2").unwrap_err();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse() {
        parse();
    }
}
