#include "codewindow.h"
#include "stdint.h"







void renderText(CodeWindow* w){
	int size = w->h * w->w;
	for(int i = 0; i < size; i++){
		w->pixels[i] = 0x000000;
	}
	int column = 0;
	int line   = 0;
	for(int i = 0; i < w->textsize; i++){
		uint32_t color = 0x000000;

		if      (w->text[i] == '\n'){
			column  = 0;
			line++;
		}else if(w->text[i] == '\t'){
			column += 4;
		}else{
			column++;
			color = 0xffffff;
		}

		if((line > w->lineoffset) && (column < w->w)){
			int ix = (w->w * (line - w->lineoffset)) + column;
			w->pixels[ix] = color;
		}

		if((line - w->lineoffset) >= w->h) return;
	}
}



int countLines(char* text, int size){
	int lct = 0;
	for(int i = 0; i < size; i++){
		if(text[i] == '\n') lct++;
	}
	return lct;
}


/*
Window* makeCodeWindow(char* text, int size, int h, int w, int lineIx){

}*/