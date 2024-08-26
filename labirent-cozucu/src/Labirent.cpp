//
// Created by Yakup on 31.07.2024.
//

#include "../include/Labirent.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <windows.h>

Labirent::Labirent(const Konum baslangic, const Konum bitis) : mBaslangic(baslangic), mBitis(bitis) {
}

bool isSafe(int matris[SATIR][SUTUN], bool gidildi[SATIR][SUTUN], int x, int y) {
    return (x >= 0 && x < SATIR && y >= 0 && y < SUTUN && matris[x][y] == 1 && !gidildi[x][y]);
}

bool Labirent::burayaHareketEdilebilirMi(const int yeniX, const int yeniY) const {
    return
        harita[yeniX][yeniY] == ' ' &&
        yeniX >= 0 && yeniX < SATIR &&
        yeniY >= 0 && yeniY < SUTUN-1 &&
        !gidildi[yeniX][yeniY];
}
void Labirent::haritayiOlustur() {

    // Dosyayı aç.
    std::ifstream dosya(DOSYA_ADI);

    // Dosya açılamadıysa hata mesajını göster.
    if (!dosya.is_open()) {
        std::cerr << "Dosya acilamadi.\n"
            << "Dosyanin, exe'nin uretildigi konumda oldugundan emin olun.\n"
            << "Dosya adi: " << DOSYA_ADI << "\n";

        exit(EXIT_FAILURE);
    }

    // Dosyadaki karakterleri haritaya al.
    for (auto & i : harita) {
        for (char & j : i) {
            dosya.get(j);
        }
    }

    // Dosyayı kapat.
    dosya.close();
}

void Labirent::haritayiYazdir() {
    for (int i = 0; i < SATIR; ++i) {
        for (int j = 0; j < SUTUN; ++j) {
            if (i == mBaslangic.mX && j == mBaslangic.mY) {
                std::cout << "+";
            } else {
                std::cout << harita[i][j];
            }
        }
    }

    eskiX = mBaslangic.mX;
    eskiY = mBaslangic.mY;
}

void Labirent::haritayiGuncelle(const int x, const int y, int mod) {
    COORD eskiPozisyon = {static_cast<short>(eskiY),static_cast<short>(eskiX)};
    COORD yeniPozisyon = {static_cast<short>(y),static_cast<short>(x)};

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(output, eskiPozisyon);
    std::cout << " ";

    SetConsoleCursorPosition(output, yeniPozisyon);
    constexpr char karakterler[] = {'^', '<', '|', '>'};
    std::cout << karakterler[mod];

    SetConsoleCursorPosition(output, COORD{SATIR, SUTUN});

    eskiX = x;
    eskiY = y;

    Sleep(150);
}

bool Labirent::labirentiCoz() {
    // Başlangıç konumumuzu ekleyerek başlıyoruz.
    cozum.push(mBaslangic);
    gidildi[mBaslangic.mX][mBaslangic.mY] = false;

    // Çözüm yığıtı boş olmadığı sürece
    while (!cozum.empty()) {
        Konum simdiki = cozum.top();

        if (simdiki.mX == mBitis.mX &&
            simdiki.mY == mBitis.mY) {
            return true;
        }

        // YUKARI, SOL, AŞAĞI ve SAĞ için değerler:
        constexpr int  dx[] = {-1, 0, 1, 0};
        constexpr int dy[] = {0, -1, 0, 1};

        const int simdikiX = simdiki.mX;
        const int simdikiY = simdiki.mY;

        bool hareketEttiMi = false;

        for (int i = 0; i < 4; ++i) {
            const int gelecekX = simdikiX + dx[i];
            const int gelecekY = simdikiY + dy[i];

            if (burayaHareketEdilebilirMi(gelecekX, gelecekY)) {
                Konum yeni(gelecekX, gelecekY);
                yeni.mYon = i;
                cozum.push(yeni);

                hareketEttiMi = true;
                gidildi[simdikiX][simdikiY]= true;

                haritayiGuncelle(gelecekX, gelecekY, i);
                break;
            }
        }
        if (!hareketEttiMi) {
            Konum silinecek = cozum.top();
            cozum.pop();
            gidildi[simdikiX][simdikiY] = true;
            hareketEttiMi = true;

            int mod{};
            if (silinecek.mYon == 0)
                mod = 2;
            else if(silinecek.mYon == 1)
                mod = 3;
            else if(silinecek.mYon == 2)
                mod = 0;
            else
                mod = 1;

            haritayiGuncelle(simdikiX, simdikiY, mod);
        }

    }

    return false;
}
