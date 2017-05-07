//
//  image_stack.c
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//


#include "image_stack.h"

typedef struct image_stack
{
    image *             img;
    struct image_stack *prev;
} image_stack;

image_stack *stack = NULL;

bool
image_stack_is_empty(void) {
    return stack == NULL;
}

/*
 * pre: stack != NULL
 */
image *
image_stack_peek (void)
{
  return stack->img;
}

/*
 * pre: img != NULL
 */
void
image_stack_push (image *img)
{
  image_stack *top = malloc (sizeof (image_stack));
    
  top->img  = img;
  top->prev = stack;
  stack     = top;
}

/*
 * pre: top != NULL
 */
void
image_stack_pop (void)
{
  assert (stack != NULL);

  image_stack* top     = stack;
  image_stack *new_top = top->prev;
    
  stack = new_top;
  free (top);
}
