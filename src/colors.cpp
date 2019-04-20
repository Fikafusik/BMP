
#include "../include/colors.hpp"

ColorTable::ColorTable() {
    colorTable["BLACK"] = colors::BLACK;
    colorTable["WHITE"] = colors::WHITE;
    colorTable["RED"] = colors::RED;
    colorTable["GREEN"] = colors::GREEN;
    colorTable["BLUE"] = colors::BLUE;
    colorTable["YELLOW"] = colors::YELLOW;
    colorTable["AQUA"] = colors::AQUA;
    colorTable["BROWN"] = colors::BROWN;
    colorTable["BIEGE"] = colors::BIEGE;
    colorTable["BLOND"] = colors::BLOND;
    colorTable["BRASS"] = colors::BRASS;
    colorTable["DENIM"] = colors::DENIM;
    colorTable["FAWN"] = colors::FAWN;
    colorTable["FLAX"] = colors::FLAX;
    colorTable["GOLD"] = colors::GOLD;
    colorTable["GOLDENROD"] = colors::GOLDENROD;
    colorTable["GRAY"] = colors::GRAY;
    colorTable["HELIOTROPE"] = colors::HELIOTROPE;
    colorTable["INDIGO"] = colors::INDIGO;
    colorTable["JADE"] = colors::JADE;
    colorTable["KHAKI"] = colors::KHAKI;
    colorTable["LEMON"] = colors::LEMON;
    colorTable["LILAC"] = colors::LILAC;
    colorTable["LIME"] = colors::LIME;
    colorTable["LINEN"] = colors::LINEN;
    colorTable["MAGENTA"] = colors::MAGENTA;
    colorTable["MALACHITE"] = colors::MALACHITE;
    colorTable["MAROON"] = colors::MAROON;
    colorTable["MAUVE"] = colors::MAUVE;
    colorTable["MUSTARD"] = colors::MUSTARD;
    colorTable["NAVY"] = colors::NAVY;
    colorTable["OCHRE"] = colors::OCHRE;
    colorTable["OLIVE"] = colors::OLIVE;
    colorTable["ORANGE"] = colors::ORANGE;
    colorTable["PANG"] = colors::PANG;
    colorTable["PEACH"] = colors::PEACH;
    colorTable["PINK"] = colors::PINK;
    colorTable["PLUM"] = colors::PLUM;
    colorTable["PUCE"] = colors::PUCE;
    colorTable["PUMPKIN"] = colors::PUMPKIN;
    colorTable["PURPLE"] = colors::PURPLE;
    colorTable["RUST"] = colors::RUST;
    colorTable["SAFFRON"] = colors::SAFFRON;
    colorTable["SILVER"] = colors::SILVER;
    colorTable["TOMATO"] = colors::TOMATO;
    colorTable["VIOLET"] = colors::VIOLET;
    colorTable["XANADU"] = colors::XANADU;
    colorTable["ZAFFRE"] = colors::ZAFFRE;
}

RGBTRIPLE ColorTable::get_color(std::string str) {
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    return colorTable[str];
}

ColorTable::~ColorTable() {
    colorTable.clear();
}

const RGBTRIPLE colors::BLACK = { 0, 0, 0 };
const RGBTRIPLE colors::WHITE = { 255, 255, 255 };
const RGBTRIPLE colors::RED = { 0, 0, 255 };
const RGBTRIPLE colors::GREEN = { 0, 255, 0 };
const RGBTRIPLE colors::BLUE = { 255, 0, 0 };
const RGBTRIPLE colors::YELLOW = { 0, 255, 255 };
const RGBTRIPLE colors::AQUA = { 255, 255, 0 };
const RGBTRIPLE colors::BROWN = { 0, 75, 150 };
const RGBTRIPLE colors::BIEGE = { 220, 245, 245 };
const RGBTRIPLE colors::BLOND = { 190, 240, 250 };
const RGBTRIPLE colors::BRASS = { 66, 166, 181 };
const RGBTRIPLE colors::DENIM = { 189, 96, 21 };
const RGBTRIPLE colors::FAWN = { 112, 170, 229 };
const RGBTRIPLE colors::FLAX = { 130, 220, 238 };
const RGBTRIPLE colors::GOLD = { 0, 215, 255 };
const RGBTRIPLE colors::GOLDENROD = { 32, 165, 218 };
const RGBTRIPLE colors::GRAY = { 128, 128, 128 };
const RGBTRIPLE colors::HELIOTROPE = { 255, 115, 223 };
const RGBTRIPLE colors::INDIGO = { 130, 0, 75 };
const RGBTRIPLE colors::JADE = { 107, 168, 0 };
const RGBTRIPLE colors::KHAKI = { 145, 176, 195 };
const RGBTRIPLE colors::LEMON = { 16, 233, 253 };
const RGBTRIPLE colors::LILAC = { 200, 162, 200 };
const RGBTRIPLE colors::LIME = { 0, 255, 204 };
const RGBTRIPLE colors::LINEN = { 230, 240, 250 };
const RGBTRIPLE colors::MAGENTA = { 255, 0, 255 };
const RGBTRIPLE colors::MALACHITE = { 81, 218, 11 };
const RGBTRIPLE colors::MAROON = { 0, 0, 128 };
const RGBTRIPLE colors::MAUVE = { 102, 51, 153 };
const RGBTRIPLE colors::MUSTARD = { 88, 219, 255 };
const RGBTRIPLE colors::NAVY = { 128, 0, 0 };
const RGBTRIPLE colors::OCHRE = { 34, 119, 204 };
const RGBTRIPLE colors::OLIVE = { 0, 128, 128 };
const RGBTRIPLE colors::ORANGE = { 0, 165, 255 };
const RGBTRIPLE colors::PANG = { 236, 252, 199 };
const RGBTRIPLE colors::PEACH = { 180, 229, 255 };
const RGBTRIPLE colors::PINK = { 203, 192, 255 };
const RGBTRIPLE colors::PLUM = { 102, 0, 102 };
const RGBTRIPLE colors::PUCE = { 153, 136, 204 };
const RGBTRIPLE colors::PUMPKIN = { 24, 117, 255 };
const RGBTRIPLE colors::PURPLE = { 128, 0, 128 };
const RGBTRIPLE colors::RUST = { 14, 65, 183 };
const RGBTRIPLE colors::SAFFRON = { 48, 196, 244 };
const RGBTRIPLE colors::SILVER = { 192, 192, 192 };
const RGBTRIPLE colors::TOMATO = { 71, 99, 255 };
const RGBTRIPLE colors::VIOLET = { 255, 0, 139 };
const RGBTRIPLE colors::XANADU = { 120, 134, 115 };
const RGBTRIPLE colors::ZAFFRE = { 168, 20, 0 };
