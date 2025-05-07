# Sprites

Sprites are used by first defining [graphical resources](graphical_resources.md) and calling `multisprite_display_sprite()` as shown in [example_multisprite.c](../../examples/example_multisprite.c):

Contrary to most other systems, sprites on the 7800 ProSystem can be very wide (up to 124 pixels wide). They are however only as tall as the horizontal zones they're in.

```
multisprite_init();
multisprite_save();

// Main loop
do {
    multisprite_flip();

    multisprite_display_sprite(xpos, ypos, bb_char1, 2, 0); 
}
```

The before-last parameter is the number of bytes the sprite takes horizontally. By default it should be (sprite width in pixels) / 4.

Note that cc7800 maintains a double [DLL](dll.md) in memory, so you have a whole screen refresh to come up with the next frame. Calling `multisprite_flip()` switches the two DLLs without any flickering.

## Sprites API

- `multisprite_display_sprite()`: displays a sprite
- `multisprite_display_small_sprite()`: displays a small sprite
- `multisprite_display_big_sprite()`: displays a sprite which spans across multiple horizontal zones
- `multisprite_display_*_sprite_aligned()`: displays a sprite which is vertically aligned to a horizontal zone. Such sprites take less time to define and to draw
- `multisprite_display_*_sprite_ex()`: has a `mode` argument which, when set to 1, displays a sprite in 160B (12 colors) or 320B mode
- `multisprite_display_*_sprite_fast()`: a faster but less failsafe way to display sprites

## multisprite_save() ?

Sometimes there are some sprites and tiles that will always be displayed on the screen. These can be background tiles, dashboard sprites, etc. Those should be defined once and for all between `multisprite_init()` and `multisprite_save()`, e.g.

```
multisprite_init();
tiling_init(tilemap, TILEMAP_WIDTH, TILEMAP_HEIGHT, x, y, 1);
multisprite_display_sprite(0, 0, game_logo, 4, 0);
multisprite_save();
```

Once these are defined before `multisprite_save()`, they do not need to be defined again in the main loop, saving time. The downside is that they cannot be removed and will always be displayed behind any other sprite.

## Overlays

Overlays allow to have a group of sprites which do not need to be refreshed any single frame, but have the ability to be changed nonetheless (contrary to what is defined before `multisprite_save()`).

Once you define an overlay, it does not need to be redefined in the main loop until it needs to be modified, in which case it is updated by calling `multisprite_clear_overlay()` and `multisprite_save_overlay()`. Note that you need to redefine it for two consecutive frames due to double buffering.

```
#define MULTISPRITE_OVERLAY

// Define sprites and tiles that will be static and drawn behind everything else
multisprite_init();
tiling_init(tilemap, TILEMAP_WIDTH, TILEMAP_HEIGHT, x, y, 1);
multisprite_display_sprite(0, 0, game_logo, 4, 0);
multisprite_save();

// Main loop
do {
    if (update_overlay) {
        update_overlay--;
        multisprite_clear_overlay();
        // Define sprites and tiles which are part of the overlay
        // These are drawn between the background and the non-overlaid sprites
        if (treasure) {
            multisprite_display_sprite_fast(x, y, treasure_chest, 2, 1);
        }
        ...
        multisprite_save_overlay();
    }

    if (need_to_recreate_overlay) {
        update_overlay = 2;
    }

    // Display the remaining sprites
    multisprite_display_sprite_fast(x, y, player_sprite, 2, 0);

    multisprite_flip();
} while (1);
```

See [example_bombjack2.c](../../examples/example_bombjack2.c)
