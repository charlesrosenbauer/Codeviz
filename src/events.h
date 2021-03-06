#ifndef __EVENTS_HEADER__
#define __EVENTS_HEADER__


#include "SDL/SDL.h"


typedef struct{
  uint64_t widgetType;
  uint64_t widgetId;
  void*    widgetData;
}GUI_Event;

typedef struct{
  int mx, my, isHover;
}HVR_Event;

typedef struct{
  int mx, my, isActive;
}ACT_Event;

typedef struct{
  union{
    SDL_Event sdl_event;
    GUI_Event gui_event;
    HVR_Event hvr_event;
    ACT_Event act_event;
  }event;
  enum{SDL_EVENT, GUI_EVENT, HVR_EVENT, ACT_EVENT} type;
}Event;

typedef struct{
  Event* events;
  int    size, capacity;
}EventList;



void insertEventList(EventList*, Event);
void clearEventList (EventList*);
void freeEventList  (EventList*);
void getEvents      (EventList*);

EventList makeEventList(int);



#endif
