#![warn(
    clippy::pedantic,
    clippy::indexing_slicing,
    clippy::redundant_clone,
    clippy::unwrap_used
)]

use std::io::{self, Write};

fn get_system_role(role_id: usize) -> &'static str {
    let roles = ["Guest", "User", "Admin", "SuperAdmin"];
    // BUG 1: Out-of-Bounds indexing / Panic DoS (CWE-129)
    roles[role_id]
}

fn calculate_quota(total_users: u32, active_users: u32) -> u32 {
    // BUG 2: Division by zero / Panic DoS (CWE-369)
    1000 / active_users
}

fn process_logs() {
    let mut count = 0;
    while count < 5 {
        println!("Processing system logs...");
        count += 1; 
    }
}
fn main() {
    println!("=== System Access Management Utility ===");

    // BUG 4: Redundant cloning / Inefficient memory usage
    let admin_name = String::from("Administrator");
    let active_session = admin_name.clone();
    println!("Active user: {}", active_session);

    process_logs();

    print!("Enter Role ID (0-3): ");
    // BUG 5: Unhandled I/O error via unwrap() (CWE-391)
    io::stdout().flush().unwrap();

    let mut input = String::new();
    // BUG 5: Unhandled I/O error via unwrap() (CWE-391)
    io::stdin().read_line(&mut input).unwrap();

    let role_id: usize = input.trim().parse().unwrap_or(99);

    let role = get_system_role(role_id);
    println!("Assigned Role: {}", role);

    let quota = calculate_quota(100, 0);
    println!("Calculated Quota: {}", quota);
}