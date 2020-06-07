#ifndef RETOKENIZER_H
#define RETOKENIZER_H
#include "token.h"

/* RE interface 
   a RE is C-function named retokenizer
   a retokenizer operate on token and/or token->type
   shortcut to token is err... token
   shortcut to token->type is tt
   eg tt.number = ttn_affix (ttn is token type number)
   a ttn is number for a tt
   convention is name ttn_xxx for tt.xxx
   ttn_yyy for tt.yyy
   xxx may tt.xxx.aaa
   yyy may tt.yyy.bbb
   importance is tt.number is ttn_xxx or ttn_yyy
   if ttn is affix and affix's arity > 0 then rea2ca
   for 0 arity variadic arity is unimplemented
   but a macro like recall may be possible
   eg ( and ) delimited arity */
#define RE(name) Stoken *func_re_##name (Stoken *token)
/* INFIX can PREFIX if ttn of token->prv
   is not TTN 
   re infix can prefix 
   use before reaffix2callabl */
#define reicanp(TTN)\
  { if(!(ttnof(token->prv) & (TTN))) tta.type = PREFIX; }
// convert affix to callable [with arguments?] what happens if no arguments?
#define reaffix2callable\
  { un_slash_ambiguity(token);\
    affix2callable_vc(token,unlink_argl(token)); }
// declare callable with return value (TODO: make this step part of reaffix2callable)
#define recallable(RETU,CUTENIZER)\
  { ttc.retu = RETU;\
    ttc.cutenizer = CUTENIZER; }

/* C-function declaration */
Stoken *unambiguity(Stoken *root);
Stoken *un_slash_ambiguity(Stoken *root);
Stoken *randlrun(Stoken *token);
Stoken *retokenize(Stoken *token);

#endif
