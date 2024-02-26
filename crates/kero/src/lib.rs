use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "kero.pest"]
pub struct KeroParser;

#[cfg(test)]
mod tests {
    use super::*;

    fn ok(input: &str) {
        KeroParser::parse(Rule::module, input).unwrap();
    }

    fn err(input: &str) {
        KeroParser::parse(Rule::module, input).unwrap_err();
    }

    #[test]
    fn empty() {
        ok("");
        ok(" ");
    }

    #[test]
    fn binary_int() {
        ok("0b0");
        ok("0b1");
        ok("0b10");
        ok("0b01");
        err("0b1_0");
    }

    #[test]
    fn octal_int() {
        ok("0o0");
        ok("0o1");
        ok("0o12");
        ok("0o01");
        err("0o1_2");
    }

    #[test]
    fn hex_int() {
        ok("0x0");
        ok("0x1");
        ok("0x12");
        ok("0x01");
        err("0x1_2");
        err("0xg");
        ok("0xabcdef");
    }

    #[test]
    fn decimal_int() {
        ok("0");
        ok("1");
        ok("12");
        err("01");
        err("1_2");
    }

    #[test]
    fn adds() {
        ok("1+2");
        ok("1 + 2");
        ok("1  +  2");
        ok("1+ 2");
        ok("1 +2");
    }

    #[test]
    fn subs() {
        ok("1-2");
        ok("1 - 2");
        ok("1  -  2");
        ok("1- 2");
        ok("1 -2");
    }

    #[test]
    fn muls() {
        ok("1*2");
        ok("1 * 2");
        ok("1  *  2");
        ok("1* 2");
        ok("1 *2");
    }

    #[test]
    fn divs() {
        ok("1/2");
        ok("1 / 2");
        ok("1  /  2");
        ok("1/ 2");
        ok("1 /2");
    }

    #[test]
    fn modulos() {
        ok("1%2");
        ok("1 % 2");
        ok("1  %  2");
        ok("1% 2");
        ok("1 %2");
    }
}
