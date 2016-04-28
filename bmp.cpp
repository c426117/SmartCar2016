#include "bmp.h"

void bmp::bmpinit(int h , int w)
{
	hofbmp = h;
	wofbmp = w;
	memfilep = malloc(fileheader+bmpheader+(panle*256)+(h*w)) ;
	loffile = (fileheader + bmpheader + (panle * 256) + (h*w));
	ifstream fin;
	fin.open("a.bmp", ios::binary);
	char* fp =(char*) memfilep;
	fin.read(fp, fileheader);
	int i = 0;
	while (i < fileheader)
	{
		fp++;
		i++;
	}
	fin.read(fp, bmpheader);
    ((tBITMAPINFOHEADER*)fp)->biWidth = w;
    ((tBITMAPINFOHEADER*)fp)->biHeight = h;
	i = 0;
	while (i < sizeof(BITMAPINFOHEADER))
	{
		fp++;
		i++;
	}
	fin.read(fp, 256*panle);
	i = 0;
	while (i < (256 * panle))
	{
		fp++;
		i++;
	}

	memdatap = fp;

	fin.close();

}

void bmp::greatbmp(char* data)
{
    char* pd = data;
    char* fd = (char*)memdatap;
	int i = 0;
	for (i = 0; i < (hofbmp*wofbmp); i++)
	{
		if (pd[i] == 48)
		{
			fd[i] = 255;
		}
		else
		{
			fd[i] = 0;
		}
	}
}


void bmp::writebmp(char* name)
{
	ofstream fout;
	fout.open(name,ios::trunc | ios::binary);
	fout.write((char*)memfilep,loffile);
	fout.close();
}
