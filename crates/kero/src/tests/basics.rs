use super::core::{err, ok};

#[test]
fn empty() {
    ok("");
    ok(" ");
}

#[test]
fn bin_int() {
    ok("0b0");
    ok("0b1");
    ok("0b10");
    ok("0b01");
    err("0b1_0");
}

#[test]
fn oct_int() {
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
fn dec_int() {
    ok("0");
    ok("1");
    ok("12");
    err("01");
    err("1_2");
}

#[test]
fn pos_int() {
    ok("0");
    ok("1");
    ok("12");
    err("01");
    err("1_2");
}

#[test]
fn neg_int() {
    ok("-0");
    ok("-1");
    ok("-12");
    err("-01");
    err("-1_2");
    ok("-0b0");
    ok("-0b1");
    ok("-0b10");
    ok("-0b01");
    err("-0b1_0");
    ok("-0o0");
    ok("-0o1");
    ok("-0o12");
    ok("-0o01");
    err("-0o1_2");
    ok("-0x0");
    ok("-0x1");
    ok("-0x12");
    ok("-0x01");
    err("-0x1_2");
}

#[test]
fn int() {
    ok("0");
    ok("1");
    ok("12");
    err("01");
    err("1_2");
    ok("-0");
    ok("-1");
    ok("-12");
    err("-01");
    err("-1_2");
    ok("-0b0");
    ok("-0b1");
    ok("-0b10");
    ok("-0b01");
    err("-0b1_0");
    ok("-0o0");
    ok("-0o1");
    ok("-0o12");
    ok("-0o01");
    err("-0o1_2");
    ok("-0x0");
    ok("-0x1");
    ok("-0x12");
    ok("-0x01");
    err("-0x1_2");
}

#[test]
fn add() {
    ok("1+2");
    ok("1 + 2");
    ok("1  +  2");
    ok("1+ 2");
    ok("1 +2");
}

#[test]
fn sub() {
    ok("1-2");
    ok("1 - 2");
    ok("1  -  2");
    ok("1- 2");
    ok("1 -2");
}

#[test]
fn mul() {
    ok("1*2");
    ok("1 * 2");
    ok("1  *  2");
    ok("1* 2");
    ok("1 *2");
}

#[test]
fn div() {
    ok("1/2");
    ok("1 / 2");
    ok("1  /  2");
    ok("1/ 2");
    ok("1 /2");
}

// #[test]
// fn modulo() {
//     ok("1%2");
//     ok("1 % 2");
//     ok("1  %  2");
//     ok("1% 2");
//     ok("1 %2");
// }
