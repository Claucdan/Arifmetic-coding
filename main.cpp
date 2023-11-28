#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "gmp.h"
char* from_int_to_char_point(int host){
    int size=std::to_string(host).size();
    char* buf=new char[size];
    for(int i=size-1;i>=0;i--){
        buf[i]=host%10+48;
        host/=10;
    }
    return buf;
}

bool comp(std::pair<char, int>& first, std::pair<char, int>& second) {
    if (first.second == second.second)
        return first.first < second.first;
    else
        return first.second < second.second;
}

class Arifm {
public:
    std::string text;
    std::vector<std::pair<char, int>> abc;
    std::vector<std::pair<char, mpf_t>> probability_of_abc;
    void _abc_creat();
    void _probability_of_abc_creat();
    mpf_t** _define_segments();
    void _arithmetic_coding();
    int _find(char& sym);

};
void Arifm::_abc_creat() {
    std::cin >> text;
    for (int i = 0; i < text.size(); ++i) {
        int j = 0;
        bool flag = true;
        for (j; j < abc.size(); ++j) {
            if (abc[j].first == text[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            abc.push_back(std::make_pair(text[i], 1));
        }
        else {
            abc[j].second++;
        }
    }
    sort(abc.begin(), abc.end(), comp);
}
void Arifm::_probability_of_abc_creat() {
    probability_of_abc.resize(abc.size());
    mpf_t size;
    mpf_init_set_ui(size,text.size());
    printf("Probility\n");
    for (int i = 0; i < abc.size(); ++i) {
        probability_of_abc[i].first=abc[i].first;
        mpf_init(probability_of_abc[i].second);
        mpf_t buffer;
        mpf_init_set_ui(buffer,abc[i].second);
        mpf_div(probability_of_abc[i].second,buffer,size);
        mpf_clear(buffer);
        printf("%c",abc[i].first);
        gmp_printf(" -> %.30Ff\n",probability_of_abc[i].second);
    }
    printf("\n");
    mpf_clear(size);
}

mpf_t** Arifm::_define_segments(){
    mpf_t** segment=new mpf_t*[probability_of_abc.size()];
    mpf_t l;
    mpf_init_set_ui(l,0);
    for (int i = 0; i < probability_of_abc.size(); i++) {
        segment[i]=new mpf_t[2];
        mpf_init_set(segment[i][0],l);
        mpf_add(l,l,probability_of_abc[i].second);
        mpf_init_set(segment[i][1],l);
        printf("%c  ",abc[i].first);
        gmp_printf("[%.30Ff ; %.30Ff)\n",segment[i][0],segment[i][1]);
    }
    return  segment;
}

void Arifm::_arithmetic_coding(){
    mpf_t** segment = _define_segments();
    mpf_t left,right;
    mpf_init_set_si(left,0);
    mpf_init_set_si(right,1);
    printf("\n");
    for (int i = 0; i < text.size(); i++) {
        char symb = text[i];
        mpf_t raz,um_right,um_left;
        mpf_inits(raz,um_right,um_left,NULL);
        mpf_sub(raz,right,left);
        mpf_mul(um_right,raz,segment[_find(symb)][1]);
        mpf_mul(um_left,raz,segment[_find(symb)][0]);
        mpf_add(right,left,um_right);
        mpf_add(left,left,um_left);
        printf("%c  -> ",symb);
        gmp_printf("[%.30Ff ; %.30Ff)\n",left,right);
    }
    mpf_add(left,right,left);
    mpf_div_ui(left,left,2);
    gmp_printf("\n\nResult of decoding:    %.21Ff\n\n",left);
}


int Arifm::_find(char& sym) {
    for (int i = 0; i < probability_of_abc.size(); i++) {
        if (sym == probability_of_abc[i].first) {
            return i;
        }
    }
}

int main(){
    mpf_set_default_prec(256);
    Arifm host;
    host._abc_creat();
    host._probability_of_abc_creat();
    host._arithmetic_coding();
    return 0;
}

