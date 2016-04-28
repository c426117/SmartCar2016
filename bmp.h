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
typedef unsigned char uchar;//�޷���char

#define examplefile "a.bmp"//ģ���ļ���


#define fileheader 14
#define bmpheader 40
#define panle 4
//�ļ���Ϣͷ �����ļ���Ϣ
//��С 14 �ֽ�
/*
typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;   //2 //�ļ����� Ĭ����BM(0x424D)
	DWORD   bfSize;//4 //�ļ���С 
	WORD    bfReserved1;//2 //������ Ĭ��0
	WORD    bfReserved2;//2 //������ Ĭ��0
	DWORD   bfOffBits;//4 ƫ���� ��ʾͷ���ִ�С
} BITMAPFILEHEADER;
*/



//λͼ��Ϣ��  ���������йص��ļ���Ϣ
//��С 40 �ֽ�
typedef struct MYBITMAPINFOHEADER {
	DWORD      biSize;//4 //���ṹ�Ĵ�С
	LONG       biWidth;//4 //ͼ�������
	LONG       biHeight;//4 //��ͼ��߶ȣ���Ϊ0
	WORD       biPlanes;//2 //ͼ��ƽ���� һ����1
	WORD       biBitCount;//2 //ɫ�����
    unsigned int      biCompression;//4//ѹ����ʽ��0��ʾ��ѹ����1��ʾRLE8ѹ����2��ʾRLE4ѹ����3��ʾÿ������ֵ��ָ�����������
    unsigned int   biSizeImage; //4//BMPͼ�����ݴ�С��������4�ı�����ͼ�����ݴ�С����4�ı���ʱ��0��䲹��
	LONG       biXPelsPerMeter;//4//ˮƽ������
	LONG       biYPelsPerMeter;//4//��ֱ������
    unsigned int      biClrUsed;//4//BMPͼ��ʹ�õ���ɫ��0��ʾʹ��ȫ����ɫ������256ɫλͼ��˵����ֵΪ100h=256
    unsigned int     biClrImportant;//4//��Ҫ����ɫ������ֵΪ0ʱ������ɫ����Ҫ������ʹ�õ�ɫ���BMPͼ����˵�����Կ����ܹ���ʾ������ɫʱ����ֵ����������������ʾ��ɫ
} tBITMAPINFOHEADER;


//��ɫ�� ��1��4��8λͼ��
//���ֽ� * ��ɫ����
/*
typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;
*/


//�������ļ�ͷ

//�Զ���ṹ

using namespace std;
class bmp //�ṩת����bmp�ļ��Ĳ���
{
public:
	
	void* memfilep;//�ļ�ָ��
	void* memdatap;//������Ϣָ��
	int loffile;//�ļ���
	int hofbmp;//�߶�
	int wofbmp;//���
	
	
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
