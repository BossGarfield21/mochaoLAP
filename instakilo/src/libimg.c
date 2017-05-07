//
//  libimg.c
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include "libimg.h"


size_t
idx_of (image *img, size_t i, size_t j)
{
  return (i + j * img->width);
}

void
set_pixel (image *img, size_t i, size_t j, pixel p)
{
  img->pixels[idx_of (img, i, j)] = p;
}

pixel
get_pixel (image *img, size_t i, size_t j)
{
  return img->pixels[idx_of (img, i, j)];
}

/*
 * function: create_empty_image
 * --------------------------------------------------------
 * returns a newly allocated image, with the given width and
 * height, filled with 0X000000
 * --------------------------------------------------------
 * width:   the width of the image
 * height:  the height of the image
 * returns: a newly allocated image
 * --------------------------------------------------------
 * pre: width >= 0 && height >= 0
 * post: is_image(result) && is_black(result)
 */
image *
create_empty_image (size_t width, size_t height)
{
  assert (width >= 0 && height >= 0);
  image *img = malloc (sizeof (image));

  img->width      = width;
  img->height     = height;
  size_t img_size = width * height;
  img->pixels     = malloc (img_size * sizeof (pixel));

  pixel bg = {0x0000, 0x0000, 0x0000};    // Default background

  for (size_t i = 0; i < img_size; i++)
  {
    img->pixels[i] = bg;
  }

  return img;
}

void
destroy_image (image *img)
{
  free (img->pixels);
  free (img);
}

uint32_t
max_color (uint32_t a, uint32_t b)
{
  if (a > b)
  {
    return a;
  }
  return b;
}

uint32_t
min_color (uint32_t a, uint32_t b)
{
  if (a > b)
  {
    return b;
  }
  return a;
}

double
to_mask (uint32_t a, uint32_t max)
{
  return ((double) a) / ((double) max);
}
