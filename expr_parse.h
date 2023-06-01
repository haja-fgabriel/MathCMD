#ifndef EXPR_PARSE_H_INCLUDED
#define EXPR_PARSE_H_INCLUDED

namespace PARSER
{
    char *cursor;

    double fact();
    double func();
    double expr(int cod, double *param);
    double sum();


    double fact()
    {

    }

    double sum()
    {

    }
    double func(int cod, double *param)
    {

    }

    double expr()
    {

        while (*cursor == '+' || *cursor == '-')
    }
}



#endif // EXPR_PARSE_H_INCLUDED
