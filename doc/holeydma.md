On the Atari 7800, the memeory seen by Maria is divided into 3 types of zones :
- "Holey DMA enabled zones" which are zones that are read by Maria. This should contain the sprites data to be displayed.
- "Holey DMA disabled zones" which are zones that are read as 0 by Maris. These are "automatic" zeros the enable Maris
    to display the void above and below sprites.
- "Holey DMA neutral zones" which are zones that are correctly read by Maria, but are not sandwiched between 2 "Holey
    DMA disables zones". These zones can typically contain tiles (i.e aligned spritew that don't upper or lower zeros).

In most games, we are using 16 pixels high sprites and thus active 16 pixels holeydma. This results in the following
memory mapping seen by Maria:


Here are the rules for scattered data layout :
1. The scattered data are stored in the order they are declared, provided that the 3
following rules are enforced.
2. The "Holey DMA enabled zones" accept all kind of scattered data, holeydma or not.
3. Holeydma scattered data (i.e. sprites data) are only fitted in "Holey DMA enabled zones"
4. Non-holeydma scattered data (i.e. likely tiles or aligned bitmaps) are fitted in memory
as low in memory as possible. They are stored in priority over code or ROM constant data.

In practice, this algorithm fits most needs without requiring any specific configuration.
