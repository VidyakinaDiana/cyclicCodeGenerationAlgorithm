#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "division.hpp"
#define _CRT_SECURE_NO_WARNINGS

int modul(int* mas, int x) {
    for (int i = x;i >= 0;i--) {
        while (mas[x] > 2)
            mas[x] = mas[x] - 2;
        while (mas[x] < 0)
            mas[x] = mas[x] + 2;
        if (mas[x] == 2)
            mas[x] = 0;
    }
    return 0;
}

int* getdivision(int* polinom1, int* polinom2, int deg1, int deg2) {
    int* koef = new int[deg1 + 1];
    for (int i = deg2;i >= 0;i--) {
        if (polinom2[i] == 0 || polinom2[i] % 2 == 0) {
            deg2--;
        }
        else {
            break;
        }
    }
    int f = deg1 - deg2;
    int r = abs(deg1 - deg2);
    if (deg2 > deg1) {

        return 0;
    }
    else
    {
        for (;;)
        {
            int x = 0;
            int r2 = deg2;
            if (polinom2[deg2] != 0) {
                while (polinom1[deg1] % polinom2[deg2] != 0)
                    polinom1[deg1] = polinom1[deg1] + 2;
                x = (polinom1[deg1] / polinom2[deg2]) % 2;
            }
            koef[r] = x;
            r--;
            for (int i = deg1; i >= (deg1 - deg2); i--) {
                polinom1[i] = (polinom1[i] - ((x * polinom2[r2]) % 2)) % 2;
                modul(polinom1, i);
                r2--;
            }
            deg1--;
            if (deg1 < deg2)
                break;
        }

    }



    int len_ost = 0;
    for (int i = deg1;i >= 0;) {
        if (polinom1[i] != 1) {
            i--;
        }
        else {
            len_ost = i;
            break;
        }
    }

    int* ostatok = new int[len_ost + 1];

    for (int i = len_ost; i >= 0;i--) {
        ostatok[i] = polinom1[i];
    }
    return ostatok;
}









/*int mod(int* mas,int z, int n){
    for (int i = z; i >= 0; i--){
        while (mas[i] > n) {
            mas[i] = mas[i] - n;
            i--;
            if (i < 0)
                break;
        }
        while (mas[i] < 0) {
            mas[i] = mas[i] + n;
            i--;
            if (i < 0)
                break;
        }
        while (mas[i] = n) {
            mas[i] = 0;
            i--;
            if (i < 0)
                break;
        }
    }
    return 0;
}*/