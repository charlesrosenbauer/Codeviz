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


void blankWindowUpdate(void* data, EventList* events){
  WinData* d = (WinData*)data;
  for(int i = 0; i < events->size; i++){
    if      (events->events[i].type == HVR_EVENT){
      if(events->events[i].event.hvr_event.isHover )
        d->color = ~d->color;
    }else if(events->events[i].type == ACT_EVENT){
      if(events->events[i].event.act_event.isActive)
        d->color = 0xffffff;
      else
        d->color = 0x000000;

    }
  }
  clearEventList(events);
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
  ret.update = blankWindowUpdate;
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
  ret.activeWindow = -1;
  ret.hoverWindow  = -1;
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


int findHover(WindowList* windows){
  for(int i = 0; i < windows->size; i++){
    Window w = windows->windows[i];
    int   mx = windows->mx;
    int   my = windows->my;
    if((mx >= w.x) && (my >= w.y) && (mx < (w.x + w.w)) && (my < (w.y + w.h))){
      return i;
    }
  }
  return -1;
}


/*
  NOTE:

  Old hover and old active should probably be alerted that they are no longer
  hover/active.
*/
void runWindowEvents(WindowList* windows, EventList* events){
  Event hover = {
    .type = HVR_EVENT,
    .event.hvr_event.mx = windows->mx,
    .event.hvr_event.my = windows->my,
    .event.hvr_event.isHover = 1
  };
  Event active = {
    .type = ACT_EVENT,
    .event.act_event.mx = windows->mx,
    .event.act_event.my = windows->my,
    .event.act_event.isActive = 1
  };
  Event unhover = {
    .type = HVR_EVENT,
    .event.hvr_event.mx = windows->mx,
    .event.hvr_event.my = windows->my,
    .event.hvr_event.isHover = 0
  };
  Event inactive = {
    .type = ACT_EVENT,
    .event.act_event.mx = windows->mx,
    .event.act_event.my = windows->my,
    .event.act_event.isActive = 0
  };

  for(int i = 0; i < events->size; i++){
    if(events->events[i].type == SDL_EVENT){
      Event e = events->events[i];
      if(e.event.sdl_event.type == SDL_MOUSEMOTION){
        windows->mx = e.event.sdl_event.motion.x;
        windows->my = e.event.sdl_event.motion.y;

        // Update hover
        int newhover = findHover(windows);
        if(windows->hoverWindow != newhover){
          if(windows->hoverWindow  >= 0) insertEventList(&windows->windows[windows->hoverWindow ].events, unhover);
          windows->hoverWindow = newhover;
          if(windows->hoverWindow  >= 0) insertEventList(&windows->windows[windows->hoverWindow ].events, hover);
        }
      }else if(e.event.sdl_event.type == SDL_MOUSEBUTTONDOWN){
        // Update active
        int newactive = windows->hoverWindow;
        if(windows->activeWindow != newactive){
          if(windows->activeWindow >= 0) insertEventList(&windows->windows[windows->activeWindow].events, inactive);
          windows->activeWindow = newactive;
          if(windows->activeWindow >= 0) insertEventList(&windows->windows[windows->activeWindow].events, active);
        }
      }

      if(windows->activeWindow >= 0){
        insertEventList(&windows->windows[windows->activeWindow].events, e);
      }
    }
  }

  for(int i = 0; i < windows->size; i++){
    Window w = windows->windows[i];
    w.update(w.data, &w.events);
  }
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
