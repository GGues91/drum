#include "tok-dclr.h"

/* add/remove extension token info */
Stok_dclr tok_dclr[]={
//REGEX                LEVEL     LENGTH       FUNCTION
  {"\\+",                  0,         1,      func_to_addition},
  {"_",                    0,         1,      func_to_subtraction},
  {"-+",                   0,         0,      func_to_hyphenline},
  {"WAV",                  0,         0,      func_to_wav},
  {"=",                    0,         0,      func_to_assignment},
  {"print",                0,         0,      func_to_print},
  {"exit",                 0,         0,      func_to_exit},
  {" |\t",                 0,         1,      func_to_blank},
  {"#",                    0,         1,      func_to_comment},
  {"(\n+)|((\r\n)+)",      0,         1,      func_to_newline},
  {"(a-z)|(A-Z)",          1,         1,      func_to_symbol},
  {"0-9+",                 1,   LONGEST,      func_to_number},
  {"\"",                   0,         1,      func_to_string},
  {"\\)",                  0,         1,      func_to_parenR},
  {"\\(",                  0,         1,      func_to_parenL},
};

int len_tok_dclr = sizeof(tok_dclr)/sizeof(Stok_dclr);
