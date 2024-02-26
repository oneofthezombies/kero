use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "kero.pest"]
pub struct KeroParser;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn decimal_int() {
        KeroParser::parse(Rule::module, "").unwrap();
        KeroParser::parse(Rule::module, "0").unwrap();
        KeroParser::parse(Rule::module, "1").unwrap();
        KeroParser::parse(Rule::module, "12").unwrap();
        KeroParser::parse(Rule::module, "01").unwrap_err();
        KeroParser::parse(Rule::module, "1_2").unwrap_err();
    }

    #[test]
    fn adds() {
        KeroParser::parse(Rule::module, "1+2").unwrap();
        KeroParser::parse(Rule::module, "1 + 2").unwrap();
        KeroParser::parse(Rule::module, "1  +  2").unwrap();
        KeroParser::parse(Rule::module, "1+ 2").unwrap();
        KeroParser::parse(Rule::module, "1 +2").unwrap();
    }

    #[test]
    fn subs() {
        KeroParser::parse(Rule::module, "1-2").unwrap();
        KeroParser::parse(Rule::module, "1 - 2").unwrap();
        KeroParser::parse(Rule::module, "1  -  2").unwrap();
        KeroParser::parse(Rule::module, "1- 2").unwrap();
        KeroParser::parse(Rule::module, "1 -2").unwrap();
    }

    #[test]
    fn muls() {
        KeroParser::parse(Rule::module, "1*2").unwrap();
        KeroParser::parse(Rule::module, "1 * 2").unwrap();
        KeroParser::parse(Rule::module, "1  *  2").unwrap();
        KeroParser::parse(Rule::module, "1* 2").unwrap();
        KeroParser::parse(Rule::module, "1 *2").unwrap();
    }

    #[test]
    fn divs() {
        KeroParser::parse(Rule::module, "1/2").unwrap();
        KeroParser::parse(Rule::module, "1 / 2").unwrap();
        KeroParser::parse(Rule::module, "1  /  2").unwrap();
        KeroParser::parse(Rule::module, "1/ 2").unwrap();
        KeroParser::parse(Rule::module, "1 /2").unwrap();
    }
}
