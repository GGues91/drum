#include "example_addition.h"


/*
  how to make return listable (eg enabling to use lists ie return more than one value)
*/
CU(example_addition_infix)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_number | ttn_property_type;
  TT(&RETU).number.n = TTcuono(syono(ttcv(0))).number.n
    + TTcuono(syono(ttcv(1))).number.n;
  return &RETU;
}
CU(example_addition_prefix)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_number | ttn_property_type;
  TT(&RETU).number.n = TTcuono(syono(ttcv(0))).number.n;
  return &RETU;
}
RE(example_addition)
{
  reicanp(ttn_number|ttn_symbol);
  reaffix2callable;
  //if argc != 1 make infix otherwise make prefix
  if(ttc.argc == 2){
    recallable(ttn_symbol|ttn_number|ttn_property_type,func_cu_example_addition_infix);
  }
  else{
    recallable(ttn_symbol|ttn_number|ttn_property_type,func_cu_example_addition_prefix);
  }
}
TO(example_addition)
{
  totoken(ttn_affix);
  toaffix(INFIX,1,1,func_re_addition);
}
