#ifndef __CODEWINDOW_HEADER__
#define __CODEWINDOW_HEADER__


#include "stdint.h"
#include "ui.h"


typedef struct{
	char*     text;
	int       h, w, textsize, lineoffset;
}CodeWindow;



Window newCodeWindow(char*, int, int, int, int, int, int, int);








#endif