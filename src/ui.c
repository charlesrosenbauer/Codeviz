#include "events.h"
#include "ui.h"
#include "SDL/SDL.h"







uint32_t* drawColorWindow(void* data){
  WinData d = *(WinData*)data;
  uint32_t* window = malloc(sizeof(uint32_t) * d.w * d.h);
  int ix = 0;
  for(int i = 0; i < d.h; i++){
    for(int j = 0; j < d.w; j++){
      window[ix] = ((i == 0) || (j == 0) || (i == (d.h-1)) || (j == (d.w-1)))? 0xffffff : d.color;
      ix++;
    }
  }
  return window;
}


Window newBlankWindow(int x, int y, int h, int w, int depth, uint32_t color){
  Window ret;
  ret.h = h;
  ret.w = w;
  ret.x = x;
  ret.y = y;
  ret.depth  = depth;
  ret.events = makeEventList(64);
  ret.data   = malloc(sizeof(WinData));
  ret.draw   = drawColorWindow;
  WinData* data = (WinData*)ret.data;
  data->h = h;
  data->w = w;
  data->color = color;
  return ret;
}







void drawGUI(SDL_Surface* screen, WindowList* windows){
  SDL_FillRect(screen, NULL, 0);
  for(int i = windows->size-1; i >= 0; i--){
    Window win = windows->windows[i];
    uint32_t* pixels = win.draw(win.data);
    int h = win.h, w = win.w, x = win.x, y = win.y;

    int windex = 0;
    uint32_t* screenpixels = screen->pixels;
    for(int j = 0; j < h; j++){
      for(int k = 0; k < w; k++){
        int sindex = (screen->w * (y + j)) + x + k;
        screenpixels[sindex] = pixels[windex];
        windex++;
      }
    }
    free(pixels);
  }
}



WindowList newWindowList(int capacity){
  WindowList ret;
  ret.windows  = malloc(sizeof(Window) * capacity);
  ret.capacity = capacity;
  ret.size     = 0;
  return ret;
}


void addWindow(WindowList* list, Window w){
  if(list->size == list->capacity){
    Window* tmp = list->windows;
    list->windows = malloc(sizeof(Window) * list->capacity * 2);
    list->capacity *= 2;
    for(int i = 0; i < list->size; i++){
      list->windows[i] = tmp[i];
    }
    free(tmp);
  }
  // For now we just insert wherever the hell. Later, we'll want to sort this.
  int copymode = 0;
  Window tmp;
  for(int i = 0; i < list->size; i++){
    if(!copymode){
        if(list->windows[i].depth > w.depth){
          tmp = list->windows[i];
          list->windows[i] = w;
          copymode = 1;
        }
    }else{
        Window othertmp = list->windows[i];
        list->windows[i] = tmp;
        tmp = othertmp;
    }
  }
  if(!copymode) tmp = w;

  list->windows[list->size] = tmp;
  list->size++;
}




void printWindow(Window w){
  printf("X:%i Y:%i H:%i W:%i D:%i [U:%lu] [D:%lu] [C:%lu]\n",
            w.x, w.y, w.h, w.w, w.depth, w.update, w.draw, w.cleanup);
}


void printWindowList(WindowList* wl){
  printf("WINDOWLIST: [CP:%i] [SZ:%i] [AW:%i] [HW:%i] [MX:%i] [MY:%i]\n",
            wl->capacity, wl->size, wl->activeWindow, wl->hoverWindow, wl->mx, wl->my);
  for(int i = 0; i < wl->size; i++){
    printWindow(wl->windows[i]);
  }
}
