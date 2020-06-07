#include "wav.h"

CU(wav)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_symbol|ttn_property_type;
  return &RETU;
}
RE(wav)
{
  reaffix2callable;
  recallable(ttn_symbol|ttn_property_type,func_cu_wav);
}
TO(wav)
{
  totoken(ttn_affix);
  toaffix(PREFIX,1,0,func_re_wav);
}
