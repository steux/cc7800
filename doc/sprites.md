# Sprites

Sprites are used by first defining [graphical resources](graphical_resources.md) and calling `multisprite_display_sprite()` as shown in [example_multisprite.c](../examples/example_multisprite.c):

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

## multisprite_save() ?

Sometimes there are some sprites and tiles that will always be displayed on the screen. These can be background tiles, dashboard sprites, etc. Those should be defined once and for all between `multisprite_init()` and `multisprite_save()`, e.g.

```
multisprite_init();
tiling_init(tilemap, TILEMAP_WIDTH, TILEMAP_HEIGHT, x, y, 1);
multisprite_display_sprite(0, 0, game_logo, 4, 0);
multisprite_save();
```

Once these are defined before `multisprite_save()`, they do not need to be defined again in the main loop, saving time. The downside is that they cannot be removed and will always be displayed behind any other sprite.
