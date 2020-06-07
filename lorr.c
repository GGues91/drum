#include "lorr.h"
#include "tok-dclr.h"

/* LorR (deal with ambiguity and precedence) */
#define L l->type.affix.type
#define R r->type.affix.type
LorR // RETURN of 1 is R-side was retokenized in LorR
     // RETURN of 0 is L-side can retokenize after return
     // solve of R-side is R->type.affix.retokenizer and return of 1
     // solve of L-side is return 0
{
  // case for - or + as PREFIX not INFIX
  if(L == PREFIX && (l->type.affix.retokenizer == func_re_addition
  		     || l->type.affix.retokenizer == func_re_subtraction))
    {
      puts("LorR L == PREFIX and func_re_addition func_re_subtraction");
      return 0;
    }
  if(L == PREFIX && R == INFIX){
    r->type.affix.retokenizer(r);
    return 1;
  }
  // case for precedence for INFIX
  if(L == INFIX && R == INFIX){
    if(l->type.affix.precedence < r->type.affix.precedence){
      r->type.affix.retokenizer(r);
      return 1;
    }
  }
  return 0;
}
#undef R
#undef L
