# Colors

The 7800 ProSystem has eight 3-color palettes plus a background color, totalling 25 colors from a palette of 256.

By default, cc7800 will use mode 160A where each sprite is using a single 3-color palette.

Colors are defined as follows:

```
*BACKGROUND = multisprite_color(0x34);

*P0C1 = multisprite_color(0x1c);
*P0C2 = multisprite_color(0xc5);
*P0C3 = multisprite_color(0xcd);

*P1C1 = 0x0f;
*P1C2 = multisprite_color(0x9D);
*P1C3 = multisprite_color(0x97);
...
```

It is recommended to use `multisprite_color()` so that the color works the same whether on NTSC or PAL systems.

## Various modes

 - 320B mode is trickier than it looks at first. It's not just a 3 color mode with transparency. 
 C1 is only displayed when you combine it with another color (from what I remember. See the color table attached). C1+C1 doesn't appear but is transparent (expect in Kangaroo mode where transparency is disabled), which is very annoying and quite limiting.

- 320D is limited to 1 color in the sprites tool, and I'm afraid this will stay as it is. Indeed, 
the behaviour of 320D is completely strange, since it depends on the value of P0 & P1, isi.e values in the palette, not the drawing itself. Indeed, when P0=0 and P1=0, 320D is like 320A (with a choice of only 2 colors instead of 8). When P0 or P1 = 1, 320D mixes colors to make stripes, which can occasionally be useful but that can't fit in sprites7800...
320C mode on the other hand is very useful. For games in high resolution, tha 320A/320C combination is the safe choice.
It provides more colors (9 colors including background) and way more consistency than then 320B/320D combination 
where both 320B and 320D are kind of flawed and offers only  7 colors including background. 

- 320C in contrary to 320D is very clear and well supported by sprites7800. It's just that for 
each 4 pixels represented by 1 byte, the 2 left pixels have the same colors and the 2 right 
pixels have another color. So it's a 320 pixels graphics resolution with 160 pixels colors 
resolution. sprites7800 checks that you enforce this restriction and generates the right coding. 
And as 320A (they share the same write mode), only C2 of all 8 palettes are used, 
which yields a 8 colors + background mode, just like 320A. 
It's a good graphics mode, easy to handle. 


