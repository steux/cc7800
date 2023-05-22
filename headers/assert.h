#ifdef DEBUG
#define assert(x) if (!(x)) *BACKGRND = 0x45;
#else
#define assert(x) ;
#endif

