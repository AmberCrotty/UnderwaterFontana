#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event & event) {
  switch (event.type) {
  case SDL_QUIT:
    code = SFEVENT_QUIT;
    break;
  case SDL_USEREVENT:
    code = SFEVENT_UPDATE;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      code = SFEVENT_PLAYER_LEFT_KEYDOWN;
      break;
    case SDLK_RIGHT:
      code = SFEVENT_PLAYER_RIGHT_KEYDOWN;
      break;
    case SDLK_UP:
      code = SFEVENT_PLAYER_UP_KEYDOWN;
      break;
    case SDLK_DOWN:
      code = SFEVENT_PLAYER_DOWN_KEYDOWN;
      break;
    case SDLK_SPACE:
      code = SFEVENT_FIRE_KEYDOWN;
      break;
    case SDLK_q:
      code = SFEVENT_QUIT;
      break;
    }
    break;
   case SDL_KEYUP:
    switch(event.key.keysym.sym) {
    case SDLK_LEFT:
      code = SFEVENT_PLAYER_LEFT_KEYUP;
      break;
    case SDLK_RIGHT:
      code = SFEVENT_PLAYER_RIGHT_KEYUP;
      break;
    case SDLK_UP:
      code = SFEVENT_PLAYER_UP_KEYUP;
      break;
    case SDLK_DOWN:
      code = SFEVENT_PLAYER_DOWN_KEYUP;
      break;
    case SDLK_SPACE:
      code = SFEVENT_FIRE_KEYUP;
      break;
    }
    break;
  default:
    code = SFEVENT_NULL;
    break;
  }
}


SFEVENT SFEvent::GetCode() {
  return code;
}
