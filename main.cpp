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
        if(c == 'F'){
            at_F = cnt;
        }
        printf("%c", c);
        cnt += 1;
    }
    fclose(fp);
    printf("\nat_F : %d\n", at_F);
    // ***********************************

    // ******* 2. Routing *******
    //deque<int> open_list;
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

    //printf("%c", *iter_map);
    printf("\ncount : %d\n\n", cnt);
    //for(int i = 0; i < cnt; i++){
    //    Square* sq = new Squre(map.at(i));
    //}
    int i = 0;
    // start point : 71
    while(i < 100){
        zz = i; zo = i+1; zt = i+2;
        oz = i+70; ot = i+72;
        tz = i+140; to = i+141; tt = i+142;
        Square* sq = new Square(zz, zo, zt, oz, ot, tz, to, tt);
        int n = 8;
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

        if(is_zz == true){
            H_zz = 1000;
        }
        else{
            H_zz = cal_distance(sq->zero_zero);
        }
        if(is_zo == true){
            H_zo = 1000;
        }
        else{
            H_zo = cal_distance(sq->zero_one);
        }
        if(is_zt == true){
            H_zt = 1000;
        }
        else{
            H_zt = cal_distance(sq->zero_two);
        }
        if(is_oz == true){
            H_oz = 1000;
        }
        else{
            H_oz = cal_distance(sq->one_zero);
        }
        if(is_ot == true){
            H_ot = 1000;
        }
        else{
            H_ot = cal_distance(sq->one_two);
        }
        if(is_tz == true){
            H_tz = 1000;
        }
        else{
            H_tz = cal_distance(sq->two_zero);
        }
        if(is_to == true){
            H_to = 1000;
        }
        else{
            H_to = cal_distance(sq->two_one);
        }
        if(is_tt == true){
            H_tt = 1000;
        }
        else{
            H_tt = cal_distance(sq->two_two);
        }

        F_zz = H_zz + G_zz; F_zo = H_zo + G_zo; F_zt = H_zt + G_zt;
        F_oz = H_oz + G_oz; F_ot = H_ot + G_ot; F_tz = H_tz + G_tz;
        F_to = H_to + G_to; F_tt = H_tt + G_tt;

        temp_map.insert(make_pair(zz, F_zz));
        temp_map.insert(make_pair(zo, F_zo));
        temp_map.insert(make_pair(zt, F_zt));
        temp_map.insert(make_pair(oz, F_oz));
        temp_map.insert(make_pair(ot, F_ot));
        temp_map.insert(make_pair(tz, F_tz));
        temp_map.insert(make_pair(to, F_to));
        temp_map.insert(make_pair(tt, F_tt));
        vector<pair<int, int>> vec(temp_map.begin(), temp_map.end());
        sort(vec.begin(), vec.end(), compare_pair_second<less>());

        //open_list.push_back(vec.begin()->first); // new start point
        i = vec.begin()->first - 71;
        printf("open_list : %d\n\n", vec.begin()->first);
        vec.erase(vec.begin());
        vector<pair<int, int>>::iterator iter_vec = vec.begin();
        close_list.push_back(i+70); // start point
        for(int j = 0; j < 7; j++){
            printf("close_list : %d\n", iter_vec->first);
            close_list.push_back(iter_vec->first); // other trash point
            iter_vec += 1;
        }
        //temp_list.clear();
        printf("i : %d\n", i);
        iter = map_list.begin();
        iter += vec.begin()->first;
        map_list.erase(iter);
        map_list.insert(iter, '*');

        delete sq;
        temp_map.clear();

        if(map_list.at(i) == f){
            break;
        }
    }

    for(int i = 0; i < cnt; i++){
        printf("%c", map_list.at(i));
    }
}




