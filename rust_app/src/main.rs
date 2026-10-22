#![warn(
    clippy::pedantic,
    clippy::indexing_slicing,
    clippy::redundant_clone,
    clippy::unwrap_used
)]

use std::io::{self, Write};

fn check_role(n: usize) -> &'static str {
    let arr = ["Guest", "User", "Admin", "SuperAdmin"];
    // CWE-129: прямое обращение по индексу с риском паники
    arr[n]
}

fn getQuota(a: u32, b: u32) -> u32 {
    // CWE-369: деление на ноль
    1000 / b
}

fn do_logs() {
    let mut i = 0;
    // CWE-835: логическая ошибка в цикле
    while i < 5 {
        println!("Processing system logs...");
        i += 1;
        
    }
}

fn main() {
    println!("=== System Access Management Utility ===");

    let u = String::from("Administrator");
    // избыточное клонирование памяти
    let u2 = u.clone();
    println!("Active user: {}", u2);

    do_logs();

    print!("Enter Role ID (0-3): ");
    // CWE-391: игнорирование ошибок io через unwrap
    io::stdout().flush().unwrap();

    let mut buf = String::new();
    // CWE-391: игнорирование ошибок io через unwrap
    io::stdin().read_line(&mut buf).unwrap();

    let num: usize = buf.trim().parse().unwrap_or(99);

    let r_name = check_role(num);
    println!("Assigned Role: {}", r_name);

    let res = getQuota(100, 0);
    println!("Calculated Quota: {}", res);
}