


#include "print.h"

CU(print)
{
  if(TTcuono(ttcv(0)).NUMBER & ttn_number)
    printf("%d\n",TTcuono(ttcv(0)).number.n);
  if(TTcuono(ttcv(0)).NUMBER & ttn_symbol)
    printf("%d\n",TTcuono(syono(ttcv(0))).number.n);
  if(TTcuono(ttcv(0)).NUMBER & ttn_list)
    {
      puts("trying to print list:");
      Stoken *tmp = TTcuono(ttcv(0)).list.token;
      //printf("%d\n",TTcuono(ttcv(0)).list.token->type.number.n);
      printf("(");
      while(tmp != NULL)
	{
	  printf("%d, ", tmp->type.number.n);
	  tmp = tmp->nxt;
	}
      printf(")\n");

    }
  if(TTcuono(ttcv(0)).NUMBER & ttn_string)
    {
      char *p = TTcuono(syono(ttcv(0))).string.s;
      char c;
      for(;*p;++p)
	{
	  while(*p == '\\')
	    {
	      ++p;
	      switch(*p){
	      case '\\':
		c = '\\';
		goto gstat;
	      case 'n':
		c = '\n';
		goto gstat;
	      default:
		{
		gstat:
		  strcpy(p-1,p);
		  *(p-1) = c;
		}
		break;
	      }
	    }
	}
      printf("%s",TTcuono(syono(ttcv(0))).string.s);
    }
}
/*
  if affix then callable is implied
*/
RE(print)
{
  reaffix2callable;
  //if(!(TTcuono(ttcv(0)).NUMBER & ttn_property_type))
  //errxit("non-type passed to PRINT");
  recallable(ttn_nil,func_cu_print);
}
TO(print)
{
  puts("found PRINT");
  totoken(ttn_affix);
  toaffix(PREFIX,1,0,func_re_print);
}
