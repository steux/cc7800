

Here are the rules for scattered data layout :
1. The scattered data are stored in the order they are declared, provided that the 3
following rules are enforced.
2. The "Holey DMA enabled zones" accept all kind of scattered data, holeydma or not.
3. Holeydma scattered data (i.e. sprites data) are only fitted in "Holey DMA enabled zones"
4. Non-holeydma scattered data (i.e. likely tiles or aligned bitmaps) are fitted in memory
as low in memory as possible. They are stored in priority over code or ROM constant data.

