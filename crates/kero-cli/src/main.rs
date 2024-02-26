use clap::{
    builder::{styling::AnsiColor, Styles},
    Parser,
};

fn get_styles() -> Styles {
    Styles::styled()
        .header(AnsiColor::BrightGreen.on_default().bold())
        .usage(AnsiColor::BrightGreen.on_default().bold())
        .literal(AnsiColor::BrightCyan.on_default().bold())
        .placeholder(AnsiColor::Cyan.on_default())
}

#[derive(Parser)]
#[command(name = "kero")]
#[command(bin_name = "kero")]
#[command(arg_required_else_help = true)]
#[command(styles = get_styles())]
#[command(author, version, about, long_about=None)]
struct Cli {
    file: Option<String>,

    #[arg(short, long)]
    #[arg(help = "Command to run")]
    command: Option<String>,
}

fn main() {
    let cli = Cli::parse();

    if let Some(file) = cli.file {
        println!("file: {}", file);
        return;
    }

    if let Some(command) = cli.command {
        println!("command: {}", command);
    }
}
