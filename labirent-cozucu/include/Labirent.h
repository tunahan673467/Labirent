#ifndef LABIRENT_H
#define LABIRENT_H

#include <stack>

#include "Konum.h"

#define SATIR 17
#define SUTUN 32

#define DOSYA_ADI "Harita.txt"

class Labirent {
public:
    Labirent(Konum baslangic, Konum bitis);

    bool burayaHareketEdilebilirMi(int yeniX, int yeniY) const;

    void haritayiOlustur();
    void haritayiYazdir();
    void haritayiGuncelle(const int x, const int y, int mod);

    bool labirentiCoz();

private:
    char harita[SATIR][SUTUN]{}; // yazdırmak için
    bool gidildi[SATIR][SUTUN]{}; // daha önce gittiğim yollara tekrar girmemem için
    Konum mBaslangic, mBitis;
    std::stack<Konum> cozum{};
    int eskiX, eskiY;
};

#endif //LABIRENT_H
