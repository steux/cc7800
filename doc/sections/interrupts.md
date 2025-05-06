# Interrupts

A common practice on many computers and consoles is to change the system properties mid-screen. A prime example on the 7800 would be Crystal Quest, where the game changes the following at the bottom of the HUD:

- It switches from mode 320A to 160A (`*CTRL` variable in cc7800)
- It changes the tileset (`multisprite_set_charbase()`)
- It changes some color palettes

The 7800 allows to setup Display List Interrupts (DLI) that will call your custom code on the last line of the desired horizontal zone(s):

```
multisprite_enable_dli(line)

void interrupt dli() {
    ...
}
```

See [test_nmi.c](../../examples/test_nmi.c)
