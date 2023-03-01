#include <stdio.h>
#include <stdlib.h>
#include "multiplication.hpp"
#define _CRT_SECURE_NO_WARNINGS


int* getmultiplication(int* polinom1, int* polinom2, int deg1, int deg2) {
    int* polinom3 = new int[deg1 + deg2 + 1]();
    int* coef = new int[deg1 + deg2 + 1]();
    int r = deg2;
    int z, y = 0;
    for (;;)
    {
        int x = 0;
        int f = deg1 + r;
        z = f;
        y = f;
        for (int i = deg1; i >= 0; i--) {
            x = polinom1[i] * polinom2[r];
            polinom3[f] = x%2;
            f--;
        }
        for (int i = deg1 + deg2; i >= 0; i--) {
            while (y < i)
                i--;
            coef[i] = coef[i]%2 + polinom3[z]%2;
            coef[i] = coef[i] % 2;
            z--;
        }
        r--;
        if (r < 0)
            break;
    }
    delete[] polinom3;
    return  coef;
}