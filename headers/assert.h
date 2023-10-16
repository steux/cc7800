#ifndef __ASSERT_H__
#define __ASSERT_H__

#ifdef DEBUG
#define assert(x) if (!(x)) *BACKGRND = 0x45;
#else
#define assert(x) ;
#endif

#endif // __ASSERT_H__
