# Scrolling

cc7800 provide various scrolling capabilities.

This is achived by using either `#define HORIZONTAL_SCROLLING`, `#define VERTICAL_SCROLLING` or `#define BIDIR_VERTICAL_SCROLLING` and then calling `multisprite_vertical_scrolling(offset)` and/or `multisprite_horizontal_scrolling(offset)`.

See the following examples:

- [example_tiled.c](../examples/example_tiled.c)
- [example_vertical_scrolling.c](../examples/example_vertical_scrolling.c)
- [example_vertical_scrolling_sparse.c](../examples/example_vertical_scrolling_sparse.c)
