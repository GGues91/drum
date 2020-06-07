#include "exit.h"

CU(exit)
{

  if(TTcuono(ttcv(0)).NUMBER & ttn_number)
    {
      exit(TTcuono(ttcv(0)).number.n);
    }
  else if(TTcuono(ttcv(0)).NUMBER & ttn_string)
    {
      printf("exit message: %s\n",TTcuono(ttcv(0)).string.s);
    }
  exit(0);
}
/*
  if affix then callable is implied
*/
RE(exit)
{
  reaffix2callable;
  //if(!(TTcuono(ttcv(0)).NUMBER & ttn_property_type))
  //errxit("non-type passed to EXIT");
  recallable(ttn_nil,func_cu_exit);
}
TO(exit)
{
  puts("found EXIT");
  totoken(ttn_affix);
  toaffix(PREFIX,1,0,func_re_exit);
}
