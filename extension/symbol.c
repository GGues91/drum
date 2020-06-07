#include "symbol.h"
#include "toxy.h"

TO(symbol)
{
  totoken(ttn_symbol | ttn_property_type);
  tt.symbol.s = *to->p;
  toxy;
  printf("%d,%d -- found %c\n",tox,toy,tt.symbol.s);
}
