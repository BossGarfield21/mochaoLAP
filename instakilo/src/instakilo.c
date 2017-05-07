//
//  instakilo.c
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

#include "instakilo.h"

/*
 * function: paint_image
 * --------------------------------------------------------
 * returns the image provided as argument, modified by the
 * function also given as argument.
 * --------------------------------------------------------
 * img: the target image
 * f:   the painting function
 * --------------------------------------------------------
 * pre: img != NULL && f != NULL
 * post: res == img
 */

image *
paint_image (image *img, pixel_set f)
{
  pixel *pt = img->pixels;
  for (size_t j = 0; j < img->height; j++)
  {
    for (size_t i = 0; i < img->width; i++)
    {
      f (img, pt++, i, j);
    }
  }
  return img;
}



/*
 * function: combine_image
 * --------------------------------------------------------
 * returns the image on the left, modified by the operation
 * given, and using the image on the right as argument to the
 * operation
 * --------------------------------------------------------
 * img: the target image
 * arg: the argument image
 * op:  the combination operator
 * --------------------------------------------------------
 * pre: size(img) == size(arg) &&
 * op changes the pixel on the left and does not change the second parameter
 * post: res == img
 */
image *
combine_image (image *img, image *arg, pixel_op op)
{
  return img;
}



