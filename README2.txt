TRE is an interpreter where the core of syntactical
analysis is provided but, you write the execution
and behavior of TRE. TO for tokenize is a step
where text is convereted to tokens. RE for
retokenize is where BASIC tokens are convereted
to ADVANCED tokens; a BASIC token was a token
directly derived from text whereas, an ADVANCED
token was a token created out of another token and,
syntactical analysis is done based on ADVANCED tokens.
EX for execute executes the resulting doubly linked list
of tokens produced in the first two steps.
each token has a TTN associated which,
is an acronym for token type number to identify it.
a token is essentially a type and,
some types are inbuilt aka hidden these, include:
affix,randl,list,runnable and, using this same
mechanism you add new types like int or string.
how to use?
you put your code in the extension directoy
(see: extension/example.c) and,
include their header counterparts in tok-dclr.h.
you must also specify information for the tokenizer
so it can recognize BASIC tokens and, also you must
specify information for the syntactic analyzer in
tok-dclr.c. you add/remove types in token.h.







-------------
WHAT IS THIS?
INTERPRETER named TORECU for
the three stages of interpretation
1 is TO for tokenize
2 is RE for retokenize
3 is CU for exeCUtion

---------------------
---------------------
---------------------
---------------------
INTERPRETER 2.0 -----
--------------- -----
--------------- -----
--------------- -----

(scroll to below to ignore some rant)

---RANT0
ttnSproperty_type
& and | is xor
e.g. ttnSnumber | ttnSproperty_type
e.g. ttnSstring | ttnSproperty_type
but! ttnSblank  //blank is not a type
this is convenient way to test if
some ttn is a *type* whatever a *type* is
we can call it a property to denote all
types available in the TORECU
like a function like PRINT may check only
to see that the argument has a ttnSproperty_type
and then investigate which type it is
otherwise it can cancel and exit with error
because no ttn appropriate was provided as argument...
instead of cycling through ttns in a list
to see whether one is a type we can just xor
every type with something like ttnSproperty_type
but this means that we must use & instead of ==
for comparison of equality and !(ttn & some_ttn)
for comparison of non-equality


---RANT1
precedence
//main.c
LorR
{
  if(L == INFIX && R == INFIX){
    if(l->type.affix.precedence < r->type.affix.precedence){
      r->type.affix.retokenizer(r);
      return 1;
    }
  }
}

---RANT2
R and L
RE(parenR)
{
  Stoken *R; int count;
  R = token; count = -1;
  do{
    token = token -> prv;
    ++count;
  }while(tt.NUMBER != ttnSrandl);
  /* remove R and L 
     and create list or 
     remain the 1st
     token between R and L */
  if(count == 1)
    {
      unlink(token); unlink(R);
      free(token); free(R);
    }
  else
    {
      errxit("count != 1 is unaccounted for");
    }
}
TO(parenR)
{
  totoken(ttnSrandl);
  tt.randl.rorl = randl_parenthesisR;
  tt.randl.retokenizer = REparenR;
  tomatch; MSGtorecu("");
}
TO(parenL)
{
  totoken(ttnSrandl);
  tt.randl.rorl = randl_parenthesisL;
  tt.randl.retokenizer = REparenR;
  tomatch; MSGtorecu("");
}

---RANT3
1return of CU as non-list rather singular
this works because innermost affix is solved first
//division.c
CU(division)
{
  static Stoken RET; // static
  RET.type.NUMBER = ttnSnumber;
  RET.type.number.n = TT(vaoca(ttc.argv[0])).number.n
  		      / TT(vaoca(ttc.argv[1])).number.n;
  return &RET;
}

---RANT4
INFIX as - or + canbe PREFIX or INFIX on context
-2 * 3 is - as INFIX at first then token->prv->type != ttnSnumber
thusso - be PREFIX
this is way to NEGATE as -3
//main.c
LorR
{
  if(L == PREFIX
     && (l->type.affix.retokenizer == REsubtraction)){
    return 0;
  }
}
//subtraction.c
CU(subtraction)
{
  static Stoken RET;
  RET.type.NUMBER = ttnSnumber;
  int c;
  for(c = 0; c < ttc.argc; ++c)
    RET.type.number.n -= vaoca(ttc.argv[c])->type.number.n;
  return &RET;
}
RE(subtraction)
{
  /* make to prefix as negation or +
     lorr(l,r) is conditional in main.c */
  if(ttn_of_vaoca(token->prv) != ttnSnumber)
      tta.type = PREFIX;
  rea2ca;
  ttc.cutenizer = CUcutenizer;
}
TO(subtraction)
{ /* code */ }

---CONCEPT
AFFIX is PREFIX, SUFFIX or INFIX
RandL is pair of token eg ( and ) or { and }
AFFIX use un_slash_ambiguity or unambiguity
RandL use randlrun
       unambiguity is implemented (   basic affix)
un_slash_ambiguity is implemneted (advanced affix)
          randlrun is implemented
what about precedence?
that is possible using un_slash_ambiguity and LorR{}
un_slash_ambiguity in retokenizer.c
LorR{} in main.c but macro in retokenizer.h
in 1.0 that (precedence) isn't possible
1.0 use unambiguity not un_slash_ambiguity (un/ambiguity is unambiguity and ambiguity)
un_slash_ambiguity imply LorR{}
precedence is ~ambiguity in LorR{}
LorR is L-side or R-side and RandL isn't same
LorR and RandL is different
LorR is for precedence/ambiguity
RandL is for pair of token which match
RandL and AFFIX is CONCEPT as high-level
       unambiguity is implementation of    BASIC AFFIX
un_slash_ambiguity is implementation of ADVANCED AFFIX imply precedence using LorR{}
          randlrun is implementation of RandL

---INTERFACE to programmer

TO is tokenize
RE is retokenize
CU is cutenize for execute

  tokenize is  TEXT to TOKEN //tokenize() in tokenizer.c
retokenize is TOKEN to TOKEN //randlrun() and un_slash_ambiguity() in retokenizer.c
	      	       	     //randlrun() is implemented un_slash_ambiguity() is implemented
			     //and unambiguity() is implemented

TO declaration use Stok_dclr
TO  definition use TO(whatever_name)
//torecu/TORECU/whatever_name.c
    #include "TORECU/whatever_name.c"
    Stok_dclr tok_dclr[]={{.regex="foo",
			   .level=0,
			   .length=3,
			   .tokenizer=TOwhatever_name}};
RE declaration use token->type.affix.retokenizer
RE  definition use RE(whatever_name)
//torecu/TORECU/whatever_name.c
    RE(whatever_name){
	// CODE
    }
CU declaration use token->type.callable.cutenizer
CU  definition use CU(whatever_name)
//torecu/TORECU/whatever_name.c
    CU(whatever_name){
	// CODE
    }

Stoken is ll in token.h
TO(name){} is Stoken *TOname(Stokenizer *tokenizer){}
RE(name){} is Stoken *REname(Stoken *token)        {}
CU(name){} is Stoken *CUname(Stoken *token)        {}

              INPUT/OUTPUT             
TEXT -> TO -> TOKEN -> RE -> TOKEN -> CU
Stokenizer -> TO() -> Stoken -> RE() -> Stoken -> CU()

add/removal of TORECU
torecu/ is directory to torecu as base of code like underlyingment of algorithm as torecu
torecu/TORECU/ is directory to TORECU in term of TO and RE and CU
some torecu is defined within torecu/TORECU/
TORECU is TO and RE and CU
torecu/TORECU/whatever_name.c contain TO(){} [and RE(){} [and CU(){}]]
where [ and ] denote optionality
least is           TO(){}
least of second is RE(){}
least of  third is CU(){}
for TO is TO-interface to programmer
    to for tokenizer ; shortcut to tokenizer whichis passed to TO(){}
    totoken(TTN)
    tomatch
for RE is RE-interface to programmer
for CU is CU-interface to programmer

------------------------
------------------------
------------------------
------------------------
---INTERPRETER 1.0 -----
------------------ -----
------------------ -----
------------------ -----

(scroll to below to ignore some rant)

---RANT0
TO is for translation of TEXT/STR to TOKEN
RE is for translation of    TOKEN to TOKEN this is syntactical analysis or parsing
syntax is implemented in the same way as non-syntax
there is a token->type for affix and a token->type for integer as well
however integer is not defined by default
the point is it's the same interface for the underlying TORECU interpreter as for
adding new stuff like an integer type
one can also extend the interpreter in this way, just like one'd extend one's own language application
however to extend the interpreter one may need to modify retokenizer.c and/or retokenizer.h
otherwise one just adds new types to token.h and writes their TO, RE and CU in torecu/whatever_name.c
and includes that in main.c priorto the definition of tok_dclr
eg input is "2 * 2" then output of tokenize is token(2) and token(*) and token(2)
then during retokenize the input is these 3 token
it is much easier to make sense that this is an arithmetic operation
because 2 can be labeled a number token and * can be labeled an arithmetic operator token
and 2 can be labeled a number token...
say you loop through the tokens returned by tokenize and only check on the
arithmetic operators and ignore the numbers
REtokenization use Zaffix and Zrandl
a Zaffix can translate to a Zcallable for CUtenization during REtokenization
a Zrandl is basically a retokenizer type like Zaffix
but Zaffix is for SUFFIX PREFIX and INFIX
Zrandl is for ( and ) or { and } etc
anything which got a R-side and a matching L-side like ( and ) in (2 + 3) * 4
the implementation of code which uses Zrandl is specifically randlrun
and the implementation of code which uses Zaffix is specifically un_slash_ambiguity/unambiguity
un_slash_ambiguity is not implemented in INTERPRETER 1.0

---RANT1
for typecheck / ttnchk
a ttnSeol to signify end of list or end of Stoken ll
instead of using a NULL pointer / value for end of list
this way typecheck / ttnchk don't need to check for a NULL
but can keep its code like something as this,
if(tt.NUMBER == ttnSinteger) return TYPE_CHECK_OK;
if tt.NUMBER is ttnSeol then TYPE_CHECK is not OK
and no extra condition for NULL was needed because ttnSeol would occur before a NULL toward the nxt-direction
and ttnSeol type is not useable as anything but a dummy
as long as a type like ttnSeol or type-number like that
it can act as a dummy which is unusable as anything else than to signify end of list
ttnSeol rather than NULL
however this require that ttnSeol is ensured at beg and end of each ll
a ll can be considered a list of Stoken
say,
EOL a b c d e f EOL
that is the entire file of input
EOL is prepended and appended at beg and end

---RANT2
TTN is power of 2
TTNxxx | TTNyyy iseg 1000 | 0100
...what's the point of this anyway??

TEXT -> TOKENIZE -> RETOKENIZE -> CUTENIZE -> DONE

focus is ll of Stoken as token


---CONCEPT
AFFIX is PREFIX, SUFFIX or INFIX
RandL is pair of token eg ( and ) or { and }
AFFIX use un_slash_ambiguity or unambiguity
RandL use randlrun
       unambiguity is implemented   (   basic affix)
un_slash_ambiguity is unimplemneted (advanced affix)
          randlrun is unimplemented
what about precedence?
that is possible using un_slash_ambiguity and LorR{}
un_slash_ambiguity in retokenizer.c
LorR{} in main.c but macro in retokenizer.h
in 1.0 that (precedence) isn't possible
1.0 use unambiguity not un_slash_ambiguity (un/ambiguity is unambiguity and ambiguity)
un_slash_ambiguity imply LorR{}
precedence is ~ambiguity in LorR{}
LorR is L-side or R-side and RandL isn't same
LorR and RandL is different
 LorR is for precedence/ambiguity
RandL is for pair of token which match
RandL and AFFIX is CONCEPT as high-level
       unambiguity is implementation of    BASIC AFFIX
un_slash_ambiguity is implementation of ADVANCED AFFIX imply precedence using LorR{}
          randlrun is implementation of RandL

---INTERFACE to programmer

TO is tokenize
RE is retokenize
CU is cutenize

  tokenize is  TEXT to TOKEN //tokenize() in tokenizer.c
retokenize is TOKEN to TOKEN //randlrun() and un_slash_ambiguity() in retokenizer.c
	      	       	     //randlrun() and un_slash_ambiguity() are unimplemented
			     //but unambiguity() is implemented

TO declaration use Stok_dclr
TO  definition use TO(whatever_name) //torecu/torecu/whatever_name.c
    #include "torecu/whatever_name.c"
    Stok_dclr tok_dclr[]={{.regex="foo",
			   .level=0,
			   .length=3,
			   .tokenizer=TOwhatever_name}};
RE declaration use token->type.affix.retokenizer
RE  definition use RE(whatever_name) //torecu/torecu/whatever_name.c
    RE(whatever_name){
	// CODE
    }
CU declaration use token->type.callable.cutenizer
CU  definition use CU(whatever_name) //torecu/torecu/whatever_name.c
    CU(whatever_name){
	// CODE
    }

Stoken is ll in token.h
TO(name){} is Stoken *TOname(Stokenizer *tokenizer){}
RE(name){} is Stoken *REname(Stoken *token)        {}
CU(name){} is Stoken *CUname(Stoken *token)        {}

              INPUT/OUTPUT             
TEXT -> TO -> TOKEN -> RE -> TOKEN -> CU
Stokenizer -> TO() -> Stoken -> RE() -> Stoken -> CU()

add/removal of torecu
torecu/ is directory to torecu as base of code like underlyingment of algorithm as torecu
torecu/TORECU/ is directory to TORECU in term of TO and RE and CU
some torecu is defined within torecu/TORECU/
TORECU is TO and RE and CU
torecu/TORECU/whatever_name.c contain TO(){} [and RE(){} [and CU(){}]]
where [ and ] denote optionality
least is           TO(){}
least of second is RE(){}
least of  third is CU(){}
for TO is TO-interface to programmer
    to for tokenizer ; shortcut to tokenizer whichis passed to TO(){}
    totoken(TTN) 
    tomatch
for RE is RE-interface to programmer
for CU is CU-interface to programmer
