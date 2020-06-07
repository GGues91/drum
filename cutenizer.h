#ifndef CUTENIZER_H
#define CUTENIZER_H
#include "token.h"

/* CU interface 
   a CU is C-function named cutenizer */
#define CU(name) Stoken *func_cu_##name (Stoken *token)
#define ttnof(TOKEN)\
  (TT(TOKEN).NUMBER & ttn_callable ? TT(TOKEN).callable.retu : TT(TOKEN).NUMBER)

/* C-function declaration */
Stoken *cuono(Stoken *token);
Stoken *execute(Stoken *token);

#endif
