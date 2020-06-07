#include "addition.h"

CU(addition_infix)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_number | ttn_property_type;
  TT(&RETU).number.n = TTcuono(syono(ttcv(0))).number.n
    + TTcuono(syono(ttcv(1))).number.n;
  return &RETU;
}
CU(addition_prefix)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_number | ttn_property_type;
  TT(&RETU).number.n = TTcuono(syono(ttcv(0))).number.n;
  return &RETU;
}

/*
void generic_re_1() {
  reicanp(a|b);
  reaffix2callable;
  // TODO: deal with more than 2 in argc
  if(ttc.argc == 2)
    recallable(ttn_symbol
	       |
	       ttn_number
	       |
	       ttn_property_type,
	       func_cu_addition_infix);
  else
    recallable(ttn_symbol
	       |
	       ttn_number
	       |
	       ttn_property_type,
	       func_cu_addition_prefix);
}
*/

RE(addition) {
  reicanp(ttn_number|ttn_symbol);
  reaffix2callable;
  //if argc != 1 make infix otherwise make prefix
  if(ttc.argc == 2){
    recallable(ttn_symbol|ttn_number|ttn_property_type,func_cu_addition_infix);
  }
  else{
    recallable(ttn_symbol|ttn_number|ttn_property_type,func_cu_addition_prefix);
  }
}
TO(addition) {
  totoken(ttn_affix);
  toaffix(INFIX,1,1,func_re_addition);
}

