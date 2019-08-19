#include "stdafx.h"
#include "square.h"

const char s = 'S';
const char f = 'F';

const char list_of_char[3] = {'o', '.', '*'};

#define G_zz 5
#define G_zo 3
#define G_zt 5
#define G_oz 3
#define G_ot 3
#define G_tz 5
#define G_to 3
#define G_tt 5

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
    deque<int> wall_list;
    map<int, int> temp_map;

    for(int i = 0; i < cnt; i++){
        if(map_list.at(i) == 'o'){
            wall_list.push_back(i);
        }
    }

    int zz = 0; int zo = 0; int zt = 0; int oz = 0; int ot = 0; int tz = 0; int to = 0; int tt = 0;
    int F_zz = 0; int F_zo = 0; int F_zt = 0; int F_oz = 0; int F_ot = 0; int F_tz = 0; int F_to = 0; int F_tt = 0;
    int H_zz = 0; int H_zo = 0; int H_zt = 0; int H_oz = 0; int H_ot = 0; int H_tz = 0; int H_to = 0; int H_tt = 0;

    bool is_zz = false; bool is_zo = false; bool is_zt = false;
    bool is_oz = false; bool is_ot = false; bool is_tz = false;
    bool is_to = false; bool is_tt = false;

    deque<char>::iterator iter;
    deque<char>::iterator iter2;

    int prev_i = 0; char cc = 0; int cc_cnt = 0;

    bool is_Sero = false; bool is_Garo = false; bool is_Garo_collision = false;
    bool is_Reverse_Garo = false;

    printf("\ncount : %d\n\n", cnt); printf("at_F : %d\n", at_F); printf("at_S : %d\n", at_S);
    int i = at_S;
    // start point : at_S -> 72
    // while(1) -> not terminated... I could't find the solution of this problem.
    for(int x = 0; x < 600; x++){
        printf("******************\n");
        prev_i = i;
        is_Sero = false; is_Garo = false;
        zz = i-72; zo = i-71; zt = i-70; oz = i-1; ot = i+1; tz = i+70; to = i+71; tt = i+72;
        Square* sq = new Square(zz, zo, zt, oz, ot, tz, to, tt);
        printf("\nzz : %d | zo : %d | zt : %d\n", zz, zo, zt);
        printf("oz : %d | SP : %d | ot : %d\n", oz, i, ot);
        printf("tz : %d | to : %d | tt : %d\n\n", tz, to, tt);
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        int n = 8;
        F_zz = 0; F_zo = 0; F_zt = 0; F_oz = 0; F_ot = 0; F_tz = 0; F_to = 0; F_tt = 0;
        H_zz = 0; H_zo = 0; H_zt = 0; H_oz = 0; H_ot = 0; H_tz = 0; H_to = 0; H_tt = 0;
        is_zz = false; is_zo = false; is_zt = false; is_oz = false;
        is_ot = false; is_tz = false; is_to = false; is_tt = false;

        // check garo collision
        cc = map_list.at(i+2);
        cc_cnt = 0;
        if(is_Garo_collision == false){
            for(int i = 0; i < 3; i++){
                if(cc == list_of_char[i]){
                    cc_cnt++;
                }
            }
            if(cc_cnt == 0){
                printf("Garo Collision!!\n");
                is_Garo_collision = true;
                is_Reverse_Garo = true;
            }
        }

        if(is_Garo_collision == true){ printf("{ Garo BLOCKED }\n"); printf("[ Garo Restarting ]\n"); close_list.clear();
            is_Garo_collision = false; }

        // check point is near to destination point
        if(i + 142 >= at_F){
            printf("Near!\n");
            close_list.clear();
        }

        // check wall encounter
        for(unsigned int z = 0; z < wall_list.size(); z++){
            if(wall_list.at(z) == zz){ printf("zz\n"); is_zz = true; n--; }
            else if(wall_list.at(z) == zo){ printf("zo\n"); is_zo = true; n--; }
            else if(wall_list.at(z) == zt){ printf("zt\n"); is_zt = true; n--; }
            else if(wall_list.at(z) == oz){ printf("oz\n"); is_oz = true; n--; }
            else if(wall_list.at(z) == ot){ printf("ot\n"); is_ot = true; n--; }
            else if(wall_list.at(z) == tz){ printf("tz\n"); is_tz = true; n--; }
            else if(wall_list.at(z) == to){ printf("to\n"); is_to = true; n--; }
            else if(wall_list.at(z) == tt){ printf("tt\n"); is_tt = true; n--; }
            if(n == 0){ break; }
        }

        // check what place is visited
        if( n > 0){
            for(unsigned int y = 0; y < close_list.size(); y++){
                if(close_list.at(y) == zz){ printf("zz\n"); is_zz = true; n--; }
                else if(close_list.at(y) == zo){ printf("zo\n"); is_zo = true; n--; }
                else if(close_list.at(y) == zt){ printf("zt\n"); is_zt = true; n--; }
                else if(close_list.at(y) == oz){ printf("oz\n"); is_oz = true; n--; }
                else if(close_list.at(y) == ot){ printf("ot\n"); is_ot = true; n--; }
                else if(close_list.at(y) == tz){ printf("tz\n"); is_tz = true; n--; }
                else if(close_list.at(y) == to){ printf("to\n"); is_to = true; n--; }
                else if(close_list.at(y) == tt){ printf("tt\n"); is_tt = true; n--; }
                if(n == 0){ break; }
            }
        }

        // check block
        if(n == 0){ printf("{ BLOCKED }\n"); printf("[ Restarting ]\n"); close_list.clear();
            is_zz = false; is_zo = false; is_zt = false; is_oz = false;
            is_ot = false; is_tz = false; is_to = false; is_tt = false;
            is_Garo_collision = false; }
        printf("n : %d\n", n);
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        // check bound of map
        if(zz < 0){ printf("[ zz < %d, %d > reaches the wall! ]\n", i, zz); }
        else{ if(is_zz == false){ H_zz = cal_distance(sq->zero_zero); F_zz = H_zz + G_zz;
                if(F_zz > 0) temp_map.insert(make_pair(zz, F_zz)); } }
        if(zo < 0){ printf("[ zo < %d, %d > reaches the wall! ]\n", i, zo); }
        else{ if(is_zo == false){ H_zo = cal_distance(sq->zero_one); F_zo = H_zo + G_zo;
                if(F_zo > 0) temp_map.insert(make_pair(zo, F_zo)); } }
        if(zt < 0){ printf("[ zt < %d, %d > reaches the wall! ]\n", i, zt); }
        else{ if(is_zt == false){ H_zt = cal_distance(sq->zero_two); F_zt = H_zt + G_zt;
                if(F_zt > 0) temp_map.insert(make_pair(zt, F_zt)); } }
        if(oz < 0){ printf("[ oz < %d, %d > reaches the wall! ]\n", i, oz); }
        else{ if(is_oz == false){ H_oz = cal_distance(sq->one_zero); F_oz = H_oz + G_oz;
                if(F_oz > 0) temp_map.insert(make_pair(oz, F_oz)); } }
        if(ot < 0){ printf("[ ot < %d, %d > reaches the wall! ]\n", i, ot); }
        else{ if(is_ot == false){ H_ot = cal_distance(sq->one_two); F_ot = H_ot + G_ot;
                if(F_ot > 0) temp_map.insert(make_pair(ot, F_ot)); } }
        if(tz < 0){ printf("[ tz < %d, %d > reaches the wall! ]\n", i, tz); }
        else{ if(is_tz == false){ H_tz = cal_distance(sq->two_zero); F_tz = H_tz + G_tz;
                if(F_tz > 0) temp_map.insert(make_pair(tz, F_tz)); } }
        if(to < 0){ printf("[ to < %d, %d > reaches the wall! ]\n", i, to); }
        else{ if(is_to == false){ H_to = cal_distance(sq->two_one); F_to = H_to + G_to;
                if(F_to > 0) temp_map.insert(make_pair(to, F_to)); } }
        if(tt < 0){ printf("[ to < %d, %d > reaches the wall! ]\n", i, to); }
        else{ if(is_tt == false){ H_tt = cal_distance(sq->two_two); F_tt = H_tt + G_tt;
                if(F_tt > 0) temp_map.insert(make_pair(tt, F_tt)); } }

        // find a point that has the min cost
        vector<pair<int, int>> vec(temp_map.begin(), temp_map.end());
        sort(vec.begin(), vec.end(), compare_pair_second<less>());

        close_list.push_back(i); // close old start point
        if(x > 1){
            if(!open_list.empty()){
                printf("[ open_list.front() is removed : %d ]\n", open_list.front());
                open_list.pop_front();
            }
        }

        // ********************************************
        // set new start point
        vector<pair<int, int>>::iterator iter_vec2 = vec.begin();

        // print result
        for(int aa = 0; aa < 8; aa++){
            printf("%d %d\n", iter_vec2->first, iter_vec2->second);
            iter_vec2++;
        }
        printf("\n");

        i = vec.begin()->first;
        printf("[ prev_i : %d ]\n", prev_i);
        printf("[ vec.begin()->first : %d ]\n", vec.begin()->first);
        if(is_Reverse_Garo == true){
            i = vec.begin()->first - 2;
            is_Reverse_Garo = false;
        }
        if(prev_i == i){
            printf("prev_i == i\n");
            i = vec.begin()->first - 1;
        }
        // ********************************************

        // check directions of garo & sero
        printf("[ i : %d ]\n", i);
        int temp = i - prev_i;
        printf("[ temp : %d ]\n", temp);
        if(temp < 0){
            if(temp == -1){ is_Garo = true; printf("[ Move Garo Minus ]\n"); }
            else if(temp == -71){ is_Sero = true; printf("[ Move Sero Minus ]\n"); }
        }
        else if(temp > 0){
            if(temp == 1){ is_Garo = true; printf("[ Move Garo ]\n"); }
            else if(temp == 71){ is_Sero = true; printf("[ Move Sero ]\n"); }
        }

        // save current i to open_list
        open_list.push_back(i); // new start point
        printf("open_list : %d\n\n", open_list.back());
        vec.erase(vec.begin());

        // check next map value using the information of garo & sero
        iter = map_list.begin();
        iter += (i + 1);
        bool no_Sero = false;
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
                if(map_list.at(i+71) == 'o'){
                    no_Sero = true;
                }
            }
        }

        // Manage points of close_list
        vector<pair<int, int>>::iterator iter_vec = vec.begin();
        printf("[ i+142 : %d ]\n", i+142);
        if(no_Sero == false){ // except oz, ot
            for(int j = 0; j < n-1; j++){
                if(iter_vec->first >= 0 && iter_vec->first < cnt){
                    if(temp < 0){
                        if((is_Sero == true) && ((i-71) > 0)){
                            printf("close_list : %d\n", iter_vec->first);
                            close_list.push_back(iter_vec->first); // store other point
                        }
                    }
                    else{
                        if((is_Garo == true) && (map_list.at(i+1) != 'o')){
                            printf("close_list : %d\n", iter_vec->first);
                            close_list.push_back(iter_vec->first); // store other point
                        }
                        else if((is_Sero == true) && (map_list.at(i+71) != 'o') &&
                                ((i+142) < 3406)){
                            printf("close_list : %d\n", iter_vec->first);
                            close_list.push_back(iter_vec->first); // store other point
                        }
                    }
                    iter_vec += 1;
                }
            }
        }

        // draw route
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

        if(map_list.at(i+1) == f){
            break;
        }
        printf("******************\n");
    }

    // print modifed map
    printf("\n\n");
    FILE* write_fp;
    if((write_fp = fopen("./map2.txt", "w")) == NULL){
        perror("{ File open ERROR! }");
        exit(0);
    }

    for(int i = 0; i < cnt; i++){
        printf("%c", map_list.at(i));
        fputc(map_list.at(i), write_fp);
    }

    printf("[ Directory : ./map2.txt ]\n");
    printf("\n\n");
}




