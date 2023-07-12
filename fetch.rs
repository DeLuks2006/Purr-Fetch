//bin/true; rustc -o "/tmp/$0.bin" 1>&2 "$0" && "/tmp/$0.bin" "$@"; exit 0;

use std::fs::File;
use std::io::prelude::*;
use std::time::{SystemTime, UNIX_EPOCH};

fn main() {
    let shell = std::env::var("SHELL").unwrap();

    let start = SystemTime::now();
    let since_the_epoch = start
        .duration_since(UNIX_EPOCH)
        .expect("Time went backwards");

    // println!("{:?}", since_the_epoch);
    let uptime = format!("{since_the_epoch:?}"); // I dunno what exactly we want
    // uptime=time.clock_gettime(time.CLOCK_BOOTTIME)
    // up=str(datetime.timedelta(seconds=uptime)) # 0:00:00.000000

    let mut file = File::open("/etc/hostname").unwrap();
    let mut hostname = String::new();
    file.read_to_string(&mut hostname).unwrap(); //.strip()
    let hostname = hostname.replace("\n", "");

    let mut file = File::open("/etc/issue").unwrap();
    let mut distro = String::new();
    file.read_to_string(&mut distro).unwrap(); //.strip()
    let distro = distro.replace("(\\l)", "").replace("\r", "").replace("\n", "");

    let kernel = std::env::consts::OS;

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
