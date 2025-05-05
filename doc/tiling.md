# Tiling

The background is typically drawn by tiles using tiling (also called indirect mode). Tiling works on cc7800 by importing a tileset (see [Graphical Resources](graphical_resources.md)) and using a tilemap.

By default, cc7800 defines the screen as follows:

- One 8-pixel high blank horizontal zone
- Fourteen 16-pixel high horizontal zones that can each accomodate a tilemap of 20 tiles
- One 8-pixel high blank horizontal zone

(include `multisprite_8lines.h` instead of `multisprite.h` to use 8-pixel high tiles instead)

The easiest way is to use `tiling_init()` as seen in [example_tiled2.c](../examples/example_tiled2.c):

```
reversed scattered(16,14) char tiles[224] = { ... };

const char tilemap[1024] = { ... };

multisprite_set_charbase(tiles);
tiling_init(tilemap, TILEMAP_WIDTH, TILEMAP_HEIGHT, x, y, 1);
```

From there, you can scroll tiles by calling `tiling_goto(x, y)`

## Tiling row by row

Contrary to most other systems with hardware tiling, each tile row is completely independent of each other in the 7800. Tiles do not need to start at X=0 and do not need to cover the whole screen. Actually you can set many tilemaps per horizontal zone.

cc7800 allows to define tiles one row at a time by using `multisprite_display_tiles_fast(x, y, tilemap, tilemap_size, palette)`, e.g.

```
multisprite_set_charbase(tiles);

multisprite_display_tiles_fast(0, 0, tilemap0, 21, 0);
multisprite_display_tiles_fast(0, 1, tilemap1, 21, 0);
multisprite_display_tiles_fast(0, 2, tilemap2, 21, 0);
multisprite_display_tiles_fast(0, 3, tilemap3, 21, 0);
...
```

Definining tilemaps row by row can be used for parallax scrolling as the `x` parameter can be negative, thus shifting the row tilemap slightly to the left.

Notes:

- The `x` parameter is in pixels whereas the `y` parameter is the row number
- It takes 20 standard large tiles to fill the whole screen
- 21 tiles will be used when using horizontal scrolling
- If you specify 32 tiles, the tilemap will loop around the screen, looking like the whole screen is covered regardless of the value of `x` (as 8*32 = 256). This allows to have a circular tilemap. This is used by Super Circus Atari to draw the balloons, the programm only changing the X coordinate of the tilemap for each row of balloons. The downside of this approach is that it takes more time for MARIA to draw this tilemap, so can create issues if there are many other sprites on that row.

## Sparse tiling

When the background does not contain a lot of detail, it may be faster to use sparse tiling, i.e. only displays a few tiles when need be and leave the rest with the background color. The game Basketbrawl uses this technique.

cc7800 has a `sparse_tiling_init()` API to use this feature. See [example_sparse_tiling.h](../examples/example_sparse_tiling.c).

## Things to know

- The tileset (`tiles` in our examples) needs to be 256-bytes aligned in memory, so it is recommended to declare it before any other graphical resources.
- When using large tiles, the tilemap index should be multiplied by two, e.g. 2 for tile #1, 4 for tile #2, etc.
