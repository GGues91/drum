#ifndef LORR_H
#define LORR_H
#include "miscellaneous.h" //errxit
#include "tokenizer.h"
#include "retokenizer.h"
#include "cutenizer.h"
#include <stdlib.h> //malloc
#include <stdio.h>  //printf
#include <string.h> //strcpy

/* run upon ambiguity
   lorr defined in lorr.c */
#define LorR int lorr(Stoken *l, Stoken *r)

int lorr(Stoken *l, Stoken *r);

#endif
