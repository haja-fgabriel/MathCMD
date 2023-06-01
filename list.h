#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "first.h"
#include "func_val.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <map>

namespace GLOBAL {
    const int SIZEb = 30;
    char beg_disp[SIZEb];
    char beg_default[SIZEb] = "CMD";
    bool FAIL = 0;
    int INPUT_SIZE;
    char *start;
    const double EPS = 1e-8;


    const int Mod1 = 100007, Mod2 = 100021;
    const int Base = 131;

    int Hash_func1(char *s, int lg) {
        int sol = 0;
        char *inc = s;
        while (!isspace(*s) && s-inc < lg) {
            sol = (1LL*sol*Base+*s)%Mod1, s++;
        }

        return sol;
    }
    int Hash_func2(char *s, int lg) {
        int sol = 0;
        char *inc = s;
        while (!isspace(*s) && s-inc < lg)
            sol = (1LL*sol*Base+*s)%Mod2, s++;
        return sol;
    }

    std::map< std::pair<int,int>, double> Num_list;
    std::map< std::pair<int,int>, double> is_func;
    std::map< std::pair<int,int>, double> is_avail;



    struct trie {
        int cod;
        int nfii;
        trie* urm[52];
        trie() {
            cod = -1;
            nfii = 0;
            memset(urm, 0, sizeof(urm));
        }

    };
    trie *inc = new trie;

    char* add_trie(trie *t, int cod, char *s) {
        int x;
        while ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) {
            if (*s >= 'A' && *s <= 'Z')
                x = *s-'A'+27;
            else x = *s-'a';
            if (t -> urm[x] == 0)
                t -> urm[x] = new trie, t -> nfii++;
            t = t -> urm[x];
            s++;
        }
        t -> cod = cod;
        return s;
    }

    char* verif(trie *t, char *s, int &cod) {
        int x;
        while ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) {
            if (*s >= 'A' && *s <= 'Z')
                x = *s-'A'+26;
            else x = *s-'a';
            if (t -> urm[x] == 0)
                return 0;
            t = t -> urm[x];
            s++;
        }
        if ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z'))
            return 0;
        cod = t -> cod;
        return s;
    }

    int deleete_trie(trie *t) {
        int i;
        for (i = 0; i < 52; i++) {
            if (t -> urm[i] == 0) continue;
            if (deleete_trie(t -> urm[i]))
                t -> nfii--;
        }

        if (t -> nfii == 0) {
            delete t;
            return 1;
        }
        return 0;
    }
}

void error() {
    std::cout<<"Bad command.\n\n";
}

char* take_word(char *s, char *z) {
    int l = 0;
    while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'z') || (*s >= '0' && *s <= '9') && s != GLOBAL::start+GLOBAL::INPUT_SIZE)
        z[l++] = *s, s++;
    return s;
}

char* verif(char *s, char *cmp) {
    while (*s == *cmp) s++, cmp++;
    if (*cmp == 0)
        return s;
    return 0;
}

char* usable_func(char *k) {
    while (isspace(*k)) k++;
    if (!((*k >= 'A' && *k <= 'Z') ||
         (*k >= 'a' && *k <= 'z')))
         return 0;
    return k;
}

double parse_value(char *s) {
    int mins = 0;
    if (*s == '-') mins = 1, s++;
    double val = 0, cat = 1e-1;
    while (*s >= '0' && *s <= '9')
        val = val*10+*s-'0', s++;
    if (*s == '.') {
        s++;
        while (*s >= '0' && *s <= '9')
            val = val+(*s-'0')*cat, s++, cat = cat/10;
    }
    if (mins) val = -val;
    return val;
}

void define_help() {
    std::cout << "Usage:\n define [var_name] [value]\n\nwhere:\n  [var_name] - name of variable\n  [value] - number ranging between -999999999.999 and 999999999.999\n\n";
}

void define_error() {
    std::cout << "Bad variable definition. Type \"define help\" for more informaton.\n\n";
}

int define_impossible(char *k) {

    if ((k=usable_func(k))) {
        if (verif(k, "help\0"))
            define_help();
        else {
            char var_num[30] = {0};

            k = take_word(k, var_num);
            while (isspace(*k))k++;
            int lft = GLOBAL::Hash_func1(var_num,strlen(var_num));
            int rgt = GLOBAL::Hash_func2(var_num,strlen(var_num));

            if (!(*k == '-' || (*k >= '0' && *k <= '9')))
                return 1;
            else {
                double d = parse_value(k);

                GLOBAL::is_avail[std::make_pair(lft, rgt)] = 1;
                GLOBAL::Num_list[std::make_pair(lft, rgt)] = d;
            }
        }
        return 0;
    }
    return 1;
}



void print_help() {

}

void print_error() {
    std::cout << "Requested variable does not exist.\n\n";
}

void print_number(double n) {
    std::cout<<n;
    /*std::cout<<(int)n;
    if (n==(int)n) return;
    std::cout<<'.';
    n -= (int)n;
    n *= 10;
    int cnt = 0;
    while (n > GLOBAL::EPS && cnt < 8) {
        std::cout<<(int)n;
        n -= (int)n;
        n *= 10;
        cnt++;
    }*/
}

int print_impossible(char *k) {     // Final version will support expressions
    int lft, rgt;
    if ((k=usable_func(k))) {
        if (verif(k, "help\0"))
            print_help();
        else {
            char var_num[30] = {0};

            k = take_word(k, var_num);

            lft = GLOBAL::Hash_func1(var_num,strlen(var_num));
            rgt = GLOBAL::Hash_func2(var_num,strlen(var_num));

            if (GLOBAL::is_avail[std::make_pair(lft,rgt)] == 0)
                return 1;

            print_number(GLOBAL::Num_list[std::make_pair(lft,rgt)]);
            std::cout << "\n\n";
        }

        return 0;
    }

    return 1;
}

void undefine_error() {
    std::cout << "The specified variable does not exist.\n\n";
}

void undefine_help() {
    std::cout << "Usage:\n undefine [var_name]\n\nwhere:\n [var_name] - name of the specified variable\n\n";
}

int undefine_impossible(char *k) {
    int lft, rgt;
    if ((k=usable_func(k))) {
        if (verif(k, "help\0"))
            undefine_help();
        else {
            char var_num[30] = {0};

            k = take_word(k, var_num);

            lft = GLOBAL::Hash_func1(var_num, strlen(var_num));
            rgt = GLOBAL::Hash_func2(var_num, strlen(var_num));

            if (GLOBAL::is_avail[std::make_pair(lft,rgt)] == 0)
                return 1;

            GLOBAL::Num_list[std::make_pair(lft,rgt)] = 0;
            GLOBAL::is_avail[std::make_pair(lft,rgt)] = 0;
        }

        return 0;
    }

    return 1;
}

void process(char *s, int &STOP) {
    char *k;
    int cod;

    if (*s == 0) return;
    if ((k = GLOBAL::verif(GLOBAL::inc, s, cod)) == NULL) {
        error();
        return;
    } else if (cod == define_val) {
        if (define_impossible(k))
            define_error();
    } else if (cod == print_val) {
        if (print_impossible(k))
            print_error();
    } else if (cod == exit_val) {
        STOP = 1;
    } else if (cod == undefine_val) {
        if (undefine_impossible(k))
            undefine_error();
    } else {
        error();
        return;
    }

}

#endif // LIST_H_INCLUDED
