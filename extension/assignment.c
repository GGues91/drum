#include "assignment.h"

assignment_t assignment[assignment_last_index + 1];

CU(assignment)
{
  static Stoken RETU;
  TT(&RETU).NUMBER = ttn_symbol;
  TT(&RETU).symbol.s = TTcuono(ttcv(0)).symbol.s;
  assignment['z' - TT(&RETU).symbol.s].value =
    *cuono(syono(ttcv(1)));
  return &RETU;
}
RE(assignment)
{
  reaffix2callable;
  //if(0 == ttnchk(ttcv(0),ttn_symbol,ttn_property_type))
  //errxit("expected ttn_symbol,ttn_property_type");
  recallable(ttn_nil,func_cu_assignment);
}
TO(assignment)
{
  totoken(ttn_affix);
  toaffix(INFIX,1,0,func_re_assignment);
}

Stoken *syono(Stoken *token)
{
  if(tt.NUMBER & ttn_symbol)
    return &(assignment['z' - tt.symbol.s].value);
  else
    return token;
}
