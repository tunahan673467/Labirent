#ifndef KONUM_H
#define KONUM_H
#include <ostream>

typedef enum {
    YUKARI, SOL, ASAGI, SAG
} Yon;

class Konum {
public:
    Konum(int x, int y);

    int mX;
    int mY;
    int mYon;

    bool operator==(const Konum& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Konum& konum);
};

#endif //KONUM_H
