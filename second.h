#ifndef SECOND_H_INCLUDED
#define SECOND_H_INCLUDED

#include <iostream>
#include <cstring>
#include <cctype>
#include "list.h"
#include "first.h"
#include <cstdlib>

void run() {
    if (GLOBAL::FAIL) {
        std::cout << "Function list failed to initialize.\nPress ENTER/RETURN to close the program.";
        system("pause>nul");
        return;
    }

    int STOP = 0;
    char s[300], *k = s;
    while (STOP == 0) {
        std::cout<<GLOBAL::beg_disp<<">";
        k = s;
        GLOBAL::start = s;
        std::cin.getline(s, sizeof(s));
        GLOBAL::INPUT_SIZE = strlen(s);
        while (isspace(*k)) k++;
        process(k, STOP);
    }
}


#endif // SECOND_H_INCLUDED
