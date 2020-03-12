#include "SDL/SDL.h"
#include "events.h"





int main(){
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface* screen = SDL_SetVideoMode(1280, 720, 32, 0);

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
    SDL_Flip(screen);
  }

  SDL_Quit();
}
