#ifndef TOKEN_H
#define TOKEN_H
#include <stdint.h>

typedef struct Stoken                Stoken;    /* reserved */

/*-----------------------------
  CONFIGURATION TO PROGRAMMER
------------------------------*/

//-------add/remove typedef for token-type struct (definition is below)
typedef struct Zrandl                Zrandl;    /* reserved */
typedef struct Zaffix                Zaffix;    /* reserved */
typedef struct Zcallable                Zcallable; /* reserved? */
typedef struct Zlist                 Zlist;     /* reserved? */

//-------add/remove Stoken member
#define Stoken__add \
  int x/*row?*/; /* reserved? */		\
  int y/*col?*/; /* reserved? */

//-------add/remove token-type
#define Stoken_dot_type__add \
  Zaffix    affix;  /* reserved */ \
  Zrandl    randl;  /* reserved */ \
  Zcallable    callable;  /* reserved? */ \
  Zlist     list;   /* reserved? */ \
  Zsymbol   symbol; \
  Znumber   number; \
  Zstring   string;

//-------add/remove token-type-number symbol // RENAME as ttn_xxx ?
#define ttn_nil           0x00000000 /* reserved */
#define ttn_eol           0x00000001 /* reserved */ //end of list
#define ttn_randl         0x00000002 /* reserved */
#define ttn_affix         0x00000004 /* reserved */
#define ttn_callable      0x00000008 /* reserved? */
#define ttn_list          0x00000010 /* reserved? */
#define ttn_symbol        0x00000020 /* temporary */
#define ttn_number        0x00000040 /* temporary */ /* 64 */
#define ttn_end_of_line   0x00000080 /* temporary? */
#define ttn_xxx000        0x00000100
#define ttn_xxx001        0x00000200
#define ttn_xxx002        0x00000400
#define ttn_xxx003        0x00000800
#define ttn_string        0x00001000
#define ttn_property_type 0x00002000 //what's this?

//-------add/remove definition of TT
typedef struct Zsymbol Zsymbol;
struct Zsymbol { int NUMBER; char  s; };
typedef struct Znumber Znumber;
struct Znumber { int NUMBER;  int  n; };
typedef struct Zstring Zstring;
struct Zstring { int NUMBER; char *s; };

//-------add/remove definition of TT (RESERVED)
struct Zaffix{ // TT is RESERVED
  int NUMBER;  // HIDDEN
#define NOFIX  0x0000
#define PREFIX 0x0001
#define INFIX  0x0002
#define SUFFIX 0x0004
  int type;
  int arity;
  int precedence;
  //void(*retokenizer)(Stoken *);
  Stoken *(*retokenizer)(Stoken *);
};
struct Zrandl{ // TT is RESERVED ?
  int NUMBER;  // HIDDEN
#define randl_reservedR   -2 //NOTE; R is even
#define randl_reservedL   -1 //NOTE; L is  odd
#define randl_parenthesisR 0
#define randl_parenthesisL 1
#define randl_curlyR       2
#define randl_curlyL       3
#define randl_bracketR     4
#define randl_bracketL     5
#define randl_indentR      6
#define randl_indentL      7
  int rorl; /* use randl_xxxR or randl_xxxL for specific
	       use rorl % 2 == 0 for R
	       use rorl % 2 != 0 for L 
	       rorl is R then rorl + 1 is randl_xxxL */
  //void(*retokenizer)(Stoken *);
  Stoken *(*retokenizer)(Stoken *);
};
//struct Zrl{    // TT is RESERVED ?
//  int NUMBER;  // HIDDEN
//  Stoken *r, *l;
//  void(*retokenizer)(Stoken *);
//};
struct Zcallable{   // TT is RESERVED
  int NUMBER;    // HIDDEN
  int argc;      // count of arguments
  Stoken **argv; // arguments
  int retu;      // what ttn is returned by cutenizer
  Stoken *(*cutenizer)(Stoken *);
};

struct Zlist{ // TT is RESERVED
  int NUMBER; // HIDDEN
  unsigned length; // count of tokens/elements
  Stoken *token; // tokens...name this "list" or "token" or "tokens" ??
};

/* C-function declaration */
void affix2callable_vc(Stoken *token, Stoken *l);
Stoken *unlink_argl(Stoken *token);
int check_types(Stoken *token, int64_t *ttnlst, int len_ttnlst);

/* macro for Stoken for convenience */
#define tt      (token->type)
#define TT(T)   ((T)->type)
#define TTcuono(TOKEN) TT(cuono((TOKEN))) //CUONO be uppercase? or, rename to TT_cuono. vaoca is better name than cuono
#define tta     (token->type.affix)
#define TTA(T)  ((T)->type.affix)
#define ttr     (token->type.randl)
#define TTR(T)  ((T)->type.randl)
#define ttc     (token->type.callable)
#define TTC(T)  ((T)->type.callable)
#define ttcv(I) (token->type.callable).argv[I]
//#define ttcvcuono(INDEX) TT(vaoca(ttc.argv[INDEX])) //WHERE TO PUT THIS???

#define typeck(...)
#define ttnchk(TOKEN,...) check_types(TOKEN, (int64_t[]){__VA_ARGS__}, sizeof((int64_t[]){__VA_ARGS__}) / sizeof(int64_t))

/* linked-list stuff for use on Stoken */
#define unlink_lr(l,r)     (l)->prv->nxt = (r)->nxt, (r)->nxt->prv = (l)->prv, (l)->prv = NULL, (r)->nxt = NULL
#define unlink_tok(TOKEN)      unlink_lr(TOKEN,TOKEN)
#define linkin(src,l,r)    (l) -> nxt = (src), (r) -> prv = (src), (src) -> prv = (l), (src) -> nxt = (r)
#define linkin_lr(a,z,l,r) (l) -> nxt = (a), (r) -> prv = (z), (a) -> prv = (l), (z) -> nxt = (r)
#define linkout(src,l,r)   (src) -> prv = (l) -> prv,

/*
  passed to RE and CU in TORECU/whatever_name.c
 */
struct Stoken
{
  union Utoken_type
  {
    int NUMBER;
    Stoken_dot_type__add
  }type;
  Stoken__add
  struct Stoken *prv,*nxt;
};

#endif
