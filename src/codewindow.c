#include "codewindow.h"
#include "stdint.h"
#include "events.h"
#include "stdlib.h"







uint32_t* renderCode(void* data){
	CodeWindow* w = data;

	int size = w->h * w->w;
	uint32_t* pix = malloc(sizeof(uint32_t) * size);
	for(int i = 0; i < size; i++){
		pix[i] = 0xff000000;
	}

	int column = 0;
	int line   = 0;
	for(int i = 0; i < w->textsize; i++){
		uint32_t color = 0xff000000;

		if      (w->text[i] == '\n'){
			column  = 0;
			line++;
		}else if(w->text[i] == '\t'){
			column += 4;
		}else if(w->text[i] == ' ' ){
			column ++;
		}else{
			column++;
			color = 0xffffffff;
		}

		if((line >= w->lineoffset) && (column < w->w)){
			int ix = (w->w * (line - w->lineoffset)) + column;
			pix[ix] = color;
		}

		if((line - w->lineoffset) >= w->h) return pix;
	}

	return pix;
}



int countLines(char* text, int size){
	int lct = 0;
	for(int i = 0; i < size; i++){
		if(text[i] == '\n') lct++;
	}
	return lct;
}


void updateCodeWindow(void* data, EventList* events){
	// Add more later
	clearEventList(events);
}


void cleanupCodeWindow(void* data){
}



Window newCodeWindow(char* text, int size, int h, int w, int x, int y, int depth, int lineIx){
	CodeWindow* data = malloc(sizeof(CodeWindow));
	data->text       = text;
	data->textsize   = size;
	data->lineoffset = lineIx;
	data->h          = h;
	data->w          = w;

	Window ret;
	ret.h = h;
	ret.w = w;
	ret.x = x;
	ret.y = y;
	ret.depth  = depth;
	ret.events = makeEventList(32);
	ret.data   = data;

	ret.update  = updateCodeWindow;
	ret.draw    = renderCode;
	ret.cleanup = cleanupCodeWindow;

	return ret;
}