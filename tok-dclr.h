#ifndef TOK_DCLR_H
#define TOK_DCLR_H
#include "miscellaneous.h" //errxit
#include "tokenizer.h"
#include "retokenizer.h"
#include "cutenizer.h"
#include <stdlib.h> //malloc
#include <stdio.h>  //printf
#include <string.h> //strcpy

/* add/remove extension source file */
#include "extension/assignment.h"
#include "extension/wav.h"
#include "extension/print.h"
#include "extension/blank.h"
#include "extension/comment.h"
#include "extension/newline.h"
#include "extension/parentheses.h"
#include "extension/string.h"
#include "extension/symbol.h"
#include "extension/number.h"
#include "extension/addition.h"
#include "extension/subtraction.h"
#include "extension/hyphenline.h"
#include "extension/exit.h"

extern Stok_dclr tok_dclr[];
extern int len_tok_dclr;

#endif
