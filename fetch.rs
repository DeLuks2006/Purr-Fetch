//bin/true; rustc -o "/tmp/$0.bin" 1>&2 "$0" && "/tmp/$0.bin" "$@"; exit 0;

use std::fs::File;
use std::io::prelude::*;

fn main() {
    let shell = std::env::var("SHELL").unwrap();

    // Please simplify this code, im fucking bad at rust
    // but atleast the uptime is correct now :p
    let mut upfile = File::open("/proc/uptime").unwrap(); // Read uptime from /proc/uptime (idk if this is in all distros but i guess so
    let mut uptime = String::new();
    upfile.read_to_string(&mut uptime).unwrap(); // Put uptime file text into uptime variable
    let v: Vec<&str> = uptime.split(" ").collect(); // Split uptime, because it has more than just the seconds
    let upsecs = v[0].parse::<f32>().unwrap(); // Parse floating number from index 0, cuz we need that to "beautify" it
    let secs = upsecs % 60.0; // calculate the seconds
    let mins = (upsecs / 60.0) % 60.0; // calculate the minutes
    let uptime = format!("{mins:.0}m {secs:.1}s"); // mak it butiful

    let mut file = File::open("/etc/hostname").unwrap();
    let mut hostname = String::new();
    file.read_to_string(&mut hostname).unwrap(); //.strip()
    let hostname = hostname.replace("\n", "");

    let mut file = File::open("/etc/issue").unwrap();
    let mut distro = String::new();
    file.read_to_string(&mut distro).unwrap(); //.strip()
    let distro = distro.replacen("(\\l)", "", 3).replace("\r", "").replace("\n", "");

    let mut file = File::open("/proc/sys/kernel/ostype").unwrap(); // Read OS Type (should be "Linux")
    let mut ostype = String::new();
    file.read_to_string(&mut ostype).unwrap();
    let mut file = File::open("/proc/sys/kernel/osrelease").unwrap(); // Read OS Release (should be the kernel version)
    let mut osrelease = String::new();
    file.read_to_string(&mut osrelease).unwrap();
    let kernel = format!("{} {}", ostype.replace("\n", ""), osrelease.replace("\n", ""));
    
    
    // probably a bit more involved
    // # terminal = os.ctermid()

    println!();
    println!("(\\_/) \x1b[0;33m     uptime:      {uptime}\x1b[0;0m"); //orange
    println!("(oᴥo) \x1b[0;31m     shell:       {shell}\x1b[0;0m"); //red
    println!("|U°U| \x1b[0;35m     distro:      {distro}\x1b[0;0m"); //purple
    println!("|   | \x1b[0;34m     hostname:    {hostname}\x1b[0;0m"); //blue
    println!("'U_U' \x1b[0;36m     kernel:      {kernel}\x1b[0;0m"); //cyan
    println!("  U" );
}
