#include "SDL/SDL.h"
#include "events.h"





void insertEventList(EventList* list, Event e){
  if(list->size == list->capacity){
    Event* events = list->events;
    list->events  = malloc(sizeof(Event) * list->capacity * 2);
    for(int i = 0; i  < list->size; i++){
      list->events[i] = events[i];
    }
    free(events);
    list->capacity *= 2;
  }
  list->events[list->size] = e;
  list->size++;
}




void clearEventList(EventList* list){
  list->size = 0;
}



void freeEventList(EventList* list){
  free(list->events);
  free(list);
}




void getEvents(EventList* list){
  SDL_Event event;
	while(SDL_PollEvent( &event )){
		Event e = {
      .event.sdl_event = event,
      .type            = SDL_EVENT
    };
    insertEventList(list, e);
	}
}



EventList makeEventList(int capacity){
  EventList ret;
  ret.capacity = capacity;
  ret.size     = 0;
  ret.events   = malloc(sizeof(Event) * capacity);
  return ret;
}
