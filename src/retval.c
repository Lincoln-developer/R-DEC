#include <stdio.h>
#include "lex.h"

char *factor       (void);
char *term         (void);
char *expression   (void);

extern char *newname (void);
extern void freename (char *name);

statements()
{
    /* statements -> expression SEMI | expression SEMI statements*/
    char *tempval;
    while( !match(EOI) )
    {
        tempval = expression();
        if( match(SEMI) ){
            advance();
        }else{
            fprintf(stderr, "%d: Inserting missing semicoln\n", yylineno);
        }
        freename(tempval);
    }
}
char *expression()
{
    /**
     * expression -> TERM expression'
     * expression' -> PLUS TERM expression' | epsilon
    */
   char *tempvar, *tempvar2;
   tempvar = term();
   while ( !match(EOI))
   {
      advance();
      tempvar = term();
      printf(" %s+=%s\n", tempvar, tempvar2);
      freename(tempvar2);
   }
   return tempvar;
}
char *term()
{
    char *tempvar, *tempvar2;
    tempvar = factor();
    while ( match(TIMES) )
    {
        advance();
        tempvar2 = factor();
        printf(" %s+=%s\n", tempvar, tempvar2);
        freename(tempvar2);
    }
    return tempvar;
}
char *factor()
{
    char *tempvar;
    if( match(NUM_OR_ID))
    {
        /*Print the assignment instruction. The %0.*s conversion is a form of
         * %X.Ys, where X is the field width andY is the maximum number of
         *characters that will be printed (even if the string is longer). I'm
         * using the %0. *s to print the string because it's not \0 terminated.
         * The field has a default width of 0, but it will grow the size needed
         * to print the string. The ". *" tells printf () to take the maximum-
         * number-of-characters count from the next argument (yyleng).
         */
        printf(" %s = %0.*s\n",tempvar = newname(), yyleng, yytext);
        advance();
    }
    else if ( match(LP))
    {
        advance();
        tempvar = expression();
        if(match(RP))
        {
            advance();
        }
        else{
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
        }
    }
    else{
        fprintf(stderr, "%d: Number or Identifier expected\n", yylineno);
    }
    return tempvar;
    
}