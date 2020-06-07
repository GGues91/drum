tre - a very basic core for an extensible interpreter
      stands for tokenise, retokenise and execute

CONCEPTS
tokens
  basic tokens
    string -> token#string to token
    "1 + 2 * 3" -> 1 , + , 2 , * , 3#whitespace ignored
  advanced tokens
    token -> token#token to token
    1 , + , 2 , * , 3 -> + , *#both containing arguments
  token types
    ttn (token type number, number to say what type)
      0
      1
      2
      4
      8#a power of two number
    types part of core (built-in)
      randl
        says info about a randl
      affix
        says info about an affix
      runnable
        says info about a runnable (function)
        converted from affix
	has arguments
	has return value
	equivalent to a function
      list
        not implemented yet
    types not part of core (non built-in)
      string
      int
      float
      etc
    text to token (tokenizer)
syntactical analysis
  affixes (arguments left,left and right,right)
    basic affixes
      + 2 2#prefix; + -> 2 2
      2 + 2#infix;  2 <- + -> 2
      2 2 +#suffix; 2 2 <- +
    advanced affixes
      precedence and ambiguity (whether left or right is solved)
        1 + 2 * 3 = 9#no precedence; ((1 + 2) * 3)
	  + has same precedence as *
	  solve + then *
        1 + 2 * 3 = 7#precedence; (1 + (2 * 3))
	  + has less precedence than *
	  solve * then +
  Right and Left mechanism (randl)
    ) and (
    B(0 + A(1 + 2 * 3))#A is solved before B is solved
  indentation block
extensions (not part of core)
  add features
  extensions to the core in extension/
    extension/myextension.h
      #include "../torecu.h" //required
      //include dependencies here
      //...
      CU(print); //declaration of executable function
      RE(print); //dec syntactic analyzer
      TO(print); //dec string to text
    extension/myextension.c
      #include "myextension.h"
      TO(myextension){ /*code*/ }#called when token is encountered from string
      RE(myextension){ /*code*/ }#called when randl or affix is encountered performs syntactical analysis
      CU(myextension){ /*code*/ }#called when runnable is encountered (execution)
    token.h
      contains definitions of token type structures and ttn
        #define ttn_myextension 0 //a number in power of two
        ...
        struct Zmyextension{
	       int number; //required
	}
common required features not part of core but included in source
  copy to extension/
    extcommon/def-non-built-in-func.c#def new function
    extcommon/indent-block.c#preceded spacing to denote block
    extcommon/parenthesis-encapsulator.c#} and { (randl)
    extcommon/curly-brace-block.c#} and { (randl)
    extcommon/bracket-encapsulator.c#} and { (randl)
    extcommon/x-y-buffer-coordinate.c#get x and y
    extcommon/blank.c#whitespaces
    extcommon/newline.c#newlines
    extcommon/int.c#c int type
    extcommon/float.c#c float type
