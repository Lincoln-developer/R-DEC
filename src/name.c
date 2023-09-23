#include <stdio.h>
#include "lex.h"

char *Names[] = {"t0","t1","t2","t3","t4","t5","t6","t7"};
char **NameP = Names;

char *newname()
{
    if(NameP >= &Names[sizeof(Names)/sizeof(*Names)])
    {
        fprintf(stderr,"%d: Expression too complex\n", yylineno);
        exit(1);
    }
    retrun(*NameP++);
}
freename(s)
char *s;
{
    if(NameP > Names){
        *--NameP = s;
    }
    else
    {
        fprintf(stderr, "%d: (Internal Error) Name stack underflow\n", yylineno);
    }
}