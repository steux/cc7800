/*
    cc7800 - a subset of C compiler for the Atari 7800
    Copyright (C) 2023 Bruno STEUX 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact info: bruno.steux@gmail.com
*/

use cc6502::Args;
use cc6502::compile::compile;

use std::fs::File;
use std::io;
use std::io::BufReader;

use clap::Parser;

mod build;
use build::build_cartridge;

fn main() {
    env_logger::init();
    let args = Args::parse();
    if args.version {
        const VERSION: &str = env!("CARGO_PKG_VERSION");
        println!("cc7800 v{} - a subset of C compiler targetting the Atari 7800 ProSystem console", VERSION);
        std::process::exit(0); 
    }
    
    let mut writer = match File::create(&args.output) {
        Ok(file) => file,
        Err(err) => {
            eprintln!("{}", err);
            std::process::exit(1);
        }
    };

    if args.input == "stdin" {
        let reader = io::stdin().lock();
        match compile(reader, &mut writer, &args, build_cartridge) {
            Err(e) => {
                eprintln!("{}", e);
                std::process::exit(1) 
            },
            Ok(_) => std::process::exit(0) 
        }
    } else {
        let f = match File::open(&args.input) {
            Ok(file) => file,
            Err(err) => {
                eprintln!("{}", err);
                std::process::exit(1);
            }
        };
        let reader = BufReader::new(f);
        match compile(reader, &mut writer, &args, build_cartridge) {
            Err(e) => {
                eprintln!("{}", e);
                std::process::exit(1) 
            },
            Ok(_) => std::process::exit(0) 
        }
    }
}
