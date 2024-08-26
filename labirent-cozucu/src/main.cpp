#include <iostream>

#include "../include/Labirent.h"

int main() {
    const Konum baslangic(0,1);
    const Konum bitis(16,29);

    // Labirent.h'taki SATIR ve SUTUN sayısını güncellemeyi unutmayın!
    system("cls");
    Labirent labirent(baslangic, bitis);
    labirent.haritayiOlustur();
    labirent.haritayiYazdir();
    labirent.labirentiCoz();
    getchar();
    return 0;
}