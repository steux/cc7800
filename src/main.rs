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

// DONE Add different verbosity levels

use cc6502::compile::compile;
use cc6502::Args;

use std::fs::File;
use std::io;
use std::io::BufReader;
use std::path::Path;

use clap::Parser;

use regex::Regex;

mod build;
use build::build_cartridge;

fn main() -> Result<(), std::io::Error> {
    env_logger::init();
    let args = Args::parse();
    if args.version {
        const VERSION: &str = env!("CARGO_PKG_VERSION");
        println!(
            "cc7800 v{} - a subset of C compiler targetting the Atari 7800 ProSystem console",
            VERSION
        );
        std::process::exit(0);
    }

    let prefix = Path::new(&args.output).file_stem().unwrap();
    let mut assembler_filename = String::from(prefix.to_str().unwrap());
    assembler_filename.push_str(".a");

    let filename = if args.assembler_output {
        args.output.clone()
    } else {
        assembler_filename.clone()
    };

    let mut writer = File::create(filename)?;

    if args.input == "stdin" {
        let reader = io::stdin().lock();
        if let Err(e) = compile(reader, &mut writer, &args, build_cartridge) {
            eprintln!("{}", e);
            std::process::exit(1)
        }
    } else {
        let f = File::open(&args.input)?;
        let reader = BufReader::new(f);
        if let Err(e) = compile(reader, &mut writer, &args, build_cartridge) {
            eprintln!("{}", e);
            std::process::exit(1)
        }
    }

    if !args.assembler_output {
        // Call DASM to produce the output file
        let filenames = ["dasm", "./dasm", "dasm.exe", ".\\dasm.exe"];
        let mut output = None;
        for f in filenames {
            let command = if args.debug {
                let mut lst_filename = String::from(prefix.to_str().unwrap());
                lst_filename.push_str(".lst");
                let mut sym_filename = String::from(prefix.to_str().unwrap());
                sym_filename.push_str(".sym");
                std::process::Command::new(f)
                    .arg(assembler_filename.clone())
                    .arg("-f3")
                    .arg(&format!("-o{}", &args.output))
                    .arg(&format!("-l{}", &lst_filename))
                    .arg(&format!("-s{}", &sym_filename))
                    .output()
            } else {
                std::process::Command::new(f)
                    .arg(assembler_filename.clone())
                    .arg("-f3")
                    .arg(&format!("-o{}", &args.output))
                    .output()
            };
            if let Ok(x) = command {
                output = Some(x);
                break;
            }
        }
        if output.is_none() {
            eprintln!("Can't find DASM. Exiting.");
            std::process::exit(1)
        }

        let output = output.unwrap();
        if output.status.success() {
            if args.verbose {
                println!("Cartridge successfully compiled with DASM");
            }
            if !args.debug {
                std::fs::remove_file(&assembler_filename)?;
            }
            Ok(())
        } else {
            let err = String::from_utf8(output.stdout).unwrap();
            let re = Regex::new(r"(-\d+ bytes free in bank \d)").unwrap();
            if let Some(caps) = re.captures(&err) {
                eprintln!("Out of memory: {}", &caps[0]);
            } else {
                eprintln!("{}", err);
            }
            std::process::exit(1)
        }
    } else {
        Ok(())
    }
}
