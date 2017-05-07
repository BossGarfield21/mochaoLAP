//
//  stack_machine.h
//  Instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "instakilo.h"
#include "image_stack.h"
#include "libimg.h"

#ifndef __INSTA_STACK_MACHINE__
#define __INSTA_STACK_MACHINE__

/*
 * This is a stack machine, whose operations work on images.
 * You can push images, and then call operations, which pop the operands
 * (i.e. the images) from the stack, and push the new result to the stack.
 */
void
ism_execute (char *);

#endif /* __INSTA_STACK_MACHINE__ */
