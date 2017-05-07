//
//  instakilo.h
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include "libimg.h"
#include "libppm.h"

#ifndef __INSTA_KILO__
#define __INSTA_KILO__

/*
 * 
 */
typedef void(pixel_set) (image *img, pixel *p, size_t i, size_t j);

typedef void(pixel_copy) (
  image *img, image *copy, pixel *p, size_t i, size_t j);

typedef void(pixel_op) (
  image *img1, pixel *p, image *img2, pixel *q, size_t i, size_t j);

image *
paint_image (image *img, pixel_set f);

image *
combine_image (image *img, image *arg, pixel_op op);

#endif /* __INSTA_KILO__ */
