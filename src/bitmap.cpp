
#include "../include/bitmap.hpp"
#include "../include/colors.hpp"

#include <cstdint>
#include <cstring>

Bitmap::Bitmap() {
    memset(&header, 0x00, sizeof(BITMAPFILEHEADER));
    memset(&inform, 0x00, sizeof(BITMAPINFO));
    picture = NULL;
    palette = NULL;
    pen_width = 1;
    pen_color   = colors::BLACK;
    brush_color = colors::WHITE;
}

void Bitmap::readHeader(std::ifstream & inStream) {
    read(inStream, header.bfType);
    if (!checkType())
        throw std::runtime_error("Unsupported bfType");
    read(inStream, header.bfSize);
    read(inStream, header.bfReserved1);
    read(inStream, header.bfReserved2);
    read(inStream, header.bfOffBits);
}

void Bitmap::readInform(std::ifstream & inStream) {
    read(inStream, inform.biSize);
    read(inStream, inform.biWidth);
    read(inStream, inform.biHeight);
    read(inStream, inform.biPlanes);
    read(inStream, inform.biBitCount);
    if (inform.biSize >= 40) {
        read(inStream, inform.biCompression);
        read(inStream, inform.biSizeImage);
        read(inStream, inform.biXPelsPerMeter);
        read(inStream, inform.biYPelsPerMeter);
        read(inStream, inform.biClrUsed);
        read(inStream, inform.biClrImportant);
    }
    if (inform.biSize >= 52) {
        read(inStream, inform.biRedMask);
        read(inStream, inform.biGreenMask);
        read(inStream, inform.biBlueMask);
    }
    if (inform.biSize >= 56)
        read(inStream, inform.biAlphaMask);
    if (inform.biSize >= 108) {
        read(inStream, inform.biCSType);
        read(inStream, inform.biEndpoints);
        read(inStream, inform.biGammaRed);
        read(inStream, inform.biGammaGreen);
        read(inStream, inform.biGammaBlue);
    }
    if (inform.biSize >= 124) {
        read(inStream, inform.biIntent);
        read(inStream, inform.biProfileData);
        read(inStream, inform.biProfileSize);
        read(inStream, inform.biReserved);
    }
}

void Bitmap::readPalette(std::ifstream & inStream) {
    LONG ps = paletteSize();
    palette = new RGBTRIPLE[ps << 2];
    for (LONG i = 0; i < ps; ++i) {
        read(inStream, palette[i].rgbtBlue);
        read(inStream, palette[i].rgbtGreen);
        read(inStream, palette[i].rgbtRed);
    }
}

void Bitmap::readPicture(std::ifstream & inStream) {
    if (inform.biBitCount != 24)
        std::runtime_error("Unsupported biBitCount");
    picture = new RGBTRIPLE *[inform.biWidth];
    for (LONG i = 0; i < inform.biWidth; ++i) 
        picture[i] = new RGBTRIPLE[inform.biHeight];
    LONG padding = linePadding();
    for (LONG i = 0; i < inform.biHeight; ++i) {
        for (LONG j = 0; j < inform.biWidth; ++j) {
            read(inStream, picture[j][inform.biHeight - i - 1].rgbtBlue);
            read(inStream, picture[j][inform.biHeight - i - 1].rgbtGreen);
            read(inStream, picture[j][inform.biHeight - i - 1].rgbtRed);
        }
        inStream.seekg(padding, std::ios_base::cur);
    }
}

void Bitmap::writeHeader(std::ofstream & outStream) {
    write(outStream, header.bfType);
    write(outStream, header.bfSize);
    write(outStream, header.bfReserved1);
    write(outStream, header.bfReserved2);
    write(outStream, header.bfOffBits);
}

void Bitmap::writeInform(std::ofstream & outStream) {
    write(outStream, inform.biSize);
    write(outStream, inform.biWidth);
    write(outStream, inform.biHeight);
    write(outStream, inform.biPlanes);
    write(outStream, inform.biBitCount);
    if (inform.biSize >= 40) {
        write(outStream, inform.biCompression);
        write(outStream, inform.biSizeImage);
        write(outStream, inform.biXPelsPerMeter);
        write(outStream, inform.biYPelsPerMeter);
        write(outStream, inform.biClrUsed);
        write(outStream, inform.biClrImportant);
    }
    if (inform.biSize >= 52) {
        write(outStream, inform.biRedMask);
        write(outStream, inform.biGreenMask);
        write(outStream, inform.biBlueMask);
    }
    if (inform.biSize >= 56) {
        write(outStream, inform.biAlphaMask);
    }
    if (inform.biSize >= 108) {
        write(outStream, inform.biCSType);
        write(outStream, inform.biEndpoints);
        write(outStream, inform.biGammaRed);
        write(outStream, inform.biGammaGreen);
        write(outStream, inform.biGammaBlue);
    }
    if (inform.biSize >= 124) {
        write(outStream, inform.biIntent);
        write(outStream, inform.biProfileData);
        write(outStream, inform.biProfileSize);
        write(outStream, inform.biReserved);
    }
}

void Bitmap::writePalette(std::ofstream & outStream) {
    LONG ps = paletteSize();
    for (LONG i = 0; i < ps; ++i) {
        write(outStream, palette[i].rgbtBlue);
        write(outStream, palette[i].rgbtGreen);
        write(outStream, palette[i].rgbtRed);
    }
}

void Bitmap::writePicture(std::ofstream & outStream) {
    LONG padding = linePadding();
    for (LONG i = 0; i < inform.biHeight; ++i) {
        for (LONG j = 0; j < inform.biWidth; ++j) {
            write(outStream, picture[j][inform.biHeight - i - 1].rgbtBlue);
            write(outStream, picture[j][inform.biHeight - i - 1].rgbtGreen);
            write(outStream, picture[j][inform.biHeight - i - 1].rgbtRed);
        }
        for (LONG j = 0; j < padding; ++j)
            write(outStream, BYTE(0x00));
    }
}

bool Bitmap::checkType() {
    return (header.bfType == 0x4D42 || header.bfType == 0x424D);
}

LONG Bitmap::linePadding() {
    return ((4 - ((inform.biWidth * (inform.biBitCount >> 3)) % 4)) & 3);
}

LONG Bitmap::paletteSize() {
    if (inform.biSize >= 40)
        return inform.biClrUsed;
    else
        return (header.bfOffBits - inform.biSize - 14) / 4;
}

int Bitmap::load(const std::string & path) {
    std::ifstream inStream(path, std::ifstream::binary);
    if (!inStream.is_open())
        throw std::runtime_error("Can not open file: " + path);
    readHeader(inStream);
    readInform(inStream);
    readPalette(inStream);
    readPicture(inStream);
    inStream.close();
    return 0;
}

int Bitmap::save(const std::string & path) {
    std::ofstream outStream(path, std::ofstream::binary);
    if (!outStream.is_open())
         throw std::runtime_error("Can not open file: " + path);
    writeHeader(outStream);
    writeInform(outStream);
    writePalette(outStream);
    writePicture(outStream);
    outStream.close();
    return 0;

}
bool Bitmap::is_inside_x(LONG x) {
    return (x >= 0 && x < inform.biWidth);
}

bool Bitmap::is_inside_y(LONG y) {
    return (y >= 0 && y < inform.biHeight);
}

bool Bitmap::is_inside(LONG x, LONG y) {
    return (is_inside_x(x) && is_inside_y(y));
}

void Bitmap::set_pen_width(LONG width) {
    pen_width = width;
}

void Bitmap::set_pen_color(RGBTRIPLE color) {
    pen_color = color;
}

void Bitmap::set_brush_color(RGBTRIPLE color) {
    brush_color = color;
}

void Bitmap::set_pixel(LONG x, LONG y) {
    if (is_inside(x, y))
        picture[x][y] = pen_color;
}

void Bitmap::draw_hor_line(LONG x1, LONG x2, LONG y) {
    if (!is_inside_y(y))
        return;
    if (x1 > x2) 
        swap(x1, x2);
    if (x2 < 0 || x1 >= inform.biWidth)
        return;
    if (x1 < 0)
        x1 = 0;
    if (x2 >= inform.biWidth)
        x2 = inform.biWidth - 1;
    for (LONG i = x1; i <= x2; ++i)
        set_pixel(i, y);
}

void Bitmap::draw_ver_line(LONG y1, LONG y2, LONG x) {
    if (!is_inside_x(x))
        return;
    if (y1 > y2)
        swap(y1, y2);
    if (y2 < 0 || y1 >= inform.biHeight)
        return;
    if (y1 < 0)
        y1 = 0;
    if (y2 >= inform.biHeight)
        y2 = inform.biHeight - 1;
    for (LONG i = y1; i <= y2; ++i)
        set_pixel(x, i); 
}

void Bitmap::draw_hor_line(LONG x1, LONG x2, LONG y, LONG width) {
    for (LONG i = -half(width); i < half(width + 1); ++i)
        draw_hor_line(x1, x2, y + i);
}

void Bitmap::draw_ver_line(LONG y1, LONG y2, LONG x, LONG width) {
    for (LONG i = -half(width); i < half(width + 1); ++i)
        draw_ver_line(y1, y2, x + i);
}

// +
void Bitmap::draw_line(LONG x1, LONG y1, LONG x2, LONG y2) {
    const LONG dx = abs(x2 - x1);
    const LONG dy = abs(y2 - y1);
    const LONG sx = sign(x2 - x1);
    const LONG sy = sign(y2 - y1);
    int error = dx - dy;
    do {
        draw_fill_circle(x1, y1, half(pen_width));
        const int error2 = error << 1;
        if(error2 > -dy) {
            error -= dy;
            x1 += sx;
        }
        if(error2 < dx) {
            error += dx;
            y1 += sy;
        }
    } while (x1 != x2 || y1 != y2);
}

// + 
void Bitmap::draw_circle(LONG x, LONG y, LONG r) {
    LONG _x = 0;
    LONG _y = r;
    LONG delta = 1 - 2 * r;
    LONG error = 0;
    while (_y >= 0) {
        draw_fill_circle(x + _x, y + _y, half(pen_width));
        draw_fill_circle(x + _x, y - _y, half(pen_width));
        draw_fill_circle(x - _x, y + _y, half(pen_width));
        draw_fill_circle(x - _x, y - _y, half(pen_width));
        error = 2 * (delta + _y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * ++_x + 1;
            continue;
        }
        error = 2 * (delta - _x) - 1;
        if ((delta > 0) && (error > 0)) {
            delta += 1 - 2 * --_y;
            continue;
        }
        _x++;
        delta += 2 * (_x - _y);
        _y--;
    }
}

void Bitmap::draw_fill_circle(LONG x, LONG y, LONG r) {
    for (LONG i = x - r; i <= x + r; ++i)
        for (LONG j = y - r; j <= y + r; ++j)
            if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
                set_pixel(i, j);
}

void Bitmap::draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2) {
    draw_hor_line(x1, x2, y1, pen_width);
    draw_hor_line(x1, x2, y2, pen_width);
    draw_ver_line(y1, y2, x1, pen_width);
    draw_ver_line(y1, y2, x2, pen_width);
}

void Bitmap::draw_fill_rectangle(LONG x1, LONG y1, LONG x2, LONG y2) {
    if (x1 > x2)
        swap(x1, x2);
    if (y1 > y2)
        swap(y1, y2);
    if (x2 < 0 || x1 >= inform.biWidth)
        return;
    if (y2 < 0 || y1 >= inform.biHeight)
        return;
    if (x1 < 0)
        x1 = 0;
    if (x2 >= inform.biWidth)
        x2 = inform.biWidth - 1;
    if (y1 < 0)
        y1 = 0;
    if (y2 >= inform.biHeight)
        y2 = inform.biHeight - 1;
    swap(pen_color, brush_color);
    for (LONG i = x1; i <= x2; ++i)
        for (LONG j = y1; j <= y2; ++j)
            set_pixel(i, j);
    swap(pen_color, brush_color);
}

void Bitmap::draw_rectangle(LONG x1, LONG y1, LONG x2, LONG y2, bool filled) {
    if (filled)
        draw_fill_rectangle(x1, y1, x2, y2);
    draw_rectangle(x1, y1, x2, y2);
}	

void Bitmap::flip() {
	RGBTRIPLE ** newPicture = new RGBTRIPLE *[inform.biHeight];
	for (LONG i = 0; i < inform.biHeight; ++i)
		newPicture[i] = new RGBTRIPLE[inform.biWidth];	
	for (LONG i = 0; i < inform.biHeight; ++i) 
		for (LONG j = 0; j < inform.biWidth; ++j)
			newPicture[i][j] = picture[j][i];
	for (LONG i = 0; i < inform.biWidth; ++i)
		delete[] picture[i];
	delete[] picture;
	picture = newPicture;
	swap(inform.biWidth, inform.biHeight);
}

void Bitmap::flip(LONG x1, LONG y1, LONG x2, LONG y2, size_t count) {
    if (x1 > x2)
        swap(x1, x2);
    if (x2 < 0 || x1 >= inform.biWidth)
        return;
    if (y1 > y2)
        swap(y1, y2);
    if (y2 < 0 || y1 >= inform.biHeight)
        return;
    if (x1 < 0)
        x1 = 0;
    if (x2 >= inform.biWidth)
        x2 = inform.biWidth - 1;
    if (y1 < 0)
        y1 = 0;
    if (y2 >= inform.biHeight)
        y2 = inform.biHeight - 1;
    
    LONG dx = (x2 - x1);
    LONG dy = (y2 - y1);
    LONG rows = dx + 1;
    LONG cols = dy + 1;
    RGBTRIPLE ** buffer = new RGBTRIPLE *[rows];
    for (LONG i = 0; i < rows; ++i)
        buffer[i] = new RGBTRIPLE[cols];
    for (LONG i = 0; i < rows; ++i) 
		for (LONG j = 0; j < cols; ++j)
			buffer[i][j] = picture[x1 + i][y1 + j];
    
    for (size_t i = 0; i < count; ++i) {
        RGBTRIPLE ** newBuffer = new RGBTRIPLE *[cols];
        for (LONG i = 0; i < cols; ++i)
            newBuffer[i] = new RGBTRIPLE[rows];	
        for (LONG i = 0; i < cols; ++i) 
            for (LONG j = 0; j < rows; ++j)
                newBuffer[i][j] = buffer[j][cols - i - 1];
        for (LONG i = 0; i < rows; ++i)
            delete[] buffer[i];
        delete[] buffer;
        buffer = newBuffer;
        swap(rows, cols);
    }
    
    draw_fill_rectangle(x1, y1, x2, y2);
    RGBTRIPLE temp_color = pen_color;
    for (LONG i = 0; i < rows; ++i) 
		for (LONG j = 0; j < cols; ++j) {
            pen_color = buffer[i][j];
            LONG dz = 0;
            if (count % 2)
                dz = half(rows - cols);
            set_pixel(x1 + i - dz, y1 + j + dz);
        }
    pen_color = temp_color;
}

void Bitmap::fractal_1(LONG x1, LONG y1, LONG x2, LONG y2) {
    if (x2 - x1 < 4 || y2 - y1 < 4)
        return;
    draw_line(x1, y1, x2, y1);
    draw_line(x2, y1, x2, y2);
    draw_line(x1, y2, x2, y2);
    draw_line(x1, y1, x1, y2);
    LONG dx = (x2 - x1);
    LONG dy = (y2 - y1);
    draw_line(x1, y1 + dy / 2, x1 + dx / 2, y1);
    draw_line(x1, y1 + dy / 2, x1 + dx / 2, y2);
    draw_line(x1 + dx / 2, y2, x2, y1 + dy / 2);
    draw_line(x1 + dx / 2, y1, x2, y1 + dy / 2);
    LONG v1x = x1 + (dx >> 2);
    LONG v1y = y1 + (dy >> 2);
    LONG v2x = x2 - (dx >> 2);
    LONG v2y = y2 - (dy >> 2);
    fractal_1(v1x, v1y, v2x, v2y);
}

void Bitmap::fractal_2(LONG x1, LONG y1, LONG x2, LONG y2) {
    if (x2 - x1 < 8 || y2 - y1 < 8)
        return;
    LONG dx = (x2 - x1);
    LONG dy = (y2 - y1);
    LONG tdx = dx / 3;
    LONG tdy = dy / 3;
    draw_fill_rectangle(x1 + tdx, y1 + tdy, x2 - tdx, y2 - tdy);
    fractal_2(x1, y1, x1 + tdx, y1 + tdy);
    fractal_2(x1 + tdx, y1, x2 - tdx, y1 + tdy);
    fractal_2(x2 - tdx, y1, x2, y1 + tdy);
    fractal_2(x1, y1 + tdy, x1 + tdx, y2 - tdy);
    fractal_2(x2 - tdx, y1 + tdy, x2, y2 - tdy);
    fractal_2(x1, y2 - tdy, x1 + tdx, y2);
    fractal_2(x1 + tdx, y2 - tdy, x2 - tdx, y2);
    fractal_2(x2 - tdx, y2 - tdy, x2, y2);
} 

void Bitmap::fractal_3(LONG x1, LONG y1, LONG x2, LONG y2) {
    if (x2 - x1 < 8 || y2 - y1 < 8)
        return;
    LONG dx = (x2 - x1);
    LONG dy = (y2 - y1);
    LONG tdx = dx / 3;
    LONG tdy = dy / 3;
    draw_fill_rectangle(x1, y1 + tdy, x1 + tdx, y2 - tdy);
    draw_fill_rectangle(x1 + tdx, y1, x2 - tdx, y1 + tdy);
    draw_fill_rectangle(x1 + tdx, y2 - tdy, x2 - tdx, y2);
    draw_fill_rectangle(x2 - tdx, y1 + tdy, x2, y2 - tdy);
    fractal_3(x1, y1, x1 + tdx, y1 + tdy);
    fractal_3(x1, y2 - tdy, x1 + tdx, y2);
    fractal_3(x1 + tdx, y1 + tdy, x2 - tdx, y2 - tdy);
    fractal_3(x2 - tdx, y1, x2, y1 + tdy);
    fractal_3(x2 - tdx, y2 - tdy, x2, y2);
}

void Bitmap::print_info() {
    printf("< < < Bitmap information > > >\n");
    printf("Bitmap HEADER:\n");
    printf("\tbfType            : %x\n", header.bfType);
    printf("\tbfSize            : %x\n", header.bfSize);
    printf("\tbfReserved1       : %x\n", header.bfReserved1);
    printf("\tbfReserved2       : %x\n", header.bfReserved2);
    printf("\tbfOffBits         : %x\n", header.bfOffBits);
    printf("Bitmap INFO:\n");
    printf("\tbiSize            : %x\n", inform.biSize);
    printf("\tbiWidth           : %x\n", inform.biWidth);
    printf("\tbiHeight          : %x\n", inform.biHeight);
    printf("\tbiPlanes          : %x\n", inform.biPlanes);
    printf("\tbiBitCount        : %x\n", inform.biBitCount);
    if (inform.biSize >= 40) {
        printf("\tbiCompression     : %x\n", inform.biCompression);
        printf("\tbiSizeImage       : %x\n", inform.biSizeImage);
        printf("\tbiXPelsPerMeter   : %x\n", inform.biXPelsPerMeter);
        printf("\tbiYPelsPerMeter   : %x\n", inform.biYPelsPerMeter);
        printf("\tbiClrUsed         : %x\n", inform.biClrUsed);
        printf("\tbiClrImportant    : %x\n", inform.biClrImportant);
    }
    if (inform.biSize >= 52) {
        printf("\tbiRedMask         : %x\n", inform.biRedMask);
        printf("\tbiGreenMask       : %x\n", inform.biGreenMask);
        printf("\tbiBlueMask        : %x\n", inform.biBlueMask);
    }
    if (inform.biSize >= 56) {
        printf("\tbiAlphaMask       : %x\n", inform.biAlphaMask);
    }
    if (inform.biSize >= 108) {
        printf("\tbiCSType          : %x\n", inform.biCSType);
        printf("\tbiGammaRed        : %x\n", inform.biGammaRed);
        printf("\tbiGammaGreen      : %x\n", inform.biGammaGreen);
        printf("\tbiGammaBlue       : %x\n", inform.biGammaBlue);
    }
    if (inform.biSize >= 124) {
        printf("\tbiIntent          : %x\n", inform.biIntent);
        printf("\tbiProfileData     : %x\n", inform.biProfileData);
        printf("\tbiGammaRed        : %x\n", inform.biProfileSize);
        printf("\tbiReserved        : %x\n", inform.biReserved);
    }
}

RGBTRIPLE Bitmap::get_pixel(LONG x, LONG y) {
    if (is_inside(x, y))
        return picture[x][y];
    else
        return { 128, 128, 128 };
}

RGBTRIPLE Bitmap::average(LONG x1, LONG y1, LONG x2, LONG y2) {
    LONG b = 0;
    LONG g = 0;
    LONG r = 0;
    LONG pixels = (x2 - x1 + 1) * (y2 - y1 + 1);
    for (int i = x1; i <= x2; ++i) 
        for (LONG j = y1; j <= y2; ++j) {
            RGBTRIPLE color = get_pixel(i, j);
            b += color.rgbtBlue;
            g += color.rgbtGreen;
            r += color.rgbtRed;
        }
    b /= pixels;
    g /= pixels;
    r /= pixels;
    RGBTRIPLE ave = { (BYTE)b, (BYTE)g, (BYTE)r }; 
    return ave;
}

void Bitmap::compress(int compress_ratio) {
    LONG newWidth = inform.biWidth / compress_ratio;
    LONG newHeight = inform.biHeight / compress_ratio;
    RGBTRIPLE ** newPicture = new RGBTRIPLE *[newWidth];
    for (LONG i = 0; i < newWidth; ++i)
        newPicture[i] = new RGBTRIPLE[newHeight];
    for (LONG i = 0; i < newWidth; ++i) 
        for (LONG j = 0; j < newHeight; ++j) 
            newPicture[i][j] = average(i * compress_ratio, j * compress_ratio, (i + 1) * compress_ratio, (j + 1) * compress_ratio);
	for (LONG i = 0; i < inform.biWidth; ++i)
		delete[] picture[i];
	delete[] picture;
	picture = newPicture;
	inform.biWidth = newWidth;
    inform.biHeight = newHeight;
}

void Bitmap::frame(LONG w, int fractalType) {
    if (fractalType < 1 || fractalType > 3)
        return;
    LONG newWidth = inform.biWidth + 2 * w;
    LONG newHeight = inform.biHeight + 2 * w;
    RGBTRIPLE ** newPicture = new RGBTRIPLE *[newWidth];
    for (LONG i = 0; i < newWidth; ++i)
        newPicture[i] = new RGBTRIPLE[newHeight];
    LONG oldWidth = inform.biWidth;
    LONG oldHeight = inform.biHeight;
    RGBTRIPLE ** oldPicture = picture;
    picture = newPicture;
    inform.biWidth = newWidth;
    inform.biHeight = newHeight;
    swap(pen_color, brush_color);
    draw_fill_rectangle(0, 0, newWidth - 1, w - 1);
    draw_fill_rectangle(0, w - 1, w - 1, newHeight - 1);
    draw_fill_rectangle(w - 1, newHeight - w - 1, newWidth - 1, newHeight - 1);
    draw_fill_rectangle(newWidth - w - 1, w - 1, newWidth - 1, newHeight - w - 1);
    swap(pen_color, brush_color);
    switch (fractalType) {
    case 1:
        fractal_1(0, 0, newWidth - 1, newHeight - 1);
        break;
    case 2:
        fractal_2(0, 0, newWidth - 1, newHeight - 1);
        break;
    case 3:
        fractal_2(0, 0, newWidth - 1, newHeight - 1);
        break;
    }
    picture = oldPicture;
    for (LONG i = 0; i < oldWidth; ++i) 
        for (LONG j = 0; j < oldHeight; ++j)
            newPicture[w + i][w + j] = picture[i][j];
    for (LONG i = 0; i < oldWidth; ++i)
        delete[] picture[i];
    delete[] picture;
    picture = newPicture;    
}

Bitmap::~Bitmap() {
    if (picture) {
        for (LONG i = 0; i < inform.biHeight; ++i)
            delete[] picture[i];
        delete[] picture;
    }
    if (palette)
        delete[] palette;
}

LONG sign(LONG value) {
    return (value < 0 ? -1 : value > 0 ? 1 : 0);
}
