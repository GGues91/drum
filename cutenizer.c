#include "cutenizer.h"

/* cute or no / callable (ie) */
Stoken *cuono(Stoken *token)
{
  static Stoken T;
  if(tt.NUMBER & ttn_callable)
    return ttc.cutenizer(token);
  else
    return token;
}

// todo: return initial token or last?
Stoken *execute(Stoken *token)
{
  while(token)
    {
      if(tt.NUMBER
	 & ttn_callable)
	{
	  ttc.cutenizer(token);
	}
      token = token->nxt;
    }
  return token;
}
