#include "stdafx.h"
#include "square.h"

const char s = 'S';
const char f = 'F';

#define G_zz 2
#define G_zo 1
#define G_zt 2
#define G_oz 1
#define G_ot 1
#define G_tz 2
#define G_to 1
#define G_tt 2

deque<char> map_list;
int at_S = 0;
int at_F = 0;
int cnt = 0;

template<template<typename> class P = less>
struct compare_pair_second{
    template<class T1, class T2> bool operator()
    (const pair<T1, T2>&left, const pair<T1, T2>&right){
        return P<T2>()(left.second, right.second);
    }
};

int cal_distance(int num){
    return (at_F - num);
}

int main()
{
    // ******* 1. Open file map.txt *******
    FILE* fp = NULL;
    if((fp = fopen("./map.txt", "r")) == NULL){
        perror("{ File open ERROR! }");
        exit(0);
    }
    // ******* Find start point & end point *******
    char c;
    while((c = fgetc(fp)) != EOF){
        map_list.push_back(c);
        if(c == 'S'){
            at_S = cnt;
        }
        if(c == 'F'){
            at_F = cnt;
        }
        //printf("%c", c);
        cnt += 1;
    }
    fclose(fp);
    printf("\nat_F : %d\n", at_F);
    // ***********************************

    // ******* 2. Routing *******
    deque<int> open_list;
    deque<int> close_list;
    map<int, int> temp_map;

    for(int i = 0; i < cnt; i++){
        if(map_list.at(i) == 'o'){
            close_list.push_back(i);
        }
    }

    int zz = 0; int zo = 0; int zt = 0; int oz = 0; int ot = 0;
    int tz = 0; int to = 0; int tt = 0;

    int F_zz = 0; int F_zo = 0; int F_zt = 0; int F_oz = 0; int F_ot = 0;
    int F_tz = 0; int F_to = 0; int F_tt = 0;

    int H_zz = 0; int H_zo = 0; int H_zt = 0; int H_oz = 0; int H_ot = 0;
    int H_tz = 0; int H_to = 0; int H_tt = 0;

    bool is_zz = false; bool is_zo = false; bool is_zt = false;
    bool is_oz = false; bool is_ot = false; bool is_tz = false;
    bool is_to = false; bool is_tt = false;

    deque<char>::iterator iter;
    deque<char>::iterator iter2;

    int prev_i = 0;

    bool is_Sero = false; bool is_Garo = false;

    //printf("%c", *iter_map);
    printf("\ncount : %d\n\n", cnt);
    printf("at_F : %d\n", at_F);
    printf("at_S : %d\n", at_S);
    int i = at_S;
    // start point : at_S -> 72
    for(int x = 0; x < 56; x++){
        printf("******************\n");
        printf("i : %d\n", i);
        prev_i = i;
        is_Sero = false; is_Garo = false;
        zz = i-72; zo = i-71; zt = i-70;
        oz = i-1; ot = i+1;
        tz = i+70; to = i+71; tt = i+72;
        Square* sq = new Square(zz, zo, zt, oz, ot, tz, to, tt);
        printf("\nzz : %d | zo : %d | zt : %d\n", zz, zo, zt);
        printf("oz : %d | SP : %d | ot : %d\n", oz, i, ot);
        printf("tz : %d | to : %d | tt : %d\n\n", tz, to, tt);
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        int n = 8;
        F_zz = 0; F_zo = 0; F_zt = 0; F_oz = 0; F_ot = 0;
        F_tz = 0; F_to = 0; F_tt = 0;
        H_zz = 0; H_zo = 0; H_zt = 0; H_oz = 0; H_ot = 0;
        H_tz = 0; H_to = 0; H_tt = 0;
        is_zz = false; is_zo = false; is_zt = false; is_oz = false;
        is_ot = false; is_tz = false; is_to = false; is_tt = false;
        for(unsigned int z = 0; z < close_list.size(); z++){
            if(n == 0) break;
            if(close_list.at(z) == zz){
                printf("zz\n");
                is_zz = true;
                n--;
            }
            else if(close_list.at(z) == zo){
                printf("zo\n");
                is_zo = true;
                n--;
            }
            else if(close_list.at(z) == zt){
                printf("zt\n");
                is_zt = true;
                n--;
            }
            else if(close_list.at(z) == oz){
                printf("oz\n");
                is_oz = true;
                n--;
            }
            else if(close_list.at(z) == ot){
                printf("ot\n");
                is_ot = true;
                n--;
            }
            else if(close_list.at(z) == tz){
                printf("tz\n");
                is_tz = true;
                n--;
            }
            else if(close_list.at(z) == to){
                printf("to\n");
                is_to = true;
                n--;
            }
            else if(close_list.at(z) == tt){
                printf("tt\n");
                is_tt = true;
                n--;
            }
        }
        printf("n : %d\n", n);

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        if(zz < 0){
            printf("[ zz < %d, %d > reaches the wall! ]\n", i, zz);
        }
        else{
            if(is_zz == false){
                H_zz = cal_distance(sq->zero_zero);
                F_zz = H_zz + G_zz;
                temp_map.insert(make_pair(zz, F_zz));
            }
        }
        if(zo < 0){
            printf("[ zo < %d, %d > reaches the wall! ]\n", i, zo);
        }
        else{
            if(is_zo == false){
                H_zo = cal_distance(sq->zero_one);
                F_zo = H_zo + G_zo;
                temp_map.insert(make_pair(zo, F_zo));
            }
        }
        if(zt < 0){
            printf("[ zt < %d, %d > reaches the wall! ]\n", i, zt);
        }
        else{
            if(is_zt == false){
                H_zt = cal_distance(sq->zero_two);
                F_zt = H_zt + G_zt;
                temp_map.insert(make_pair(zt, F_zt));
            }
        }
        if(oz < 0){
            printf("[ oz < %d, %d > reaches the wall! ]\n", i, oz);
        }
        else{
            if(is_oz == false){
                H_oz = cal_distance(sq->one_zero);
                F_oz = H_oz + G_oz;
                temp_map.insert(make_pair(oz, F_oz));
            }
        }
        if(ot < 0){
            printf("[ ot < %d, %d > reaches the wall! ]\n", i, ot);
        }
        else{
            if(is_ot == false){
                H_ot = cal_distance(sq->one_two);
                F_ot = H_ot + G_ot;
                temp_map.insert(make_pair(ot, F_ot));
            }
        }
        if(tz < 0){
            printf("[ tz < %d, %d > reaches the wall! ]\n", i, tz);
        }
        else{
            if(is_tz == false){
                H_tz = cal_distance(sq->two_zero);
                F_tz = H_tz + G_tz;
                temp_map.insert(make_pair(tz, F_tz));
            }
        }
        if(to < 0){
            printf("[ to < %d, %d > reaches the wall! ]\n", i, to);
        }
        else{
            if(is_to == false){
                H_to = cal_distance(sq->two_one);
                F_to = H_to + G_to;
                temp_map.insert(make_pair(to, F_to));
            }
        }
        if(tt < 0){
            printf("[ to < %d, %d > reaches the wall! ]\n", i, to);
        }
        else{
            if(is_tt == false){
                H_tt = cal_distance(sq->two_two);
                F_tt = H_tt + G_tt;
                temp_map.insert(make_pair(tt, F_tt));
            }
        }

        vector<pair<int, int>> vec(temp_map.begin(), temp_map.end());
        sort(vec.begin(), vec.end(), compare_pair_second<less>());

        close_list.push_back(i); // start point

        i = vec.begin()->first;
        //is_Sero_minus
        int temp = i - prev_i;
        if(temp < 0){
            if(temp == -1){
                is_Garo = true;
                printf("[ Move Garo Minus ]\n");
            }
            else if(temp == -71){
                is_Sero = true;
                printf("[ Move Sero Minus ]\n");
            }
        }
        else{
            if(temp == 1){
                is_Garo = true;
                printf("[ Move Garo ]\n");
            }
            else if(temp == 71){
                is_Sero = true;
                printf("[ Move Sero ]\n");
            }
        }

        open_list.push_back(i); // new start point
        printf("open_list : %d\n\n", open_list.back());
        vec.erase(vec.begin());

        iter = map_list.begin();
        iter += i+1;
        if(temp < 0){
            if(((i-1) > 0) && is_Garo == true){
                printf("map : %c\n", map_list.at(i-1)); // check 'o'
            }
            else if(((i-71) > 0) && is_Sero == true){
                printf("map : %c\n", map_list.at(i-71)); // check 'o'
            }
        }
        else{
            if(is_Garo == true){
                printf("map : %c\n", map_list.at(i+1)); // check 'o'
            }
            else if(is_Sero == true){
                printf("map : %c\n", map_list.at(i+71)); // check 'o'
            }
        }

        vector<pair<int, int>>::iterator iter_vec = vec.begin();

        //printf("F_tz : %d, H_tz : %d, G_tz : %d\n", F_tz, H_tz, G_tz);
        //printf("F_tt : %d, H_tt : %d, G_tt : %d\n", F_tt, H_tt, G_tt);
        for(int j = 0; j < n-1; j++){
            if(iter_vec->first >= 0 && iter_vec->first < cnt){
                printf("close_list : %d\n", iter_vec->first);
                if(temp < 0){
                    if((is_Sero == true) && ((i-71) > 0)){
                        close_list.push_back(iter_vec->first); // store other point
                    }
                }
                else{
                    if((is_Garo == true) && (map_list.at(i+1) != 'o')){
                        close_list.push_back(iter_vec->first); // store other point
                    }
                    else if((is_Sero == true) && (map_list.at(i+71) != 'o')){
                        close_list.push_back(iter_vec->first); // store other point
                    }
                }
                iter_vec += 1;
            }
        }

        if(map_list.at(i+1) == 'o'){
            iter2 = map_list.erase(iter-1);
            map_list.insert(iter-1, '*');
        }
        else{
            iter2 = map_list.erase(iter);
            map_list.insert(iter, '*');
        }

        delete sq;
        temp_map.clear();

        if(map_list.at(i) == f){
            break;
        }
        printf("******************\n");
    }

    printf("\n\n");
    for(int i = 0; i < cnt; i++){
        printf("%c", map_list.at(i));
    }
    printf("\n\n");
}




