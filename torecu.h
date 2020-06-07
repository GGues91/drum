#ifndef EXTENSION_H
#define EXTENSION_H

#include "miscellaneous.h"
#include "token.h"
#include "tokenizer.h"
#include "retokenizer.h"
#include "cutenizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* CU, RE, TO in cutenizer.h and retokenizer.h and tokenizer.h */
#define TORECU(foo)\
  CU(foo);\
  RE(foo);\
  TO(foo);

#endif
