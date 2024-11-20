<p align="center">
  <img width="50%" src="https://github.com/steux/cc7800/raw/main/misc/cc7800.png" />
</p>

# cc7800

cc7800 implements a subset of C compiler for Atari 7800. The main goal of cc7800 is to enable making games for the Atari 7800
using C language, including fast filling of Maria display lists, not to provide full C support for the 6502 
(have a look at cc65 if this is what you are looking for). Any code written for cc7800 can be compiled with gcc, but not
the other way round... The 6502 processor is famous for being an inefficient target for C compilers, due to its poor
stack support, its infamous indexing modes and its lack of registers. cc7800 tries to cope with these limitations by not strictly
implementing all C features but mapping C syntax to the specifics of 6502, in particular 6502 X/Y indexing modes.

cc7800 is implemented in the Rust programming language, a touch of modernity for an almost 40 years old console... The C language grammar has been handwritten from scratch as a PEG grammar, so don't expect any ANSI or ISO C compliance.  

## Main features


- Produces DASM compatible code ([DASM](https://github.com/dasm-assembler/dasm) is required as a second stage compiler) 
- Uses only 1 byte of RAM
- Local variables and function parameters make smart usage of zeropage memory.
- Scattering of ROM data is supported through the scattered keyword, which greatly simplifies the use of Holey DMA and sprite
  data layout.
- X and Y registers are directly mapped to X and Y variables, just like if they were declared as unsigned char global variables.
- All C constructs are implemented (for, if, while, goto, etc).
- Supports SuperGame bankswitching (including EXROM) and extra RAM on cart
- Clean bootstrap code is automatically generated

## Known limitations


- The only data types supported are char (8-bit), short (16-bit) and char pointers (16-bits), and one dimensional arrays of these types.
- Array subscripts are preferably constants, X and Y variables / registers (performance penalty or error in case of too complex subscript)
- 16-bits arithmetics is severly constrained. Generated code may generate an error if too complex (carry propagation check).
- No 32-bits operations, no floating point.
- Works with one C file. No linking provided. Use `#include "other_file.c"` to cope with this.
- Functions are not reentrant, since cc7800 doesn't use the stack for parameters passing.

## How to install

Installing from source is quite straightforward when Rust Cargo is available on your platform. If this is not the case, please
use [rustup](https://www.rust-lang.org/tools/install) to install it, then use `cargo install --path .` in the root
directory to compile and install cc7800 locally.

You can install the binary directly using Cargo by typing `cargo install cc7800`

If you definitely don't want to install Rust (quite a shame), a Windows installer will be provided in the coming years.

## Examples of code using cc7800

A few examples are available in the `examples` directory. To compile HelloWorld, please type in the root directory : 

`cc7800 -Iheaders examples/test_helloworld.c`

This will produce `a.out`, which is an atari 7800 cartridge with .a78 header. Note that running cc7800 requires that DASM is installed in the current directory or can be found in the system's path.

The `a.out` file can be executed with the `a7800` emulator by typing `a7800 a7800 -cart a.out`, or copied directly on a
Concerto cart.

## Technical details

### Atari 7800 specific keywords

In order to deal with the very special Atari 7800 memory mapping, some specific keywords have been added to
the standard C language. These keywords are `scattered`, `holeydma`, `reversed`, `ramchip` and `bankX`.
Please look at the examples to understand how/where to use these keywords.

### Intrinsics

cc7800 supports a few intrinsics to help making ASM-like tuned code :

- `load(expr)` loads the 6502 accumulator with `expr`. It implements a `LDA` isntruction.

- `store(expr)` stores `expr` into the accumulator. It implements a `STA` isntruction.

- `strobe(pointer)` implements a `STA` instruction also. It's just the same as store, but accepts only pointers. Typically used for your numerous `strobe(WSYNC)` instructions in your kernel...

- `asm(string)` inlines the given assembler instruction into the C code. Particularly useful to call ASM function (use `asm("jsr asm_function")`).

### 16-bits arithmetics support

16-bits arithmetics is supported, BUT beware to use only simple expressions (like a simple addition, or `+=`, not multiple additions on the same line of code), since carry propagation is not ensured (maybe will it be in the future). In particular 16-bits operations are not supported in comparisons. Use `short` to declare a 16-bits variable. `char *` are also 16-bits variables, since address space on 6502 is 16-bits wide.

In order to convert from 16-bits to 8-bits, use the `>> 8` special operation to get the higher byte of a `short`, and use nothing to get the lower byte.

### Optimizations

X and Y are `unsigned char` typed, BUT in order to optimize the loops, they are considered `signed char` when compared to 0. Hence the code `do { something; Y-- } while (Y >= 0);` will be implemented with a `BPL` (branch if plus) instruction, just like you would do in assembler. Beware then that if Y >= 128, due to the complement-to-2 binary representation, it will be considered negative number and the loop will exit immediately.

## TODO

- [X] Fix issues with Atari 7800 memory mapping
- [ ] Provide more examples
- [X] Add bankswitching support
- [ ] Add banksets support
- [ ] Create a high level library to handle text, graphics, tiles, multisprite, etc
- [ ] Fix 16 bits arithmetics so that it becomes more usable...

