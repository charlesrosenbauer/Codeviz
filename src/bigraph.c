#include "bigraph.h"
#include "stdint.h"
#include "events.h"
#include "stdlib.h"




uint32_t* renderBigraph(void* data){
	BigraphWindow* w = data;

	int size = 258 * 258;
	uint32_t* pix = malloc(sizeof(uint32_t) * size);
	{
		int ix = 0;
		for(int i = 0; i < 258; i++){
			for(int j = 0; j < 258; j++){
				if((i == 0) || (i == 257) || (j == 0) || (j == 257)){
					pix[ix] = 0xffffffff;
				}else{
					pix[ix] = 0xff000000;
				}
				ix++;
			}
		}
	}

	char prev = w->text[w->textsize-1];
	for(int i = 0; i < 131072; i++){
		uint32_t x = (uint8_t)prev;
		uint32_t y = (uint8_t)w->text[i];
		int ix  = ((y + 1) * 258) + x + 1;
		pix[ix] = 0xff007700;
		prev = y;
	}
	return pix;
}


void updateBigraph(void* data, EventList* events){
	// Add more later
	clearEventList(events);
}


void cleanupBigraph(void* data){
}



Window newBigraphWindow(char* text, int size, int x, int y, int depth, int lineIx){
	BigraphWindow* data = malloc(sizeof(BigraphWindow));
	data->text       = text;
	data->textsize   = size;
	data->lineoffset = lineIx;
	data->h          = 258;
	data->w          = 258;

	Window ret;
	ret.h = 258;
	ret.w = 258;
	ret.x = x;
	ret.y = y;
	ret.depth  = depth;
	ret.events = makeEventList(32);
	ret.data   = data;

	ret.update  = updateBigraph;
	ret.draw    = renderBigraph;
	ret.cleanup = cleanupBigraph;

	return ret;
}