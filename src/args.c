#include <stdio.h>
#include "lex.h"

void factor       (char *tempvar);
void term         (char *tempvar);
void expression   (char *tempvar);

extern char *newname (void);
extern void freename (char *name);

statements()
{
    /* statements -> expression SEMI | expression SEMI statements*/

    char *tempvar;

    while(!match(EOI))
    {
        expression(tempvar = newname());
        freename(tempvar);

        if(match(SEMI))
           advance();
        else
           fprintf(stderr, "%d: Inserting missing semicolon", yylineno);
    }
}
void expression(tempvar)
char *tempvar;
{
    /***
     * expression -> term expression'
     * expression' -> PLUS term expression' | epsilon
     * 
    */
   char *tempvar2;

   term(tempvar2);
   while (match(PLUS))
   {
      advance();
      term(tempvar2 = newname());
      printf("  %s += %s\n", tempvar2, tempvar);
      freename(tempvar2);
   }
}
void term(tempvar)
char *tempvar;
{
    char *tempvar2;
    factor(tempvar2);
    while(match(TIMES))
    {
        advance();
        factor(tempvar2 = newname());
        printf("  %s += %s\n", tempvar2, tempvar);
        freename(tempvar2);
    }
}
void factor(tempvar)
char *tempvar;
{
    if(match(NUM_OR_ID))
    {
        printf("  %s = %0.*s\n",tempvar,yyleng, yytext);
        advance();
    }
    else if (match(LP))
    {
        advance();
        expression(tempvar);
        if(match(RP))
        {
            advance();
        }
        else 
           fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
       fprintf(stderr, "%d: Number or Identifier expected\n", yylineno);
}