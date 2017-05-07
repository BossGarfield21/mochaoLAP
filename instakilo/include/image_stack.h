//
//  image_stack.h
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include <stdbool.h>

#include "instakilo.h"
#include "libimg.h"

#ifndef __INSTA_IMAGE_STACK__
#define __INSTA_IMAGE_STACK__

bool
image_stack_is_empty(void);

image *
image_stack_peek (void);

void
image_stack_push (image *img);

void
image_stack_pop (void);

#endif /* __INSTA_IMAGE_STACK__ */
