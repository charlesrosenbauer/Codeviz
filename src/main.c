#include "SDL/SDL.h"
#include "events.h"
#include "ui.h"




int main(){
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 32, 0);

  WindowList windows = newWindowList(64);
  addWindow(&windows, newBlankWindow(128,  32, 64, 16, 1, 0xff00ff));
  addWindow(&windows, newBlankWindow( 64, 128, 16, 64, 3, 0xff0000));
  addWindow(&windows, newBlankWindow( 80,  48, 32, 16, 2, 0x00ff00));
  addWindow(&windows, newBlankWindow( 80,  96, 16, 80, 0, 0x0000ff));


  int cont = 1;
  EventList events = makeEventList(256);
  while(cont){
    getEvents(&events);

    for(int i = 0; i < events.size; i++){
      Event e = events.events[i];
      if((e.type == SDL_EVENT) && (e.event.sdl_event.type == SDL_QUIT)){
        cont = 0;
      }
    }

    runWindowEvents(&windows, &events);

    clearEventList(&events);
    drawGUI(screen, &windows);
    SDL_Flip(screen);
  }

  SDL_Quit();
}
