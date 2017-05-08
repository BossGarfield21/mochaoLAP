//
//  stack_machine.c
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include "stack_machine.h"

#define MAX_STR	1024

typedef char str[MAX_STR];

typedef enum { RED, GREEN, BLUE } pixel_base_color;

typedef enum { HORIZONTAL, VERTICAL, CENTER } gradient_kind;

static int intensity = 0xFFFF;



void
all_red (image *img, pixel *p, size_t i, size_t j)
{
  p->r = intensity;
  p->g = 0x0000;
  p->b = 0x0000;
}

void
all_blue (image *img, pixel *p, size_t i, size_t j)
{
  p->r = 0x0000;
  p->g = 0x0000;
  p->b = intensity;
}

void
all_green (image *img, pixel *p, size_t i, size_t j)
{
  p->r = 0x0000;
  p->g = intensity;
  p->b = 0x0000;
}

void
add_pixels (image *img1, pixel *p, image *img2, pixel *q, size_t i, size_t j)
{
  p->r = min_color (q->r + p->r, __COLORS);
  p->g = min_color (q->g + p->g, __COLORS);
  p->b = min_color (q->b + p->b, __COLORS);
}


void
bw_pixels (image *img1, pixel *p, size_t i, size_t j)
{
  color_field c = (3 * ((int) p->r) + 2 * ((int) p->g) + (int) p->b) / 6;
  p->r = p->g = p->b = c;
}

void
negative_pixels (image *img1, pixel *p, size_t i, size_t j)
{
  p->r = __COLORS -((int)p->r);
  p->g =  __COLORS - ((int)p->g);
  p->b =  __COLORS - ((int)p->b);
}

void
horizontal_pixels (image *img1, pixel *p, size_t i, size_t j)
{
  int a = img1->width;
  color_field c = __COLORS - (__COLORS /  (double)a) *i;
  p->r = p->g = p->b = c;
}

void
vertical_pixels (image *img1, pixel *p, size_t i, size_t j)
{
  int a = img1->height;
  color_field c = __COLORS - (__COLORS /  (double)a) *j;
  p->r = p->g = p->b = c;
}

void
centrals_pixels (image *img1, pixel *p, size_t i, size_t j)
{ 
  
  int b = img1->height;
  int a = img1->width;
  double dx  = fabs (i - img1->width / 2.0);
  double dy  = fabs (j - img1->height / 2.0);
  double dst = sqrt (dx * dx + dy * dy);
  double x = sqrt(a*a + b*b);
  color_field e = __COLORS - (__COLORS / (x/2)) * dst;
  p->r = p->g = p->b = e ;
}

void
mask_pixels (image *img1, pixel *p, image *img2, pixel *q, size_t i, size_t j)
{

  p->r = to_mask ( q->r, __COLORS ) * p->r;
  p->g = to_mask ( q->g, __COLORS ) * p->g;
  p->b = to_mask ( q->b, __COLORS ) * p->b;

}

image*
copiar_pixels (image *img, pixel_copy cp){
	
	image *img1 = create_empty_image(img1->width, img1->height);
	pixel *pt = img->pixels;
	for (size_t j = 0; j < img1->height; j++)
   {
    for (size_t i = 0; i < img1->width; i++)
    {
      cp (img, img1, pt++, i, j);
    }
  }
  
  return img1;
}


void
dup_pixels(image *img, image *copy, pixel *p, size_t i, size_t j){
	
	
	
}

image *
combinar_imagens (image *img, image *arg, pixel_op op)
{
  pixel *pt1 = img->pixels;
  pixel *pt2 = arg->pixels;
  for (size_t j = 0; j < img->height; j++)
  {
    for (size_t i = 0; i < img->width; i++)
    {
      op (img, pt1++, arg, pt2++, i, j);
    }
  }
	
  return img;
}

void
sepia_pixels (image *img1, pixel *p, size_t i, size_t j)
{
  p->r = min_color (__COLORS,
                    ((double) p->r) * 0.393 + ((double) p->g) * 0.769
                      + ((double) p->b) * 0.189);
  p->g = min_color (__COLORS,
                    ((double) p->r) * 0.349 + ((double) p->g) * 0.686
                      + ((double) p->b) * 0.168);
  p->b = min_color (__COLORS,
                    ((double) p->r) * 0.272 + ((double) p->g) * 0.534
                      + ((double) p->b) * 0.131);
}

void
sin_distance_to_center (image *img, pixel *p, size_t i, size_t j)
{
  double dx  = fabs (i - img->width / 2.0);
  double dy  = fabs (j - img->height / 2.0);
  double dst = sqrt (dx * dx + dy * dy) / 20;

  p->r = p->g = p->b = 0.7 * __COLORS + 0.3 * __COLORS * sin (dst);
}

void
ism_execute_load(str arg_line) {
  str arg;

  sscanf (arg_line, "%s", arg);

  image *img = ppm_load_image (arg);
  if (img == NULL) {
      perror (arg);
      exit (1);
  }
  image_stack_push (img);
}

void
ism_execute_store(str arg_line) {
  str arg;

  sscanf (arg_line, "%s", arg);
  if (image_stack_is_empty())
  {
      fprintf (stderr, "Machine Crashed: Empty stack on store \n");
      exit (1);
  }

  image *img = image_stack_peek ();
  image_stack_pop ();

  ppm_write_image (arg, img);
  destroy_image (img);
}

void
ism_execute_color(str arg_line, pixel_base_color color) {
  int width, height;
  sscanf (arg_line, "%d %d %d", &width, &height, &intensity);
  image *img = create_empty_image (width, height);
  switch( color ) {
    case RED: 
      paint_image (img, all_red);
      break;
    case GREEN: 
      paint_image (img, all_green);
      break;
    case BLUE: 
      paint_image (img, all_blue);
      break;
  }
  
  image_stack_push (img);
}

void
ism_execute_bw(void) {
  image *img1     = image_stack_peek ();
  image_stack_pop ();

  paint_image (img1, bw_pixels);
  image_stack_push (img1);
}

void
ism_execute_sepia(void) {
  image *img1     = image_stack_peek ();
  image_stack_pop ();

  paint_image (img1, sepia_pixels);
  image_stack_push (img1);
}

void
ism_execute_add(void) {
    // TODO This function is part of the assignment
  image *img1 = image_stack_peek();
  image_stack_pop ();

  image *img2 = image_stack_peek();
  image_stack_pop ();

  combinar_imagens (img1, img2, add_pixels);
  image_stack_push (img1);
}

void
ism_execute_mask(void) {
    // TODO This function is part of the assignment
  image *img1 = image_stack_peek();
  image_stack_pop ();

  image *img2 = image_stack_peek();
  image_stack_pop ();
  
  combinar_imagens(img1, img2, mask_pixels);
  image_stack_push (img1);
	
}

void
ism_execute_negative(void) {
    // TODO This function is part of the assignment
	
  image *img1 = image_stack_peek();
  image_stack_pop ();
  

  paint_image (img1, negative_pixels);
  image_stack_push (img1);
  
}

void
ism_execute_gradient( gradient_kind kind, str arg_line) {
    // TODO This function is part of the assignment
	int a,b;
	sscanf (arg_line, "%d", &a);
	sscanf (arg_line, "%d", &b);
	image *img1 = create_empty_image(a, b);
	
	switch( kind ) {
    case HORIZONTAL: 
      paint_image (img1, horizontal_pixels);
      break;
    case VERTICAL: 
      paint_image (img1, vertical_pixels);
      break;
    case CENTER: 
      paint_image (img1, centrals_pixels);
      break;
  }
  
	image_stack_push (img1);
}

void
ism_execute_droplet(str arg_line) {
    // TODO This function is part of the assignment
  int a, b;
  sscanf (arg_line, "%d", &a);
  sscanf (arg_line, "%d", &b);
  image *img1 = create_empty_image(a, b);
  
  paint_image (img1, sin_distance_to_center);
  image_stack_push (img1);
}

void
ism_execute_dup(void) {
    // TODO This function is part of the assignment
}

void
ism_execute_blur(str arg_line) {
    // TODO This function is part of the assignment
}

void
ism_execute_resize(str arg_line) {
    // TODO This function is part of the assignment
}

void
ism_execute_flip( gradient_kind kind ) {
    // TODO This function is part of the assignment
}

void
ism_execute_shift(str arg_line) {
    // TODO This function is part of the assignment
}

void
ism_execute (char *fn)
{
  str line;

  FILE *fi = fopen (fn, "r");
  if (fi == NULL)
  {
    perror (fn);
    exit (1);
  }
  while (fgets (line, MAX_STR, fi) != NULL)
  {
    str cmd;

    sscanf (line, "%s", cmd);
    char *arg_line = line + strlen (cmd);

    __insta_log ("%s\n", cmd);

    if (strcmp (cmd, "load") == 0) 
      ism_execute_load( arg_line);

    else if (strcmp (cmd, "store") == 0) 
      ism_execute_store( arg_line);

    else if (strcmp (cmd, "bw") == 0)  
      ism_execute_bw();

    else if (strcmp (cmd, "sepia") == 0) 
      ism_execute_sepia();

    else if (strcmp (cmd, "red") == 0) 
      ism_execute_color( arg_line, RED );

    else if (strcmp (cmd, "green") == 0) 
      ism_execute_color( arg_line, GREEN );

    else if (strcmp (cmd, "blue") == 0)  
      ism_execute_color( arg_line, BLUE );

    else if (strcmp (cmd, "droplet") == 0) 
      ism_execute_droplet(arg_line);

    else if (strcmp (cmd, "add") == 0) 
      ism_execute_add();

    else if (strcmp (cmd, "mask") == 0)  
      ism_execute_mask();

    else if (strcmp (cmd, "negative") == 0)  
      ism_execute_negative();

    else if (strcmp (cmd, "gradient-h") == 0)  
      ism_execute_gradient( HORIZONTAL, arg_line );

    else if (strcmp (cmd, "gradient-v") == 0)  
      ism_execute_gradient( VERTICAL, arg_line );

    else if (strcmp (cmd, "gradient-c") == 0)  
      ism_execute_gradient( CENTER, arg_line );

    else if (strcmp (cmd, "dup") == 0) 
      ism_execute_dup();

    else if (strcmp (cmd, "blur") == 0)  
      ism_execute_blur(arg_line);

    else if (strcmp (cmd, "resize") == 0)  
      ism_execute_resize(arg_line);

    else if (strcmp (cmd, "flip-h") == 0)
        ism_execute_flip( HORIZONTAL );
      
    else if (strcmp (cmd, "flip-v") == 0)
        ism_execute_flip( VERTICAL );
      
    else if (strcmp (cmd, "shift") == 0)
      ism_execute_shift(arg_line);

    else
    {
      fprintf (stderr, "Machine Crashed: Unknown command:\t\"%s\"\n", cmd);
    }
  }
  if (! image_stack_is_empty ())
  {
    fprintf (stderr, "Machine Crashed: Non-empty stack in the end");
  }
  fclose (fi);
}
