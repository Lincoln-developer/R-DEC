#include <stdio.h>
#include "lex.h"

/* Basic parser, shows the structure but there is no code generation*/
statements(){
    /**
     * Statements -> expression SEMI
     *             | expression SEMI statements
    */
   expression();

   if(match(SEMI)){
      advance();
   }
   else
      fprintf(stderr, "%d: Inserting missing semicolon\n",yylineno);
   if(!match(EOI)){
      statements();            /*Do another statement */
   } 
}

expression(){
    /* expression -> term expression'*/
    term();
    expr_prime();
}
expr_prime(){
    /*expression' -> PLUS term expression'
    *              | epsilon
    */
   if(match(PLUS)){
      advance();
      term();
      expr_prime();
   }
}
term(){
    /* term -> factor term' */
    factor();
    expr_prime();
}
term_prime(){
    /*term' -> TIMES factor term'
    *        | epsilon
    */
   if(match(TIMES))
   {
      advance();
      factor();
      term_prime();
   }
}
factor()
{
    /*factor -> NUM_OR_ID
    *         | LP expression RP
    */
   if (match(NUM_OR_ID))
      advance();
    
    else if(match(LP))
    {
        advance();
        expression();
        if(match(RP))
        {
            advance();
        }
        else 
          fprintf(stderr, "%d: Mismatched parenthesis \n",yylineno);

    }
    else
      fprintf(stderr, "%d Number or Identifier expected\n", yylineno);
}