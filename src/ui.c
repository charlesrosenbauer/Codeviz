#include "ui.h"
#include "SDL/SDL.h"















void drawGUI(SDL_Surface* screen, WindowList* windows){
  SDL_FillRect(screen, 0, NULL);
  for(int i = windows->size-1; i >= 0; i--){
    Window w = windows->windows[i];
    uint32_t* pixels = w.draw(w.data);
    int h = w.h, w = w.w, x = w.x, y = w.y;
  }
}
