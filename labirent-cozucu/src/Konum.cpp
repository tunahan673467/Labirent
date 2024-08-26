#include "../include/Konum.h"

Konum::Konum(const int x, const int y) : mX(x), mY(y), mYon(YUKARI) {
}

bool Konum::operator==(const Konum &other) const {
    return (this->mX == other.mX && this->mX == other.mY);
}

std::ostream & operator<<(std::ostream &os, const Konum &konum) {
    os << "X: " << konum.mX << " | Y: " << konum.mY;
    return os;
}
