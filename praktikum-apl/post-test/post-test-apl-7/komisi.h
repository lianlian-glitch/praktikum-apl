#ifndef KOMISI_H
#define KOMISI_H

#include <iostream>
#include <string>

using namespace std;

struct DetailLukisan {
    string gaya;   
    string ukuran; 
};

struct Pesanan {
    string pemesan;
    DetailLukisan detail; 
    string status;
    long harga;
};

struct User {
    string username; 
    string password; 
    string role; 
};

#define MAX_USERS 50
#define MAX_PESANAN 100
#define MAX_INFO 100 

void insertionSortNamaAsc(Pesanan pesanan[], int n) {
    for (int i = 1; i < n; i++) {
        Pesanan key = pesanan[i];
        int j = i - 1;
        while (j >= 0 && pesanan[j].pemesan > key.pemesan) {
            pesanan[j + 1] = pesanan[j];
            j = j - 1;
        }
        pesanan[j + 1] = key;
    }
}

void bubbleSortHargaDesc(Pesanan pesanan[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (pesanan[j].harga < pesanan[j + 1].harga) {
                Pesanan temp = pesanan[j];
                pesanan[j] = pesanan[j + 1];
                pesanan[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSortGayaAsc(Pesanan pesanan[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indeksMin = i;
        for (int j = i + 1; j < n; j++) {
            if (pesanan[j].detail.gaya < pesanan[indeksMin].detail.gaya) {
                indeksMin = j;
            }
        }
        if (indeksMin != i) {
            Pesanan temp = pesanan[i];
            pesanan[i] = pesanan[indeksMin];
            pesanan[indeksMin] = temp;
        }
    }
}

#endif