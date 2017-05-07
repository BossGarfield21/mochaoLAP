//
//  libppm.c
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include "libppm.h"

const char * ppm_type             = __INSTA_PPM_TYPE;
const size_t num_component_colors = __COLORS;

/*
 * We are using a simple image format, named ppm
 * see the following URL for more information
 * http://netpbm.sourceforge.net/doc/ppm.html
 */

static int
correct_image_format (FILE *fi, char *fn, image *img)
{
  int color_depth = -1;
  // check the image format
  char buff[80];
  if (fgets (buff, sizeof (buff), fi) == NULL)
  {
    __insta_log ("Error reading file header");
    return -1;
  }

  // check the image format
  if (buff[0] != 'P' || buff[1] != '6')
  {
    __insta_log ("Invalid image format (expecting 'P6')\n");
    return -1;
  }

  // skipping comments
  char c;
  while ((c = getc (fi)) == '#')
  {
    while ((c = getc (fi)) != '\n')
    {
      ;
    }
  }

  ungetc (c, fi);

  // reading image width and height
  if (fscanf (fi, "%zd %zd", &img->width, &img->height) != 2)
  {
    __insta_log ("'%s': Invalid image size\n", fn);
    return -1;
  }
  printf ("%lu\t%lu\n", img->width, img->height);

  int rgb_comp_color;
  // reading rgb component
  if (fscanf (fi, "%d", &rgb_comp_color) != 1)
  {
    __insta_log ("'%s': Invalid rgb component\n", fn);
    return -1;
  }

  // check rgb component depth
  if (rgb_comp_color == __INSTA_NUM_COMPONENT_COLORS)
  {
    color_depth = __INSTA_COLOR_DEPTH;
  } else if (rgb_comp_color == __INSTA_NUM_ALTERNATIVE_COMPONENT_COLORS)
  {
    color_depth = __INSTA_ALTERNATIVE_COLOR_DEPTH;
  } else
  {
    return -1;
  }

  if (fgetc (fi) != '\n')
  {
    return false;
  }

  return color_depth;
}


image *
ppm_load_image (char *fn)
{
  FILE *fi = fopen (fn, "r");
  assert (fi != NULL);

  image *img = malloc (sizeof (image));
  assert (img != NULL);

  int color_depth = correct_image_format (fi, fn, img);

  if (color_depth == -1)
  {
    return NULL;
  }

  // gets the number of bytes required, given the depth of colors (it's
  // equivalent to a division by 8)
  size_t depth_size = color_depth >> 3;

  size_t raw_size = img->width * img->height * 3;
  // The 3 represents the three components of color (R, G, B).
  // Since we do not expect that the number of this basic colors ever changes,
  //   we have no problem on leaving this hard-coded.
  byte *data = malloc (raw_size * depth_size);
  assert (data != NULL);

  // read pixel data from file
  if (fread (data, depth_size, raw_size, fi) != raw_size)
  {
    __insta_log ("Error loading image '%s'\n", fn);
    return NULL;
  }

  /*
   * In the PPM format, the most significant byte is the right-most one.
   *
   * Since we want to abstract ourselves from the file format, we store
   * the images in memory in the normal order (i.e. the most significant
   * byte is the leftmost, and not the opposite).
   *
   * The following transforms the data represented on disk into an image
   * structure (that is stored in memory, and in the correct order).
   */
  if (color_depth == __INSTA_COLOR_DEPTH)
  {
    /*
     * If the image is stored in 16 bits, we have to swap the left byte by the
     * right byte.
     */
    img->pixels     = (pixel *) data;
    size_t img_size = img->width * img->height;
    for (size_t i = 0; i < img_size; i++)
    {
      img->pixels[i].r = (img->pixels[i].r >> 8) | (img->pixels[i].r << 8);
      img->pixels[i].g = (img->pixels[i].g >> 8) | (img->pixels[i].g << 8);
      img->pixels[i].b = (img->pixels[i].b >> 8) | (img->pixels[i].b << 8);
    }
  } else
  {
    /*
     * In this case, the image is stored using 8 bits, but we really want to
     * use 16 bits.
     */
    img->pixels = malloc (img->width * img->height * sizeof (pixel));
    assert (img->pixels != NULL);
    size_t img_size = img->width * img->height;
    for (size_t i = 0; i < img_size; i++)
    {
      img->pixels[i].r = ((color_field) data[3 * i + 0]) << 8;
      img->pixels[i].g = ((color_field) data[3 * i + 1]) << 8;
      img->pixels[i].b = ((color_field) data[3 * i + 2]) << 8;
    }
    free (data);
  }

  fclose (fi);

  return img;
}

void
ppm_write_image (char *fn, image *img)
{
  assert (fn != NULL);
  assert (img != NULL);
  FILE *fp = fopen (fn, "w");
  assert (fp != NULL);

  /*
   * In the PPM format, the most significant byte is the right-most one.
   *
   * Since we want to abstract ourselves from the file format, we store the
   * images in memory in the normal order (i.e. the most significant byte is
   * the leftmost, and not the opposite).
   *
   * The following transforms an image from the memory representation to the
   * disk representation (i.e. it swaps the left and right bytes to match the
   * PPM specification).
   */

  size_t img_size = img->width * img->height;
  pixel *data     = malloc (img_size * sizeof (pixel));
  assert (data != NULL);

  for (size_t i = 0; i < img_size; i++)
  {
    data[i].r = (img->pixels[i].r >> 8) | (img->pixels[i].r << 8);
    data[i].g = (img->pixels[i].g >> 8) | (img->pixels[i].g << 8);
    data[i].b = (img->pixels[i].b >> 8) | (img->pixels[i].b << 8);
  }

  /* Print the P6 format header */
  fprintf (fp,
           "%s\n%ld %ld\n%ld\n",
           ppm_type,
           img->width,
           img->height,
           num_component_colors);
  fwrite (data, sizeof (pixel), img->width * img->height, fp);
  free (data);
  fclose (fp);
}
