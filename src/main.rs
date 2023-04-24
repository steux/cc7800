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

fn main() -> Result<(), std::io::Error> {
    env_logger::init();
    let args = Args::parse();
    if args.version {
        const VERSION: &str = env!("CARGO_PKG_VERSION");
        println!("cc7800 v{} - a subset of C compiler targetting the Atari 7800 ProSystem console", VERSION);
        std::process::exit(0); 
    }
    
    let filename = if args.assembler_output {
        &args.output
    } else {
        "out.tmp"
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
        if let Err(e)  = compile(reader, &mut writer, &args, build_cartridge) {
            eprintln!("{}", e);
            std::process::exit(1) 
        }
    }

    if !args.assembler_output {
        // Call DASM to produce the output file
        
        let output = match std::process::Command::new("dasm")
            .arg("out.tmp")
            .arg("-f3")
            .arg(&format!("-o{}", &args.output))
            .output() {
            Ok(x) => x,
            Err(_) => {
                match std::process::Command::new("./dasm")
                    .arg("out.tmp")
                    .arg("-f3")
                    .arg(&format!("-o{}", &args.output))
                    .output() {
                        Ok(x) => x,
                        Err(_) => {
                            match std::process::Command::new("dasm.exe")
                                .arg("out.tmp")
                                .arg("-f3")
                                .arg(&format!("-o{}", &args.output))
                                .output() {
                                    Ok(x) => x,
                                    Err(_) => {
                                        match std::process::Command::new(".\\dasm.exe")
                                            .arg("out.tmp")
                                            .arg("-f3")
                                            .arg(&format!("-o{}", &args.output))
                                            .output() {
                                                Ok(x) => x,
                                                Err(_) => {
                                                    eprintln!("Can't find DASM. Exiting.");
                                                    std::process::exit(1) 
                                                }
                                            }
                                    }
                                }
                        }
                    }
            }
        };

        if output.status.success() {
            if args.verbose {
                println!("Cartridge successfully compiled with DASM");
            }
            std::fs::remove_file("out.tmp")?;
            Ok(())
        } else {
            let err = String::from_utf8(output.stderr).unwrap();
            Err(std::io::Error::new(std::io::ErrorKind::Other, err))
        }
    } else {
        Ok(())
    }
}
