#include "Image.h"

#include <stdio.h>
#include <stdlib.h>

//Default Constructor
TGAImage::TGAImage() 
{

}

//Overridden Constructor
TGAImage::TGAImage(short width, short height) {
	m_width = width;
	m_height = height;
	m_pixels = new Colour[m_width * m_height];
	//m_pixels = (Colour*)malloc(m_width * m_height * sizeof(Colour));
	//m_pixels = new Colour[0];
}

//Set all pixels at once
void TGAImage::setAllPixels(Colour *pixels) {
	m_pixels = pixels;
}

void TGAImage::setAllPixels(Colour& c)
{
	for (int i = 0; i < m_width * m_height; ++i)
	{
		m_pixels[i].r = c.r;
		m_pixels[i].g = c.g;
		m_pixels[i].b = c.b;
		m_pixels[i].a = c.a;
	}
}

//Set indivdual pixels
void TGAImage::setPixel(Colour inputcolor, int x, int y) {
	if( x >= 0 && y >= 0 && x < m_width && y < m_height)
	{
		m_pixels[convert2dto1d(x,y)] = inputcolor;
	}
}

Colour* TGAImage::getPixel(int x, int y)
{
	if( x >= 0 && y >= 0 && x < m_width && y < m_height)
	return &m_pixels[convert2dto1d(x, y)];
	else
		return &m_pixels[0]; 
}

//Convert 2d array indexing to 1d indexing
int TGAImage::convert2dto1d(int x, int y) {
	return m_width * (m_height - 1 - y) + x;
}

void TGAImage::WriteImage(string filename) {

	//Error checking
	if (m_width <= 0 || m_height <= 0)
	{
		cout << "Image size is not set properly" << endl;
		return;
	}

	ofstream o(filename.c_str(), ios::out | ios::binary);

	//Write the header
	o.put(0);
   	o.put(0);
   	o.put(2);                         /* uncompressed RGB */
   	o.put(0); 		o.put(0);
   	o.put(0); 	o.put(0);
   	o.put(0);
   	o.put(0); 	o.put(0);           /* X origin */
   	o.put(0); 	o.put(0);           /* y origin */
   	o.put((m_width & 0x00FF));
   	o.put((m_width & 0xFF00) / 256);
   	o.put((m_height & 0x00FF));
   	o.put((m_height & 0xFF00) / 256);
   	o.put(32);                        /* 24 bit bitmap */
   	o.put(0);
   	
	//Write the pixel data
	for (int i=0;i<m_height*m_width;i++) {
		o.put(m_pixels[i].b);
		o.put(m_pixels[i].g);
		o.put(m_pixels[i].r);
		o.put(m_pixels[i].a);
	}   
	
	//close the file
	o.close();
	
}
