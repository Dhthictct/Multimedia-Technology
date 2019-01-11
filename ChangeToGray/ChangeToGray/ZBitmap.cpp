#include "stdafx.h"
#include "ZBitmap.h"
#include <fstream>
#include <cmath>
using namespace std;

ZBitmap::ZBitmap()
{
   rgb=NULL;
   palette=NULL;
}

ZBitmap::ZBitmap(string pathName)
{
	rgb=NULL;
    palette=NULL;
	string str;
    ifstream fin(pathName.c_str(),ios::binary);
    string total_str="";
	int count=0;
	int value;

 
	while(getline(fin,str))
	{
        int num=10;
	    total_str+=str+(char)num;
	}

	
	bh.bfType=total_str[0]<<8|total_str[1];
	bh.bfSize=(total_str[5]<<24)|(total_str[4]<<16)|(unsigned short)(total_str[3]<<8|(unsigned char)total_str[2]);
 
	bh.bfReserved1=0;
	bh.bfReserved2=0;
	
	bh.bfOffBits=(total_str[13]<<24)|(total_str[12]<<16)|(unsigned short)(total_str[11]<<8|(unsigned char)total_str[10]);

	BITMAPINFOHEADER bih;

	bih.biSize=(total_str[17]<<24)|(total_str[16]<<16)|(unsigned short)(total_str[15]<<8|(unsigned char)total_str[14]);
    bih.biWidth=(total_str[21]<<24)|(total_str[20]<<16)|(unsigned short)(total_str[19]<<8|(unsigned char)total_str[18]);
    bih.biHeight=(total_str[25]<<24)|(total_str[24]<<16)|(unsigned short)(total_str[23]<<8|(unsigned char)total_str[22]);
    bih.biPlanes=1;
	bih.biBitCount=(unsigned short)(total_str[29]<<8|(unsigned char)total_str[28]);
    bih.biCompression=(total_str[33]<<24)|(total_str[32]<<16)|(unsigned short)(total_str[31]<<8|(unsigned char)total_str[30]);
	bih.biSizeImage=(total_str[37]<<24)|(total_str[36]<<16)|(unsigned short)(total_str[35]<<8|(unsigned char)total_str[34]);
	bih.biXPelsPerMeter=(total_str[41]<<24)|(total_str[40]<<16)|(unsigned short)(total_str[39]<<8|(unsigned char)total_str[38]);
	bih.biYPelsPerMeter=(total_str[45]<<24)|(total_str[44]<<16)|(unsigned short)(total_str[43]<<8|(unsigned char)total_str[42]);
    bih.biClrUsed=(total_str[49]<<24)|(total_str[48]<<16)|(unsigned short)(total_str[47]<<8|(unsigned char)total_str[46]);
	bih.biClrImportant=(total_str[53]<<24)|(total_str[52]<<16)|(unsigned short)(total_str[51]<<8|(unsigned char)total_str[50]);
	
    
    int iLineByteCnt = (((bih.biWidth * bih.biBitCount) + 31) >> 5) << 2;
	int m_iImageDataSize = iLineByteCnt * bih.biHeight;
	int header_lenth=total_str.length()-m_iImageDataSize;
    int skip = 4 - ((bih.biWidth * bih.biBitCount)>>3) & 3;
    
	rgb=new MYRGBCOLOR[bih.biHeight*bih.biWidth];
	int index_count=0;
	if(bih.biBitCount==1)
	{
		UINT16* total_byte= new UINT16[bih.biSizeImage];
		for(int j=bh.bfOffBits,int k=0;j<total_str.length()-1;j++)
		{
			
			count++;
			total_byte[k]=(unsigned char)total_str[j];
			 
			k++;
		
			
		}
		
		int count=(bh.bfOffBits-53)/4;
		palette=new MYPALETTE[count];
		for(int pp=54,int kk=0;pp<54+count*4;pp+=4)
		{
			palette[kk].Alpha=(unsigned short)total_str[pp+3];
			palette[kk].R=(unsigned short)total_str[pp+2];
			palette[kk].G=(unsigned short)total_str[pp+1];
			palette[kk].B=(unsigned short)total_str[pp];
			
			kk++;
		}

        int index[8];
		skip=(bih.biSizeImage*8-bih.biHeight*bih.biWidth)/bih.biHeight;

		for(int w=0;w<bih.biSizeImage;w++)
		{
		   for(int index_loop=0;index_loop<8;index_loop++)
		   {
			  
			  index[index_loop]=(total_byte[w]&(int)pow(2,index_loop))>>index_loop;
			  rgb[index_count].R=palette[index[index_loop]].R;
			  rgb[index_count].G=palette[index[index_loop]].G;
			  rgb[index_count].B=palette[index[index_loop]].B;
			  rgb[index_count].Alpha=palette[index[index_loop]].Alpha;
			  index_count++;
			  if(index_count%bih.biWidth==0)
			     break;
		  }	  	 
		}
	}
	if(bih.biBitCount==4)
	{
		UINT16* total_byte= new UINT16[bih.biSizeImage];
		for(int j=bh.bfOffBits,int k=0;j<total_str.length()-1;j++)
		{
			count++;
			total_byte[k]=(unsigned char)total_str[j];
			 
			k++;	
		}
		
		int count=(bh.bfOffBits-53)/4;
		palette=new MYPALETTE[count];
		for(int pp=54,int kk=0;pp<54+count*4;pp+=4)
		{
			palette[kk].Alpha=(unsigned short)total_str[pp+3];
			palette[kk].R=(unsigned short)total_str[pp+2];
			palette[kk].G=(unsigned short)total_str[pp+1];
			palette[kk].B=(unsigned short)total_str[pp];
			
			kk++;
		}
		int index[2];
		//cout<<skip<<endl;
		//cout<<bih.biSizeImage/bih.biHeight<<" "<<bih.biHeight*bih.biWidth*4<<endl;
		//skip=(bih.biSizeImage*4-bih.biHeight*bih.biWidth)/bih.biHeight;
		for(int w=0;w<bih.biSizeImage;w++)
		{ 
			 index[0]=total_byte[w]&0xf;
			 rgb[index_count].R=palette[index[0]].R;
			 rgb[index_count].G=palette[index[0]].G;
			 rgb[index_count].B=palette[index[0]].B;
			 rgb[index_count].Alpha=palette[index[0]].Alpha;
             index_count++;
			 if(index_count%bih.biWidth==0)
			 {
                 w+=skip;
				 continue;
			 }
			 index[1]=(total_byte[w]>>4)&0xf;
			 rgb[index_count].R=palette[index[1]].R;
			 rgb[index_count].G=palette[index[1]].G;
			 rgb[index_count].B=palette[index[1]].B;
			 rgb[index_count].Alpha=palette[index[1]].Alpha;
			 index_count++;
			 if(index_count%bih.biWidth==0)
			 {
			     w+=skip;
				 continue;
			 }
		}
	 
	}
	if(bih.biBitCount==8)
	{
		UINT16* total_byte= new UINT16[total_str.length()-1-bh.bfOffBits];
		
		for(int j=bh.bfOffBits,int k=0;j<total_str.length()-1;j++)
		{
			count++;
			total_byte[k]=(unsigned char)total_str[j];
			k++;	
		}
		
		int count=(bh.bfOffBits-53)/4;
		palette=new MYPALETTE[count];
		for(int pp=54,int kk=0;pp<54+count*4;pp+=4)
		{
			palette[kk].Alpha=(unsigned short)total_str[pp+3];
			palette[kk].R=(unsigned short)total_str[pp+2];
			palette[kk].G=(unsigned short)total_str[pp+1];
			palette[kk].B=(unsigned short)total_str[pp];
			
			kk++;
		}
		//cout<<skip<<endl;
		//cout<<bih.biSizeImage/bih.biHeight<<" "<<bih.biHeight*bih.biWidth*4<<endl;
		//skip=(bih.biSizeImage*4-bih.biHeight*bih.biWidth)/bih.biHeight;
		for(int w=0;w<bih.biSizeImage;w++)
		{
            rgb[index_count].R=palette[total_byte[w]].R;
			rgb[index_count].G=palette[total_byte[w]].R;
            rgb[index_count].B=palette[total_byte[w]].R;
			rgb[index_count].Alpha=palette[total_byte[w]].Alpha;
			index_count++;
		    if(index_count%bih.biWidth!=0)
			{
               w+=skip;
			}
		 
		}
		 
		 
	 
	}
	if(bih.biBitCount==24)
	{
		UINT16* total_byte= new UINT16[bih.biSizeImage-skip*bih.biHeight];
		for(int j=bh.bfOffBits,int k=0;j<total_str.length()-1;j++)
		{	
			if(skip==0)
			{
				count++;
				total_byte[k]=(unsigned char)total_str[j];
				k++;
			}
			else
			{
				if(k%(iLineByteCnt-skip)==0&&k!=0)
				{
					j+=skip;
					k++;
				}
				else
				{
					count++;
					total_byte[k]=(unsigned char)total_str[j];
					k++;
				}
				
			}
		}
		int l=0;
		for(int w=0;w<bih.biHeight*bih.biWidth;w++)
		{
			rgb[w].R=(unsigned short)total_byte[l+2];
			rgb[w].G=(unsigned short)total_byte[l+1];
			rgb[w].B=(unsigned short)total_byte[l];
			
			l+=3;
		}
		delete []total_byte;	
		DWORD** pixel;
		pixel = new DWORD*[bih.biHeight];
		for (int d=0; d<bih.biHeight; d++)
			pixel[d] = new DWORD[bih.biWidth];
		
		
		for(int u=0;u<bih.biHeight;u++)
		{
			for(int v=0;v<bih.biWidth;v++)
			{
				pixel[u][v]=(rgb[v+u*bih.biWidth].R<<16)|(unsigned short)((rgb[v+u*bih.biWidth].G<<8)|(unsigned char)(rgb[v+u*bih.biWidth].B));
			}
		}	 
	}
   

}

ZBitmap::~ZBitmap()
{
	delete []rgb;
	delete []palette;
}

BITMAPFILEHEADER ZBitmap::getFileHeader()
{
	return bh;
}

MYRGBCOLOR* ZBitmap::getRGBColor()
{
    return rgb;
}

MYPALETTE* ZBitmap::getPalette()
{
	return palette;
}

BITMAPINFOHEADER ZBitmap::getInfoHeader()
{
	return bih;
}

void main()
{
	ZBitmap bm("C:\\5.bmp");
    BITMAPFILEHEADER bh=bm.getFileHeader();
    MYRGBCOLOR*   rgb=bm.getRGBColor();
	cout<<hex<<(int)(unsigned char)rgb[0].R<<endl;
}
