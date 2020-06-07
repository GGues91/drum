#include "hyphenline.h"
#include "toxy.h"

CU(hyphenline)
{
}
RE(hyphenline)
{
  
}
TO(hyphenline)
{
  totoken(ttn_affix); toxy;
  toaffix(NOFIX,1,0,func_re_hyphenline);
  tomatch; puts(match);
}
