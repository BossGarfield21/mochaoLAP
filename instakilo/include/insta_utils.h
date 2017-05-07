//
//  insta_utils.h
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include <stdlib.h>
#include <assert.h>

#ifndef __INSTA_UTILS__
#define __INSTA_UTILS__

#ifndef NDEBUG
#define __insta_log(...) fprintf (stderr, __VA_ARGS__)
#else
#define __insta_log(...) ((void) 0)
#endif

#endif /* __INSTA_UTILS__ */
