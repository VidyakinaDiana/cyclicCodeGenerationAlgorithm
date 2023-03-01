#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "division.hpp"
#include "multiplication.hpp"
#include <string.h>
#include <string>
#include <windows.h>
using namespace std;
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int deg_G, k, d;

    printf("Enter degree of g(x) - r: ");
    while (scanf("%d", &deg_G) != 1)
    {
        printf("Error, try again\n");
        while (getchar() != '\n');
    }

    int* G_x = new int[deg_G + 1];
    for (int i = deg_G; i >= 0; i--) {     // раздаем коэффиценты 1ому многочлену
        printf("Enter factor for g(x) x^%d = ", i);
        while (scanf("%d", &G_x[i]) != 1)
        {
            printf("Error, try again\n");
            while (getchar() != '\n');
        }
    }
    G_x[deg_G] = 1;
    modul(G_x, deg_G);
    printf("Enter sequence of 0 and 1 - l: ");
    char* l = (char*)malloc(100);
    while (scanf("%s", l) != 1)
    {
        printf("Error, try again\n");
        while (getchar() != '\n');
    }

    printf("Enter a number of information symbols k: ");
    while (scanf("%d", &k) != 1)
    {
        printf("Error, try again\n");
        while (getchar() != '\n');
    }
    string ll = l;
    int size = ll.size();//sizeof(l)/sizeof(l[0]);
    int size1 = size - 1;
    //printf("%d", size);
    int* m = new int[k];
    for (int i = k - 1; i >= 0; i--) {
        static int j = 0;
        if (k >= size) {
            if (l[j] != '\0' && i < size) {
                m[i] = l[j] - '0';
                j++;
            }
            else m[i] = 0;
        }
        if (k < size) {
            m[j] = l[size1] - '0';
            j++;
            size1--;
        }
    }

    int deg_M;
    for (int i = k - 1;i >= 0;) {
        if (m[i] != 1)
            i--;
        else {
            deg_M = i;
            break;
        }
    }
    int* M_x = new int[deg_M + 1];
    for (int i = deg_M; i >= 0;i--) {
        M_x[i] = m[i];
    }
    int n = deg_G + k;

    printf(" \n");
    printf("КОДЕР:\n");
    printf("Степень r пораждающего многочлена g(x) = %d\n", deg_G);
    printf("Пораждающий многочлен g(x): \n");
    for (int i = deg_G; i >= 0; i--) {
        printf("%dx^%d ", G_x[i], i);
        if (i != 0) printf(" + ");
    }
    printf(" \n");
    printf("Информационная последовательность l : %s\n", l);
    printf("Cообщение длины k = %d\n", k);
    printf("Вектор сообщения m : ");
    for (int i = k - 1; i >= 0; i--) {
        printf("%d", m[i]);
    }
    printf(" \n");
    printf("Степень многочлена m(x) = %d\n", deg_M);
    printf("Многочлен m(x)\n");
    for (int i = deg_M; i >= 0; i--) {
        printf("%dx^%d ", M_x[i], i);
        if (i != 0) printf(" + ");

    }
    printf(" \n");

    printf("Enter vector e of 0 and 1 (size is %d):", n);
    char* e = (char*)malloc(n);
    while (scanf("%s", e) != 1)
    {
        printf("Error, try again\n");
        while (getchar() != '\n');
    }
    printf("Вектор ошибок e : %s\n", e);
    printf(" \n");

    int* x_r = new int[deg_G + 1];
    x_r[deg_G] = 1;
    for (int i = deg_G - 1; i >= 0; i--) {
        x_r[i] = 0;
    }


    int* C_x = getdivision(getmultiplication(M_x, x_r, deg_M, deg_G), G_x, deg_M + deg_G, deg_G);
    int deg_C = _msize(C_x) / sizeof(int) - 1;
    printf("Степень многочлена C(x) = %d\n", deg_C);
    printf("Многочлен C(x): \n");
    for (int i = deg_C; i >= 0; i--) {
        printf("%dx^%d ", C_x[i], i);
        if (i != 0) printf("+ ");
    }
    printf(" \n");
    int* A_x = new int[n];
    int* a_x = getmultiplication(M_x, x_r, deg_M, deg_G);
    int deg_A = n - 1;
    for (int i = 0; i < n; i++) {
        if (deg_C >= i)
            A_x[i] = (a_x[i] + C_x[i]) % 2;
        else A_x[i] = a_x[i];
        if (_msize(A_x) / sizeof(int) - 1 < n && A_x[n - 1] != 1)
            A_x[n - 1] = 0;
    }
    printf("Степень многочлена A(x) = %d\n", deg_A);
    printf("Многочлен A(x): \n");
    for (int i = deg_A; i >= 0; i--) {
        printf("%dx^%d ", A_x[i], i);
        if (i != 0) printf("+ ");
    }
    printf(" \n");
    printf("Последовательность А : ");
    for (int i = deg_A; i >= 0; i--) {
        printf("%d", A_x[i]);
    }
    printf(" \n");
    printf(" \n");
    printf("ДЕКОДЕР:\n");

    int* E_x = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        static int j = 0;
        if (e[j] != '\0') {
            E_x[i] = e[j] - '0';
            j++;
        }
    }
    printf(" \n");

    printf(" \n");


    int* B_x = new int[n];
    int deg_B = n - 1;
    for (int i = 0; i < n; i++) {
        B_x[i] = (A_x[i] + E_x[i]) % 2;
    }
    printf("Степень многочлена B(x) = %d\n", deg_B);
    printf("Многочлен B(x): \n");
    for (int i = deg_B; i >= 0; i--) {
        printf("%dx^%d ", B_x[i], i);
        if (i != 0) printf("+ ");
    }
    printf(" \n");
    int* S_x = getdivision(B_x, G_x, deg_B, deg_G);
    int deg_S = _msize(S_x) / sizeof(int) - 1;
    printf("Степень многочлена S(x) = %d\n", deg_S);

    printf("Многочлен S(x): \n");

    int E = 0;
    for (int i = deg_S; i >= 0; i--) {
        if (S_x[i] == 1)
            E = 1;
        printf("%dx^%d ", S_x[i], i);
        if (i != 0) printf("+ ");
    }
    int flag = 0;
    if (E == 1)
        printf(" E = 1, есть ошибки \n");
    if (E == 0) {
        // printf(" E = 0, ошибок нет \n");
        for (int i = n - 1;i >= 0;i--)
            if (E_x[i] != 0) flag = 1;
        if (flag == 1) {
            printf("Вектор ошибок ненулевой, декодер принял неверное решение \n");
            flag = 0;
        }
    }
    return 0;
}
