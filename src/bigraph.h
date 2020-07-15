#ifndef __BIGRAPH_HEADER__
#define __BIGRAPH_HEADER__


#include "stdint.h"
#include "ui.h"




typedef struct{
	char*     text;
	int       h, w, textsize, lineoffset;
}BigraphWindow;



Window newBigraphWindow(char*, int, int, int, int, int);



#endif