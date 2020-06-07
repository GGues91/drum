#include "miscellaneous.h" //errxit
#include "tokenizer.h"
#include "retokenizer.h"
#include "cutenizer.h"
#include <stdlib.h> //malloc
#include <stdio.h>  //printf
#include <string.h> //strcpy
#include "tok-dclr.h" //edit for adding/removing extensions
#include "lorr.h"     //edit for precedence and ambiguity
#include "macroopt.h" //command line options processor

// maybe put somewhere else
int read_file_add_newlines(char *filename, char **p, char **q)
{
  // text -- remember to terminate with \n or segmentation-fault
  FILE *stream = fopen(filename,"rb");
  if(stream == NULL) return 0;
  fseek(stream,0,SEEK_END);
  long length = ftell(stream);
  *p = calloc(1,/* \n*/1 + length + /* \n*/1 + /* \0*/1);
  **p = '\n'; /* ( ? \n ? */
  fseek(stream,0,SEEK_SET);
  long l = fread((*p)+1,1,length,stream);
  if(l != length) { free(*p); return 0; }
  (*p)[1 + length] = '\n'; /* ) ? \n ? */
  (*p)[2 + length] = '\0';
  *q = (*p) + 2 + length;
  fclose(stream);
  return 1;
}

int main(int argc, char **argv)
{
  char *input_file = "main.tre";
  // load everything onto the stack
  {
    int n = 1;
    macroopt
  case 'h':
    puts ("tre\n\
	-h show help\n\
	-v version\n\
	-f file to execute\n\
	-- stop interpreting options\n");
    exit(0);
    break;
  case 'v':
    puts ("Version 1.0");
    exit(0);
    break;
  case 'f':gotarg
      puts (optarg);
    break;
  case '-':
    macroopt_optyes = 0; //stop processing options when '--' is found
    break;
    remacroopt
    else argv[n++] = argv[optind]; //sort positional arguments in reversed order
    int posend = n;
    while (--n)
      ;//puts (argv[n]);
    //chronological order
    for (n = 1; n < posend; ++n)
      {
	//puts (argv[n]);
	input_file = argv[n];
	printf("input_file: %s\n",input_file);
      }
  }

  // read the file
  char *p,*q;
  if(!read_file_add_newlines(input_file,&p,&q))
    errxit("input file could not be read");

  // tokenize the file
  puts("~~~t");
  Stoken *token;
  token = tokenize(p,q,tok_dclr,len_tok_dclr);

  // retokenize the file
  puts("~~~r");
  token = retokenize(token);

  {
    Stoken *tmp = token;
    while(token)
      {
	if(tt.NUMBER & ttn_list)
	  puts("YEAH found list");
	token = token->nxt;
      }
    token = tmp;
  }
  
  // execute the file
  puts("~~~e");
  execute(token);
  
  return 0;
}
