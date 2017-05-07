//
//  test_instakilo.c
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "test_instakilo.h"

// Auxiliary functions

bool
has_size (size_t width, size_t height, image *img)
{
  byte *pt = (byte *) img->pixels;
  for (size_t i = 0; i < img->height * img->width; i++)
  {
    if (!(*pt++ >= 0))
    {
      return false;    // pokes all bytes...
    }
  }
  return img->width == width && img->height == height;
}

bool
is_black (image *img)
{
  byte *pt = (byte *) img->pixels;
  for (size_t i = 0; i < 3 * img->height * img->width; i++)
  {
    if (!(*pt++ == 0))
    {
      return false;
    }
  }
  return true;
}


bool
is_solid (image *img, pixel p)
{
  pixel *pt = (pixel *) img->pixels;
  for (size_t i = 0; i < img->height * img->width; i++)
  {
    if (pt->r != p.r || pt->g != p.g || pt->b != p.b)
    {
      __insta_log ("the image is not solid..\n");
      return false;
    }
  }
  return true;
}

pixel _RED_PIXEL = {0xFFFF, 0x0000, 0x0000};

pixel _BLUE_PIXEL = {0x0000, 0x0000, 0xFFFF};

pixel _GREY_PIXEL = {0xA000, 0xA000, 0xA000};

pixel _REDBLUE_PIXEL = {0xFFFF, 0x0000, 0xFFFF};

void
_all_red (image *img, pixel *p, size_t i, size_t j)
{
  *p = _RED_PIXEL;
}

void
_all_blue (image *img, pixel *p, size_t i, size_t j)
{
  *p = _BLUE_PIXEL;
}

void
_add_pixels (image *img1, pixel *p, image *img2, pixel *q, size_t i, size_t j)
{
  p->r = min_color (q->r + p->r, __COLORS);
  p->g = min_color (q->g + p->g, __COLORS);
  p->b = min_color (q->b + p->b, __COLORS);
}

// Tests

void
test_empty_image ()
{
  size_t width  = 100;
  size_t height = 100;
  image *img    = create_empty_image (width, height);
  assert (has_size (width, height, img));
  assert (is_black (img));

  destroy_image (img);
}

void
test_paint_image ()
{
  size_t width  = 100;
  size_t height = 100;
  image *img    = create_empty_image (width, height);

  paint_image (img, _all_red);

  assert (is_solid (img, _RED_PIXEL));
  destroy_image (img);
}

void
test_combine_image ()
{
  // This test only works after combine_image is done
  // size_t width  = 100;
  // size_t height = 100;
  // image *img    = create_empty_image (width, height);
  // image *arg    = create_empty_image (width, height);

  // paint_image (img, _all_red);
  // paint_image (arg, _all_blue);

  // combine_image (img, arg, _add_pixels);

  // assert (is_solid (img, _REDBLUE_PIXEL));

  // destroy_image (img);
  // destroy_image (arg);
}


void
test_write_load_image ()
{
  image *img = create_empty_image (1000, 1000);
  paint_image (img, _all_red);

  assert (is_solid (img, _RED_PIXEL));

  ppm_write_image ("test-output/test_red.ppm", img);
  free (img);

  image *img2 = ppm_load_image ("test-output/test_red.ppm");

  assert (img2 != NULL);
  assert (is_solid (img2, _RED_PIXEL));
}

void
test_all ()
{
  __insta_log ("Debug mode\n");

  char cwd[1024];
  getcwd (cwd, sizeof (cwd));
  printf ("cwd: %s\n", cwd);

  test_empty_image ();

  test_paint_image ();

  test_combine_image ();

  test_write_load_image ();

}
