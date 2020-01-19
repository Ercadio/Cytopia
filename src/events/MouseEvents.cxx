#include "MouseEvents.hxx"
#include "../util/Exception.hxx"
#include "../util/LOG.hxx"

MousePositionEvent::MousePositionEvent(const SDL_Event & event) :
  xPosition(event.motion.x),
  yPosition(event.motion.y),
  xVelocity(event.motion.xrel),
  yVelocity(event.motion.yrel)
{
  if(event.type != SDL_MOUSEMOTION)
    throw CytopiaError{TRACE_INFO "Invalid SDL_Event type"};
}


ClickEvent::ClickEvent(const SDL_Event & event) :
  xPosition(event.button.x),
  yPosition(event.button.y)
{
  switch(event.button.button)
  {
    case SDL_BUTTON_LEFT:
      state = ClickEvent::Left;
      break;
    case SDL_BUTTON_RIGHT:
      state = ClickEvent::Right;
      break;
    case SDL_BUTTON_MIDDLE:
      state = ClickEvent::Middle;
      break;
    default:
      throw CytopiaError{TRACE_INFO "Invalid SDL_Event type"};
  }
  state |= (event.button.type == SDL_MOUSEBUTTONDOWN) ? ClickEvent::Pressed : ClickEvent::Released;
}
