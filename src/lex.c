#include "lex.h"
#include <stdio.h>
#include <ctype.h>

char *yytext =     "";   /*Lexem (not '\0' terminated)*/
int   yyleng =     0;    /* Lexem lenth */
int   yylineno =   0;    /* Input line number */

lex()
{
    static char input_buffer[128];
    char *current;

    current = yytext + yyleng; /*Skip the current lexem*/

    while(1){
        while(!*current){
            /*Get new lines, skipping leading white spaces
            * on the line until a nonblank line is found
            */
           current = input_buffer;
           if(!gets(input_buffer))
           {
            *current = '\0';
            return EOI;
           }
            ++yylineno;
            while(isspace(*current)){
                ++current;
            }
            for(; *current; ++current){
                /*Get the next token */
                yytext = current;
                yyleng = 1;

                switch (*current)
                {
                case EOF:return EOF;
                    break;
                case ';':return SEMI;
                    break;
                case '+':return PLUS;
                    break;
                case '*':return TIMES;
                    break;
                case ')':return RP;
                    break;
                case '(':return LP;
                    break;
                case '\n':
                case '\t':
                case ' ': break;
                default:
                    if (! isalnum(*current))
                    {
                        fprintf(stderr, "Ignoring illegal input <%c>\n", *current);

                    }
                    else
                    {
                        while (isalnum(*current))
                        {
                            ++current;
                            yyleng = current - yytext;
                            return NUM_OR_ID;

                        }
                        break;
                    }
                }

            }
        }
    }

}

static int Lookahead = -1;       /* Lookahead token */
int match(token)
int token;
{
    /* Return true if "token" matches the current Lookahead symbol */
    if(Lookahead == -1)
      Lookahead = lex();

    return token = Lookahead;
}

void advance()
{
    /* Advance the Lookahead to the next input symbol*/
    Lookahead = lex();
}