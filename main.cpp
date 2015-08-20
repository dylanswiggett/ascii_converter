#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cmath>

#include "CImg.h"

#include "textcolor.cpp"

using namespace std;
using namespace cimg_library;

#define FONTSIZE 10

string drawchars = "1234567890!@#$^&*()-=_+abcdefghijklmnopqrstuvwxyz,.<>?/;:\\\"'[]{}|~` ";

void generate_chars(int fontsize)
{
  CImgList<float> text = CImgList<unsigned char>::font(fontsize);
  float color = 255;
  char buffer[255];
  unsigned int i;
  char charbuf[2] = {0};
  int maxwidth;

  for (i = 0; i < drawchars.length(); i++) {
    CImg<float> testimg;
    charbuf[0] = drawchars[i];
    testimg.draw_text(0,0,charbuf,&color,0,1,text);
    if (testimg.width() > maxwidth)
      maxwidth = testimg.width();
  }

  for (i = 0; i < drawchars.length(); i++) {
    CImg<float> testimg(maxwidth, fontsize, 1, 3, 0);
    charbuf[0] = drawchars[i];
    testimg.draw_text(0,0,charbuf,&color,0,1,text);
    testimg.blur(fontsize / 7);
    snprintf(buffer, sizeof(buffer), "txtimgs/%d.bmp", (int)drawchars[i]);
    testimg.save(buffer);
  }
}

int get_chars(int fontsize, CImgList<float> &imgs, char **names)
{
  char *namesbuf = new char[255];
  char buffer[255];
  DIR *dir;
  struct dirent *dirent;
  int i = 0;


  struct stat st = {0};

  if (stat("txtimgs", &st) == -1) {
    mkdir("txtimgs", 0700);
  }
  
  if ((dir = opendir("txtimgs"))) {
    while ((dirent = readdir(dir))) {
      snprintf(buffer, sizeof(buffer), "txtimgs/%s", dirent->d_name);

      if (dirent->d_type & DT_REG) {
	CImg<float> img(buffer);
	if (img.height() != fontsize) {
	  delete [] namesbuf;
	  return 0;
	}
	imgs.insert(img, i);
	namesbuf[i++] = atoi(dirent->d_name);
      }
    }
  }
  *names = namesbuf;
  cout << namesbuf << endl;
  return i;
}

int main(int argc, char **argv)
{
  int fontsize = FONTSIZE;
  int usecolor = 0;
  if (argc != 2 && argc != 3 && argc != 4) {
    cout << "usage: ./main imgpath [fontsize [usecolor]]" << endl;
    return 1;
  }
  if (argc > 2) {
    fontsize = atoi(argv[2]);
    cout << "using fontsize " << fontsize << endl;
  }
  if (argc > 3) {
    usecolor = atoi(argv[3]);
  }
  CImg<float> orig_img(argv[1]);
  orig_img.resize(orig_img.width(), orig_img.height() / 2, 1);
  CImg<float> img = orig_img;
  img.RGBtoYCbCr().channel(0);
  img.save("greyscale.bmp");
  for (int i = 0; i < 10; i++)
    img.blur_median(fontsize/3);
  img.blur(fontsize/10);
  img.laplacian();
  //img.blur(fontsize/10).laplacian();
  img.save("laplace.bmp");

  CImgList<float> charimgs;
  char *names;
  int numchars = 0;

  if (!(numchars = get_chars(fontsize, charimgs, &names)))
    generate_chars(fontsize);
  if (!(numchars = get_chars(fontsize, charimgs, &names))) {
    cerr << "Could not generate chars." << endl;
    return 1;
  }

  int fontw = charimgs[0].width();

  int w = img.width();
  int h = img.height();

  for (int y = 0; y < h; y += fontsize) {
    for (int x = 0; x < w; x += fontw) {
      CImg<float> cropped = img.get_crop(x, y, 0, x + fontw, y + fontsize, 1);
      char bestchar = ' ';
      int bestchari = 0;
      float bestconvolve = -100000;
      for (int i = 0; i < numchars; i++) {
	float convolve = 0;
	for (int px = 0; px < fontw; px++) {
	  for (int py = 0; py < fontsize; py++) {
	    float r = cropped(px, py, 0, 0) - .7;
	    float c = charimgs[i](px, py, 0, 0);
	    convolve += c * (r - .7);
	    if (c < 0) {
	      cout << "unexected negative value" << endl;
	      return 1;
	    }
	  }
	}
	if (convolve > bestconvolve) {
	  bestchar = names[i];
	  bestchari = 0;
	  bestconvolve = convolve;
	}
      }
      if (usecolor) {
	float fg_r, fg_g, fg_b, bg_r, bg_g, bg_b;
	float fg_t, bg_t;
	CImg<float> orig_cropped = orig_img.get_crop(x, y, 0, x + fontw, y + fontsize, 1);
	for (int px = 0; px < fontw; px++) {
	  for (int py = 0; py < fontsize; py++) {
	    float r = orig_cropped(px, py, 0, 0) / 255;
	    float g = orig_cropped(px, py, 0, 1) / 255;
	    float b = orig_cropped(px, py, 0, 2) / 255;
	    float c = charimgs[bestchari](px, py, 0, 0);

	    fg_r += r * c;
	    fg_g += g * c;
	    fg_b += b * c;
	    fg_t += c;
	    bg_r += r * (1-c);
	    bg_g += g * (1-c);
	    bg_b += b * (1-c);
	    bg_t += 1-c;
	  }
	}

	fg_t /= (float)usecolor / 10;
	bg_t /= (float)usecolor / 10;

	fg_r /= fg_t;
	fg_g /= fg_t;
	fg_b /= fg_t;
	bg_r /= bg_t;
	bg_g /= bg_t;
	bg_b /= bg_t;
      
	textcolornear(fg_r, fg_g, fg_b, bg_r, bg_g, bg_b);
      }
      cout << bestchar;
      if (bestconvolve < 0) {
	cout << "what?" << endl;
	return 1;
      }
    }
    cout << endl;
  }

  textcolor(RESET, BLACK, WHITE);
  
  return 0;
}
