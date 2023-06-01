#ifndef FIRST_H_INCLUDED
#define FIRST_H_INCLUDED

#include "list.h"
#include "func_val.h"
#include <fstream>
#include <cstring>


char* check_word(char *k) {
    while (isspace(*k)) k++;
    if (*k != '=') return 0;
    else k++;
    while (isspace(*k)) k++;
    if (*k == 0) return 0;
    return k;
}

void init() {
    std::ifstream f("param.ini");

    char s[300], *k, *cpy;
    strcpy(GLOBAL::beg_disp, GLOBAL::beg_default);

    // Aici se introduc denumirile functiilor cu tot cu codurile sale de confirmare
    GLOBAL::add_trie(GLOBAL::inc, define_val, "define");
    GLOBAL::add_trie(GLOBAL::inc, undefine_val, "undefine");
    GLOBAL::add_trie(GLOBAL::inc, print_val, "print");
    GLOBAL::add_trie(GLOBAL::inc, exit_val, "exit");

    while (f.getline(s, sizeof(s))) {
        k = s;
        while (*k == ' ') k++;
        if (*k == '#') continue;
        char second[GLOBAL::SIZEb];
        k = take_word(k, second);
        if (strcmp(second, "before") == 0) {
            if ((cpy=check_word(k)) != NULL) {
                k = cpy;
                strcpy(GLOBAL::beg_disp, k);
            }
        } else if (strcmp(second,"func_list") == 0) {
            if ((cpy=check_word(k)) != NULL) {
                k = cpy;

                int STOP = 0, waste;
                int l = 0;
                while (STOP == 0) {
                    if (*k == '{') {
                        l = 0;
                        memset(second, 0, sizeof(second));
                    }
                    else if ((*k >= 'a' && *k <= 'z') || (*k >= 'A' && *k <= 'Z'))
                        second[l++] = *k;
                    else if (*k == ',' || *k == '}') {

                        if (GLOBAL::verif(GLOBAL::inc,second,waste) == NULL) {
                            GLOBAL::FAIL = 1;
                            STOP = 1;
                        }
                        l = 0;
                        memset(second, 0, sizeof(second));
                        if (*k == '}')
                            STOP = 1;
                    }
                    k++;
                }
            }
        }
    };

    f.close();
}



#endif // FIRST_H_INCLUDED
