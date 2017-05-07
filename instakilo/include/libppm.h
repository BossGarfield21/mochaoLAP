//
//  libppm.h
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "libimg.h"

#ifndef __INSTA_PPM_UTILS__
#define __INSTA_PPM_UTILS__

#define __INSTA_NUM_COMPONENT_COLORS ((1 << __INSTA_COLOR_DEPTH) - 1)
#define __INSTA_NUM_ALTERNATIVE_COMPONENT_COLORS                               \
  ((1 << __INSTA_ALTERNATIVE_COLOR_DEPTH) - 1)
#define __COLORS __INSTA_NUM_COMPONENT_COLORS
#define __INSTA_PPM_TYPE "P6"

image *
ppm_load_image (char *fn);

void
ppm_write_image (char *fn, image *img);

#endif /* __INSTA_PPM_UTILS__ */
