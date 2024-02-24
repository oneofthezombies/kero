use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "kero.pest"]
pub struct KeroParser;

fn parse() {
    let successful_parse = KeroParser::parse(Rule::field, "-273.15");
    println!("{:?}", successful_parse);

    let unsuccessful_parse = KeroParser::parse(Rule::field, "this is not a number");
    println!("{:?}", unsuccessful_parse);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse() {
        parse();
    }
}
