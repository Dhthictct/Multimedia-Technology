#ifndef ZBITMAP_H
#define ZBITMAP_H
#include<iostream>
#include<string>
using namespace std;

typedef unsigned short UINT16;
typedef unsigned char UINT8;
typedef unsigned int DWORD; 
typedef DWORD LONG;
typedef unsigned short WORD;

typedef struct tagBITMAPFILEHEADER
{
	UINT16 bfType;    //bm  2字节
    DWORD bfSize;     //文件大小  4字节
    UINT16 bfReserved1; //保留字段1  2字节
    UINT16 bfReserved2; //保留字段2  2字节
    DWORD bfOffBits;    //数据区偏移量  4字节
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize; //BITMAPINFOHEADER需要的字节数 4字节
	LONG biWidth; //图像宽度 4字节
	LONG biHeight; //图像高度 4字节
	WORD biPlanes; //图像平面数 2字节
	WORD biBitCount; //比特/像素 2字节
	DWORD biCompression; //是否压缩 4字节
	DWORD biSizeImage; //图像数据区大小 4字节
	LONG biXPelsPerMeter; //水平分辨率 4字节
	LONG biYPelsPerMeter; //垂直分辨率 4字节
	DWORD biClrUsed; //使用的调色板项 4字节
	DWORD biClrImportant;//重要调色板项 4字节
} BITMAPINFOHEADER;

typedef struct tagRGBCOLOR
{
	UINT16 R;  //红色分量 1字节
	UINT16 G;  //绿色分量 1字节
	UINT16 B;  //蓝色分量 1字节
	UINT16 Alpha;//透明度 1字节
}MYRGBCOLOR;

typedef struct tagPALETTE
{
	UINT16 R;  //红色分量 1字节
	UINT16 G;  //绿色分量 1字节
	UINT16 B;  //蓝色分量 1字节
	UINT16 Alpha;//透明度 1字节
}MYPALETTE;


class ZBitmap
{
private:
   BITMAPFILEHEADER  bh;
   BITMAPINFOHEADER bih;
   MYRGBCOLOR      *rgb;
   MYPALETTE   *palette;

public:
   ZBitmap();
   ZBitmap(string pathName);
   ~ZBitmap();
   
   BITMAPFILEHEADER getFileHeader();
   BITMAPINFOHEADER getInfoHeader();
   MYRGBCOLOR* getRGBColor();
   MYPALETTE *getPalette();

   void saveBitmap(string pathName);
   
};

#endif