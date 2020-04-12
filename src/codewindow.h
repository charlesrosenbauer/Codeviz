#ifndef __CODEWINDOW_HEADER__
#define __CODEWINDOW_HEADER__


#include "stdint.h"
#include "ui.h"


typedef struct{
	char*     text;
	uint32_t* pixels;
	int       h, w, textsize, lineoffset;
}CodeWindow;



Window* makeCodeWindow(char*, int, int, int, int);








#endif