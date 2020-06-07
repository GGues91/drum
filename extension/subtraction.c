#include "subtraction.h"

CU(subtraction_infix)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_number | ttn_property_type;
  TT(&RETU).number.n = TTcuono(syono(ttcv(0))).number.n
    - TTcuono(syono(ttcv(1))).number.n;
  return &RETU;
}
CU(subtraction_prefix)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_number | ttn_property_type;
  TT(&RETU).number.n = -TTcuono(syono(ttcv(0))).number.n;
  return &RETU;
}
RE(subtraction)
{
  reicanp(ttn_number|ttn_symbol);
  reaffix2callable;
  if(ttc.argc == 2){
    recallable(ttn_symbol|ttn_number|ttn_property_type,func_cu_subtraction_infix);
  }
  else{
    recallable(ttn_symbol|ttn_number|ttn_property_type,func_cu_subtraction_prefix);
  }
}
TO(subtraction)
{
  totoken(ttn_affix);
  toaffix(INFIX,1,1,func_re_subtraction);
}
