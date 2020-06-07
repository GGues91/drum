#include "parentheses.h"

/*
  use as template for anything depending on RandL
*/
RE(parenR)
{
  Stoken *R; int count;
  R = token; count = -1;
  // find L
  do{
    token = token -> prv;
    ++count;
  }while(!(tt.NUMBER & ttn_randl));
  /* remove R and L 
     and create list or 
     remain the 1st
     token between R and L */
  if(count == 1)
    {
      /* by default if, there is only one element
	 then, do not create a list but, result the
	 one token */
      unlink_tok(token); unlink_tok(R);
      free(token); free(R);
    }
  else if (count > 1)
    {
      puts("creating list");
      Stoken *list_token = malloc(sizeof(Stoken));
      TT(list_token).NUMBER = ttn_list;
      TT(list_token).list.length = count;

      token->prv->nxt = list_token;
      R->nxt->prv = list_token;

      list_token->prv = token->prv;
      list_token->nxt = R->nxt;
      TT(list_token).list.token = token->nxt;

      token->nxt->prv = NULL;
      R->prv->nxt = NULL;

      //unlink(token);
      //unlink(R);
      free(token);
      free(R);

      //seems to work fine...
    }
  else
    {
      //printf("!!!warning; list is empty\n");
      unlink_tok(token); unlink_tok(R);
      free(token); free(R);
    }
}
TO(parenR)
{
  totoken(ttn_randl);
  torandl(randl_parenthesisR,
	  func_re_parenR);
}
TO(parenL)
{
  totoken(ttn_randl);
  torandl(randl_parenthesisL,
	  func_re_parenR);
}
