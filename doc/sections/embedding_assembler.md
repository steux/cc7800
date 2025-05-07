When embedding assembler, _cc7800_ needs to know the size of the code (as _cc7800_ is making a

layout of the code that mixes sprites / code / data). 
When you don't provide it, _cc7800_ "estimates" a code size of 3 bytes per line 
(pure rule of thumb), which is way less than what you have here (due to your tables). 
This results in a bad layout that DASM can't compile.

In order to solve this issue, you have to indicate the size of your assembler code to _cc7800_.
When using the _"asm"_ intrinsics, just indicate the size as a parameter to asm. 
For instance, `asm("jsr xxx", 3)` instead of `asm("jsr xxx")`. 
When including an _.asm_ file, just put `; codesize: xxx` at the beginning of the file
and _cc7800_ will be happy and produce a correct layout. 
You get the codesize by compiling your _.asm_ file separately with DASM.
