use anyhow::anyhow;
use anyhow::Context;
use anyhow::Result;

fn no_exist_read() -> Result<()> {
    std::fs::read("no_exist_file")
        .map(|_| return ())
        .with_context(|| "failed to read")?;
    Ok(())
}

fn main() -> Result<()> {
    println!("hello");
    let err = no_exist_read().unwrap_err();
    println!("error display {}", err);
    println!("error debug {:?}", err);
    println!("root_cause {}", err.root_cause());
    println!("backtrace {}", err.backtrace());
    match err.downcast_ref::<std::io::Error>() {
        Some(v) => println!("downcast ok {}", v),
        None => println!("downcast error"),
    }
    for error in err.chain() {
        println!("chain {}", error);
    }
    return Ok(());
}
