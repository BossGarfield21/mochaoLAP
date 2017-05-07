//
//  libimg.h
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
#include <stdlib.h>
#include "insta_utils.h"

#ifndef __INSTA_LIB_IMG__
#define __INSTA_LIB_IMG__

typedef uint8_t byte;

// The default color depth must be greater than the alternative!
typedef uint16_t color_field;
#define __INSTA_COLOR_DEPTH 16
#define __INSTA_ALTERNATIVE_COLOR_DEPTH 8

#pragma pack(push, 1)
typedef struct
{
  color_field r;
  color_field g;
  color_field b;
} pixel;
#pragma pack(pop)

typedef struct
{
  size_t width, height;
  pixel *pixels;
} image;

size_t
idx_of (image *img, size_t i, size_t j);

void
set_pixel (image *img, size_t i, size_t j, pixel p);

pixel
get_pixel (image *img, size_t i, size_t j);

image *
create_empty_image (size_t width, size_t height);

void
destroy_image (image *img);

uint32_t
max_color (uint32_t a, uint32_t b);

uint32_t
min_color (uint32_t a, uint32_t b);

double
to_mask (uint32_t a, uint32_t max);

#endif    // __INSTA_LIB_IMG__
