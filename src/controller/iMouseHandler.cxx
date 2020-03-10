#include <SDL2/SDL.h>

#include "iMouseHandler.hxx"
#include "../view/Shape.hxx"
#include "../util/LOG.hxx"

iMouseHandler::~iMouseHandler() = default;

void iMouseHandler::onMouseClick(class ClickEvent &&) { }
void iMouseHandler::onMouseHover() { }
void iMouseHandler::onMouseLeave() { }
void iMouseHandler::onScroll(ScrollEvent &&) { }

void iMouseHandler::setCursor(CursorType type)
{
  SDL_SystemCursor id;
  switch(type)
  {
    case CursorType::Arrow:
      id = SDL_SYSTEM_CURSOR_ARROW;
      break;
    case CursorType::Hand:
      id = SDL_SYSTEM_CURSOR_HAND;
      break;
  }
  SDL_Cursor* cursor = SDL_CreateSystemCursor(id);
  LOG(LOG_DEBUG) << "Setting cursor";
  SDL_SetCursor(cursor);
}
