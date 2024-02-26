use crate::Rule;
use lazy_static::lazy_static;
use pest::{iterators::Pairs, pratt_parser::PrattParser};

lazy_static! {
    static ref PRATT_PARSER: PrattParser<Rule> = {
        use pest::pratt_parser::{Assoc, Op};

        PrattParser::new()
            .op(Op::infix(Rule::ari_in_op_add, Assoc::Left)
                | Op::infix(Rule::ari_in_op_sub, Assoc::Left))
            .op(Op::infix(Rule::ari_in_op_mul, Assoc::Left)
                | Op::infix(Rule::ari_in_op_div, Assoc::Left))
    };
}

#[derive(Debug, PartialEq)]
pub enum Expr {
    Integer(i32),
    BinOp {
        lhs: Box<Expr>,
        op: Op,
        rhs: Box<Expr>,
    },
}

#[derive(Debug, PartialEq)]
pub enum Op {
    Add,
    Subtract,
    Multiply,
    Divide,
}

pub fn parse_expr(pairs: Pairs<Rule>) -> Expr {
    PRATT_PARSER
        .map_primary(|primary| match primary.as_rule() {
            Rule::int => Expr::Integer(primary.as_str().parse::<i32>().unwrap()),
            rule => unreachable!("Expr::parse expected primary expression, found {rule:?}"),
        })
        .map_infix(|lhs, op, rhs| {
            let op = match op.as_rule() {
                Rule::ari_in_op_add => Op::Add,
                Rule::ari_in_op_sub => Op::Subtract,
                Rule::ari_in_op_mul => Op::Multiply,
                Rule::ari_in_op_div => Op::Divide,
                rule => unreachable!("Expr::parse expected infix operator, found {rule:?}"),
            };
            Expr::BinOp {
                lhs: Box::new(lhs),
                op,
                rhs: Box::new(rhs),
            }
        })
        .parse(pairs)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::KeroParser;
    use pest::Parser;

    #[test]
    fn test_parse_expr() {
        let module = KeroParser::parse(Rule::module, "1 + 2 * 3")
            .unwrap()
            .next()
            .unwrap();
        let stmt = module.into_inner().next().unwrap();
        let expr = stmt.into_inner().next().unwrap();
        let ari_expr = expr.into_inner().next().unwrap();
        let expr = parse_expr(ari_expr.into_inner());
        assert_eq!(
            expr,
            Expr::BinOp {
                lhs: Box::new(Expr::Integer(1)),
                op: Op::Add,
                rhs: Box::new(Expr::BinOp {
                    lhs: Box::new(Expr::Integer(2)),
                    op: Op::Multiply,
                    rhs: Box::new(Expr::Integer(3)),
                }),
            }
        );
    }
}
