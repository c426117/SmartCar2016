#pragma once
#pragma pack(1)
//BMP.h 
//#include <WINGDI.h>
#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
//typedef unsigned int DWORD;
typedef long LONG;
typedef unsigned char uchar;//无符号char

#define examplefile "a.bmp"//模板文件名


#define fileheader 14
#define bmpheader 40
#define panle 4
//文件信息头 储存文件信息
//大小 14 字节
/*
typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;   //2 //文件类型 默认是BM(0x424D)
	DWORD   bfSize;//4 //文件大小 
	WORD    bfReserved1;//2 //保留字 默认0
	WORD    bfReserved2;//2 //保留字 默认0
	DWORD   bfOffBits;//4 偏移量 表示头部分大小
} BITMAPFILEHEADER;
*/



//位图信息由  储存像素有关的文件信息
//大小 40 字节
typedef struct MYBITMAPINFOHEADER {
	DWORD      biSize;//4 //本结构的大小
	LONG       biWidth;//4 //图像宽像素
	LONG       biHeight;//4 //（图像高度）总为0
	WORD       biPlanes;//2 //图像平面数 一定是1
	WORD       biBitCount;//2 //色彩深度
    unsigned int      biCompression;//4//压缩方式，0表示不压缩，1表示RLE8压缩，2表示RLE4压缩，3表示每个像素值由指定的掩码决定
    unsigned int   biSizeImage; //4//BMP图像数据大小，必须是4的倍数，图像数据大小不是4的倍数时用0填充补足
	LONG       biXPelsPerMeter;//4//水平像素数
	LONG       biYPelsPerMeter;//4//垂直像素数
    unsigned int      biClrUsed;//4//BMP图像使用的颜色，0表示使用全部颜色，对于256色位图来说，此值为100h=256
    unsigned int     biClrImportant;//4//重要的颜色数，此值为0时所有颜色都重要，对于使用调色板的BMP图像来说，当显卡不能够显示所有颜色时，此值将辅助驱动程序显示颜色
} tBITMAPINFOHEADER;


//调色板 仅1，4，8位图有
//四字节 * 颜色总数
/*
typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;
*/


//以上是文件头

//自定义结构

using namespace std;
class bmp //提供转换成bmp文件的操作
{
public:
	
	void* memfilep;//文件指针
	void* memdatap;//像素信息指针
	int loffile;//文件长
	int hofbmp;//高度
	int wofbmp;//宽度
	
	
	bmp()
	{
		memfilep = NULL;
		memdatap = NULL;
		loffile = 0;
	}
	~bmp() { free(memfilep); }
	void bmpinit(int h,int w);
    void greatbmp(char* data);
	void writebmp(char* name);
	
	
	
	
	
};
