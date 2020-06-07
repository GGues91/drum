#ifndef TOXY_H
#define TOXY_H
#include "../torecu.h"

/* global x and y during tokenization
   a TO need to manually change tox and toy to reflect
   point in buffer (input string / source file) so next token gets correct tox/toy
 */
extern int tox, toy;

#define toxy_start_x 0
#define toxy_start_y 0

#define toxy { token->x = tox; token->y = toy; }

#endif
