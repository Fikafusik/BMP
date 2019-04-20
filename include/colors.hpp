
#ifndef __COLORS_HPP__
#define __COLORS_HPP__

#include "bitmapdef.h"
#include <algorithm>
#include <string>
#include <map>

class ColorTable {
private:
    std::map<std::string, RGBTRIPLE> colorTable;
public:
    ColorTable();
    RGBTRIPLE get_color(std::string str);
    ~ColorTable();
};

namespace colors {
    extern const RGBTRIPLE BLACK;
    extern const RGBTRIPLE RED;
    extern const RGBTRIPLE GREEN;
    extern const RGBTRIPLE BLUE;
    extern const RGBTRIPLE YELLOW;
    extern const RGBTRIPLE AQUA;
    extern const RGBTRIPLE WHITE;  
    extern const RGBTRIPLE BROWN;
    extern const RGBTRIPLE BIEGE;
    extern const RGBTRIPLE BLOND;
    extern const RGBTRIPLE BRASS;
    extern const RGBTRIPLE DENIM;
    extern const RGBTRIPLE FAWN;
    extern const RGBTRIPLE FLAX;
    extern const RGBTRIPLE GOLD;
    extern const RGBTRIPLE GOLDENROD;
    extern const RGBTRIPLE GRAY;
    extern const RGBTRIPLE HELIOTROPE;
    extern const RGBTRIPLE INDIGO;
    extern const RGBTRIPLE JADE;
    extern const RGBTRIPLE KHAKI;
    extern const RGBTRIPLE LEMON;
    extern const RGBTRIPLE LILAC;
    extern const RGBTRIPLE LIME;
    extern const RGBTRIPLE LINEN;
    extern const RGBTRIPLE MAGENTA;
    extern const RGBTRIPLE MALACHITE;
    extern const RGBTRIPLE MAROON;
    extern const RGBTRIPLE MAUVE;
    extern const RGBTRIPLE MUSTARD;
    extern const RGBTRIPLE NAVY;
    extern const RGBTRIPLE OCHRE;
    extern const RGBTRIPLE OLIVE;
    extern const RGBTRIPLE ORANGE;
    extern const RGBTRIPLE PANG;
    extern const RGBTRIPLE PEACH;
    extern const RGBTRIPLE PINK;
    extern const RGBTRIPLE PLUM;
    extern const RGBTRIPLE PUCE;
    extern const RGBTRIPLE PUMPKIN;
    extern const RGBTRIPLE PURPLE;
    extern const RGBTRIPLE RUST;
    extern const RGBTRIPLE SAFFRON;
    extern const RGBTRIPLE SILVER;
    extern const RGBTRIPLE TOMATO;
    extern const RGBTRIPLE VIOLET;
    extern const RGBTRIPLE XANADU;
    extern const RGBTRIPLE ZAFFRE;
}

#endif