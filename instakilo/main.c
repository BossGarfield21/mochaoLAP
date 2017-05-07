//
//  main.c
//  instakilo
//
//  LAP 2016-17: C Programming language assignment
//
//  Created By:
//  João Costa Seco
//  Guilherme Rito
//

#include <stdio.h>

#include "include/stack_machine.h"
#include "include/test_instakilo.h"

int
main (int argc, char *argv[])
{
#ifndef NDEBUG
  test_all ();
#endif

  if (argc != 2)
  {
    printf ("Usage: %s pipeline.ppl", argv[0]);
    return 0;
  }

  ism_execute (argv[1]);
  return 0;
}
