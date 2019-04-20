
#ifndef __BITMAP_HPP__
#define __BITMAP_HPP__

#include "bitmapdef.h"

#include <cstdio>
#include <string>
#include <fstream>

class Bitmap {
private:
    BITMAPFILEHEADER    header;
    BITMAPINFO          inform;
    RGBTRIPLE **        picture;
    RGBTRIPLE *         palette;
    LONG pen_width;
    RGBTRIPLE pen_color;
    RGBTRIPLE brush_color;
    
    void readHeader(std::ifstream & inStream);
    void readInform(std::ifstream & inStream);
    void readPalette(std::ifstream & inStream);
    void readPicture(std::ifstream & inStream);
    
    void writeHeader(std::ofstream & outStream);
    void writeInform(std::ofstream & outStream);
    void writePalette(std::ofstream & outStream);
    void writePicture(std::ofstream & outStream);

    bool is_inside_x(LONG x);
    bool is_inside_y(LONG y);
    bool is_inside(LONG x, LONG y); 

    bool checkType();
    LONG linePadding();
    LONG paletteSize();
    
    RGBTRIPLE get_pixel(LONG x, LONG y);
    void set_pixel(LONG x, LONG y);

    void draw_hor_line(LONG x1, LONG x2, LONG y);
    void draw_ver_line(LONG y1, LONG y2, LONG x);
    void draw_hor_line(LONG x1, LONG x2, LONG y, LONG width);
    void draw_ver_line(LONG y1, LONG y2, LONG x, LONG width);  

    RGBTRIPLE average(LONG x1, LONG y1, LONG x2, LONG y2);
public:
    Bitmap();

    int load(const std::string & path);
    int save(const std::string & path);

    void set_pen_width(LONG width);
    void set_pen_color(RGBTRIPLE color);
    void set_brush_color(RGBTRIPLE color);

    void draw_fill_circle(LONG x, LONG y, LONG r);

    void draw_line(LONG x1, LONG y1, LONG x2, LONG y2);
    void draw_circle(LONG x, LONG y, LONG r);
    
    void draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2);
    void draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2, bool filled);
    void draw_fill_rectangle(LONG x1, LONG y1, LONG x2, LONG y2);
	
    void fractal_1(LONG x1, LONG y1, LONG x2, LONG y2);
    void fractal_2(LONG x1, LONG y1, LONG x2, LONG y2);
    void fractal_3(LONG x1, LONG y1, LONG x2, LONG y2);

    void flip();
    void flip(LONG x1, LONG y1, LONG x2, LONG y2, size_t count);

    void frame(LONG width, int fractalType);

    void compress(int compression_ratio);

    void print_info();
    
    ~Bitmap();
};

template <typename Type, size_t size>
void read(std::ifstream & inStream, Type & value) {
    inStream.read(reinterpret_cast<char *>(&value), size);
}
template <typename Type, size_t size>
void write(std::ofstream & outStream, Type value) {
    outStream.write(reinterpret_cast<char *>(&value), size);
}

template <typename Type>
void read(std::ifstream & inStream, Type & value) {
    inStream.read(reinterpret_cast<char *>(&value), sizeof(value));
}

template <typename Type>
void write(std::ofstream & outStream, Type value) {
    outStream.write(reinterpret_cast<char *>(&value), sizeof(value));
}

template <typename Type>
void swap(Type & a, Type & b) {
    Type temp = a;
    a = b;
    b = temp;
}

template <typename Type>
Type half(Type value) {
    return (value >> 1);
}

LONG sign(LONG value);      

#endif // __BITMAP_HPP__
