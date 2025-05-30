Examples for cc7800 
-------------------

To compile (from the cc7800 main directory) :
```
cc7800 -g -v --insert-code -Iheaders -Iexamples examples/XXX.c
```
or from the examples directory :
```
cc7800 -g -v --insert-code -I../headers XXX.c
```

example_multisprite.c
---------------------

Basic usage of the `multisprite.h` header, that provides double buffering sprites display (and much more).
Functions used in this example:
- `multisprite_init`, which sets up a 160x224 double buffer display.
- `multisprite_set_charbase`, which initializes the tiles graphics pointer.
- `multisprite_display_tiles`, which displays a series of tile on screen.
- `multisprite_save`, which saves a background to be used from frame to frame.
- `multisprite_color`, which is a macro that enables PAL/NTSC independant color settings.
- `multisprite_flip`, which flips the screen buffers.
- `multisprite_display_sprite`, which is the standard basic function to display sprites.

example_vertical_scrolling.c
----------------------------

Add a background scrolling to the previous example (macro `VERTICAL_SCROLLING`). 
Vertical scrolling is done through the call to `multisprite_vertical_scrolling`.
A scrolling buffer must be filled when asked for (through the `multisprite_vscroll_buffer_empty` function).
The scrolling buffer is filled through the `multisprite_scroll_buffer_tiles` and
`multisprite_vscroll_buffer_sprite` functions.

An additional feature shown in this example is the DMA control capability (through
the `DMA_CHECK` macro). This enables to reserve some DMA time (through 
`multisprite_reserve_dma`) for drawing something ON TOP of sprites (ensuring that
these sprites won't eat up all DMA). We use `multisprite_display_sprite_fast` for the hello world
text overlay in order to skip the DMA test for this one.

example_score.c
---------------

Adds a top zone to the previous example (macros `_MS_NB_TOP_ZONES` and `_MS_NB_SCROLLING_ZONES`). 
The top zone is not subject to double buffering and sprites are not drawn on it. It must be
manually set by `multisprite_set_top_zone_dl` to which a display list (manually crafted) must be provided. The example
shows how to set this display list to display a score.

example_tiled.c
---------------

This example introduces 3 new concepts : the interaction with Tiled (used to defined the background tiling), 
bidirectionnal vertical scrolling (used here to vertically pan the background tiling) and `multisprite.h`
horizontal scrolling. The latter has very little capabilities : it only scrolls a display list per line, by modifying
the x position of the first element of each display list list. 
Every 8 pixels, the pointer of that display list list element is incremented or decremented wrt
the scrolling direction. It's really only meant to scroll simple backgrounds made of one or two display lists par zone.
For more complex scrolling (i.e. for horizontal shooters), please use `example_horizontal_scrolling.c` which uses
sparse tiling.

example_tiled2.c
----------------

Again a full tiled background display examply, this time very simplified due to the `tiling.h` header. The `tiling_init`
and `tiling_goto` do all the job by simply setting the full background each time it is called (i.e. it's very simple
to use, but not very fast. But anyway full background display on the Atari 7800 is not very fast, due to the Maria chip
architecture. It's also not very nice looking since all tiles must share the same palette). Note that `tiling_goto`
manages correctly out of bounds display. Please consider sparse tiling for better looking background display. 

example_sparse_tiling.c
-----------------------

This example shows how to use Tiled and spare tiling. The idea behind sparse tiling is to not cover all the background
with tiles (due the sparse name), to save DMA/CPU (very important on the Atari 7800, since this is the main 
bottleneck of the machine). Other big advantages of sparse tiling is the possibility to mix palettes and the
ability the mix immediate and tiling/indirect modes (immediate drawing being faster on the 7800), and also to mix
display modes (in this example, 160A and 160B tiles).

Basically, using sparse tiling is done through the `tiles7800` utility (from `tools7800`)  that is able to generate sparse tiling data through the
`--sparse` option. In addition to a TMX file (designed by Tiled editor), you'll have to provide the .yaml tiles
definition (so that tiles7800 can identify which tile is what, associate the correct palette, resolution).

In this example, the header `sparse_tiling.h` is used, which provides a nice `sparse_tiling_goto` function that helps
displaying a part of the tiles when panning is required.

example_sparse_tiling_hires.c
-----------------------------

This example is similar to the previous one, but the tiles are in 320 A/C mode (i.e. highres mode).

example_sparse_tiling_320BD.c
-----------------------------

The same with a 320 B/D mode display. Frankly, given the 320B awkwardness and 320D uselessness, go for 320 A/C
if you want to use highres. That will be be my advice of the day. 

example_bombjack1.c
-------------------

This example is a good example of sparse tiling for drawing background and platform. Here, the background is drawn
using the `multisprite_sparse_tiling` function. Note one of the nicest features of sparse tiling: the ability to
overlay several tiles with different palettes, allowing to use 160A mode with more than 4 colors in the same
8x8 tile block (for instance at the top of the pyramid, where we have a blue background from palette 4 and 
the sphinx colors from palette 5.

This example shows also the ability to customize the display beyond the `multisprite_init` function. Here, we're using the overscan region to make a 240p display instead of the 224p standard display of `multisprite_init`.

example_bombjack2.c
-------------------

This example adds the bombjack character. It's a good example of how to animate a sprite according to user's inputs.
It's also a good example of the `multisprite_sparse_tiling_collision` function found in `multisprite.h`.
This is also a major example of the `MULTISPRITE_OVERLAY` feature, where the background is saved with
`multisprite_save` and the bombs, which are on overlay over the background, are saved through the
`multisprite_save_overlay` function. This enables some static sprites not to be drawn at each frames, while
still being updatable (like in this example when bombs are redrawn when one explodes). 

example_sfx.c
-------------

This example uses `conio.h` header to propose a simple text GUI to play TIA sound effects converted from 7800basic.
The sound output is provided by the `sfx.h` header and the `sfx_init`, `sfx_schedule` and `sfx_play` functions. 

example_rmtracker.c
-------------------

This example shows how to use the `rmtplayer.h` to play Pokey music generated with RMT (Raster Music Tracker,
a free great tool available on https://github.com/VinsCool/RASTER-Music-Tracker) 

example_tiatracker.c
--------------------

This example shows how to use exported TIATracker music for cc7800. In order to generate the right C header for your TIA
music, you have to use the forked version of TIATracker available at https://github.com/steux/tiatracker 


The next examples form the basis of a Shoot'em up game (vertical scrolling with background,
collision detection, small effective sprites (bullets), explosions...)

example_vertical_scrolling_sparse.c
-----------------------------------

This is an example of scrolling with `multisprite.h` and sparse tiling. This is quite simple and indeed very powerful
for making shoot'em'up games. All the resources required to build the example can be found in the shmup subdirectory.

example_vertical_scrolling_sparse_vmem.c
-----------------------------------

This is an example of scrolling with `multisprite.h` and sparse tiling, this time using RAM at $4000 as video RAM. The
principle is that all the necessary data are transferred to RAM on the fly to be used as immediate mode. There is strictly no
tiled/indirect display mode used for the tiles, so CPU and DMA can be used at their maximum. Note however that this may
not be the simplest way to make a game, as sacrificing ROM at $4000 for RAM reduces the ability to use a lot of code or graphics.  

example_explosions.c
--------------------

This an example of use of the `multisprite_display_big_sprite` macro, which allows to use taller than 16 pixels high
sprites more efficiently than by subsequent calls to `multisprite_display_sprite`. 

example_small_sprites.c
-----------------------

This is an example of the `multisprite_display_small_sprites` macro, which can provide a significant gain both on CPU 
(sprite drawing) and DMA (one 1 display list impacted). Statistically, displaying a 8 pixels high sprites with this macro will provide a 25% gain not only on CPU side,
but also on DMA side, since in 50% of case, the sprite will overlay only 1 display list zone.

example_collision.c
-------------------

This is an example of the pixel accurate detection collision provided by the `multisprite.h` header combined
with `sprites7800`. It uses the `multisprite_compute_collision` and `multisprite_collision_detected` macros, and
the `collisions` keyword of `sprites7800` (see lines 164 to 166 of `shmup/resources/shmup.yaml`).

example_shmup.c
---------------

This is a SuperGame example integrating all the previous examples. Compilation options include `-DPOKEY_MUSIC` to
activate background music, and `-DMULTISPRITE_USE_VIDEO_MEMORY` to activate video memory at $4000 to free CPU.
What is interesting here is the use of DLI (Display List Interrupt) to switch from one charbase (to display digits in
the upper part) to another tileset (to display background)

The following examples form the basis of a horizontal shooter. The examples are based on the R-Type
arcade game :

example_horizontal_scrolling.c
------------------------------

This is a SuperGame example showing the horizontal scrolling capabilities of `sparse_tiling.h` header,
through the `sparse_tiling_display` and `sparse_tiling_scroll` functions. A `-DMULTISPRITE_USE_VIDEO_MEMORY` compilation option
is available to activate video memory at $4000 to free CPU/DMA (at the expense of the precious $4000-$8000 memory area).
This also enables the vertical tiles mirroring capabilities of `tiles7800`.

example_dobkeratops.c
---------------------

This is an example of displaying a really big 160B sprite, which the 7800 handles particularly well. This is also an
example of how to generate a sinus based multi-sprite animation (the boss tail).

example_RType.c
---------------

This is the horizontal scrolling example with the addition of a controllable spaceship. The use of
`sparse_tiling_collision` allows to detect collision between sprites and a scrolling sparse tiling background.
An interesting addition is a custom display setup with a 320A/C (high res) bottom score display area.

example_RType2.c
----------------

A bigger example elaborating on the previous ones, showing how to combine everything together to build
a game and a christmas card.


The following 2 examples make use of the `bitmap7800` tool :

example_BCs_title_screen.c
--------------------------

This is an example of use of the `bitmap7800` tool for generating a title screen in 160B mode (12 colors + background). 
`bitmap7800` generates display lists that can be directly used by the `multisprite_display_bitmap` function. 
Another interesting feature of `bitmap7800` is the generation of the funciton to set the palette (here
`title_screen_set_palette`), directly based on the colors used in the bitmap (limited to 13 colors obviously).

example_cc7800_banner.c
-----------------------

Another example of use of `bitmap7800`, but this time in 320A mode and combined with `conio.h`. The use of
`conio_set_dl` and `conio_restore_dl` enables an easy display of bitmaps in console mode, directly by using
the display list generated by `bitmap7800. Note that you are welcome to use this code for any game made with
cc7800 to make a little advertisment for the tool (not a requirement).

example_breakout.c
------------------

This is an example of paddle game using `multisprite_8lines.h` header. It's a highres gfx little game that can
be used as a starting point for an arkanoid like game. Note that the ball uses 2 different sprites for odd and
even horizontal position, giving access to high res display accuracy (a sprite in high res can only be 
positioned at low-res position accuracy (i.e. 0 < x < 160). 

example_gas_paddles.c
---------------------

This is an example of another paddle game using `multisprite_8lines.h` header, featuring a 4 players paddle game.
This one uses 320A/C mode display.

example_3d.c
------------

To be expanded. At the moment, only atan2 function is implemented...

test_helloworld.c
-----------------

Custom made display using only the 'prosystem.h' header. Displays a "Hello World" message using provided "Army font".
Generates a 8K ROM, the smallest possible cart generated by cc7800.

test_sprite.c
-------------
Custom made display and moving sprite using only the `prosystem.h`
header (no helper). Note the use of `holeydma` keyword that enables cc7800 to put
the sprite graphics data into a holeydma enabled memory spot (necessary for
displaying a sprite laying over 2 display lists). Note that this code is for NTSC only.

test_text.c
-----------
Custom made display using only the `prosystem.h` header (no helper). 
Note that this code is for NTSC only.

test_rand.c
-----------
Custom made display using only the `prosystem.h` header (no helper). 
`rand()` function from `stdlib.h` is used to continuously alter the background color. Note that this code is for NTSC only.

test_conio.c
------------

Example of use of the `conio.h` header. Shows color text display
with custom character, since only the 128 first characters are defined
in the standard font. As it's using the `conio.h` header, both NTSC and PAL
displays are supported (autodetected).

test_itoa.c
-----------

Example of use of `itoa` function implemented in `stdlib.h` header. Results are displayed using `conio.h`

test_bankswitching.c
--------------------

Custom made display and moving sprite using only the `prosystem.h`
header (no helper). The init function is set in `bank1` (default bank is bank0,
which for supergames is fixed and set at the end of the ROM). As 2 banks are
being used, cc7800 automatically generates a SuperGame cartridge (see `-v` verbose output of
the compiler to understand the memory layout).

test_nmi.c
----------

Displays 64 sprites moving on screen, using `multisprite.h` headers (double buffering).
Background color is changed in the middle of the screen through an interrupt (NMI =
non maskable interrupt). Note the use of the special definition `SHORT_INTERRUPT`
that tells cc7800 not to save the X and Y registers, since they are not altered by the interrupt code.

test_paddles.c
--------------

Continuous reading of 4 paddles using an interrupt. Note that paddles reading takes a lot of CPU.










