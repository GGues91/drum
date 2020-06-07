#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "../torecu.h"
/*
  if some TORECU/whatever_name.c depends
  on some other TORECU/whatever_name.c
  eg this TORECU/assignment.c
  it can just include TORECU/assignment.h
 */

CU(assignment);
RE(assignment);
TO(assignment);

typedef struct assignment_t assignment_t;
struct assignment_t
{
  Stoken value;
};

#define assignment_last_index ('z' - 'a')

Stoken *syono(Stoken *token);

#endif
