# Memory

There might be a point where cc7800 complains about "Memory full" when the program starts to grow, e.g.

```
Compiler error: Bad configuration - Memory full. Zeropage Atari 7800 RAM is limited to 192 bytes
Compiler error: Bad configuration - Memory full. Internal Atari 7800 RAM is limited to 4KB
Compiler error: Bad configuration - Memory full. Linear ROM size is limited to 52KB (ideally 48KB for high scores save cart compatibility)
Compiler error: Bad configuration - Memory full. Not enough ROM memory in bank #0
```

## "Zeropage Atari 7800 RAM is limited to 192 bytes"

The first 256 bytes of the 6502 (called Zeropage) have the fastest access time. These are mapped to its own RAM. However, some of it is used by the stack and cc7800, so only 192 bytes are available to you.

The only way around this error is to move some of the variables to the 7800 RAM by using the `ramchip` keyword (e.g. `ramchip unsigned char my_variable;`)

## "Internal Atari 7800 RAM is limited to 4KB"

Any variable declared with `ramchip` is stored in the ProSystem 4 Kb of RAM. Unfortunately, the double DLL used by cc7800 occupies its fair share of ramchip.

Make sure to add a `const` in front of any data which is not changed (`const char my_array[32] = { ... };`) so that it is stored in the cart ROM instead of RAM.

If there still isn't enough RAM, a way around it is to use banking (`bank1 char my_array[32]` instead of `ramchip char my_array[32]`). cc7800 will automatically use EXRAM bankswitching (requiring the physical cart to have embedded RAM chip), which will add 16 Kb of RAM at address $4000.

## "Linear ROM size is limited to 52KB"

This occurs when two much code and resources are defined and the total goes beyond 52 Kb.

The way around this is to use bank switching by using the keywords `bank1`, `bank2`, ... `bank9` in either a resource Yaml file, in front of `const` variables or in front of functions, e.g.

```
bank1 const char my_array[32] = { ... };

bank2 void my_function() { ... }
```

Each bank is 16 Kb large. The default bank, bank #0, is now 16 Kb large as well (from address $C000 to $FFFF). All the other banks are stored from address $8000 and $BFFF. If bank #0 is always visible, only one non-default bank is visible at a time.

The way to explicitly switch bank is to use the `ROM_SELECT` keyword (e.g. `*ROM_SELECT=2` to switch to bank #2)

Notes:

- Only code stored in bank #0 should switch bank. Otherwise the 7800 won't be able to read the next instruction
- When calling a function defined in a non-default bank, cc7800 will automatically add the code to switch bank

## "Memory full. Not enough ROM memory in bank #0"

This is typically the first error one gets when using bankswitching, as now less data is available at any one time (32 Kb instead of 52 Kb). Code and data need to be reorganized across banks.

General tips:

- The main function should be in bank #0, most other code can be moved to other banks
- MARIA needs to be able to see any graphical resources it needs to display
- Splash screen or option menus (code and associated graphical resources) can be stored in separate banks
- Graphical resources from different game levels can be spread across multiple banks
- Use `cc7800 -v` to get an indication of how much is stored in each bank
