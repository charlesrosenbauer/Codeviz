#include "SDL/SDL.h"
#include "events.h"
#include "ui.h"




int main(){
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 32, 0);

  WindowList windows = newWindowList(64);
  addWindow(&windows, newBlankWindow( 8,  8, 16, 16, 0, 0x0000ff));
  addWindow(&windows, newBlankWindow(80, 48, 32, 16, 0, 0x00ff00));



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

    clearEventList(&events);
    drawGUI(screen, &windows);
    SDL_Flip(screen);
  }

  SDL_Quit();
}
