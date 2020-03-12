#ifndef __UI_HEADER__
#define __UI_HEADER__


#include "stdint.h"
#include "events.h"



typedef struct{
  int   h, w, x, y, depth;
  EventList    events;
  void*          data;
  void      (* update)(void*, EventList*);
  uint32_t* (*   draw)(void*);
  void      (*cleanup)(void*);
}Window;



typedef struct{
  Window*  windows;
  int      capacity, size, activeWindow, hoverWindow, mx, my;
}WindowList;




void addWindow      (WindowList *, Window);
void runWindowEvents(WindowList *, EventList*);
void drawGUI        (SDL_Surface*, WindowList*);

WindowList newWindowList(int);







#endif
