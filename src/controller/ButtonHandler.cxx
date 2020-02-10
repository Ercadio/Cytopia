#include "ButtonHandler.hxx"
#include "../events/MouseEvents.hxx"

ButtonHandler::ButtonHandler(Callback callback, ButtonState & state, const iShape & shape) :
  m_HandleClick(callback),
  m_State(state),
  m_Shape(shape)
{ }

ButtonHandler::~ButtonHandler() = default;

void ButtonHandler::onMouseHover()
{
  // setCursor(CursorType::Pointer);
  m_State.setStatus(ButtonStatus::Hovered);
}

void ButtonHandler::onMouseClick(ClickEvent && event)
{
  if(event.state & ClickEvent::Pressed && event.state & ClickEvent::Left)
    m_State.setStatus(ButtonStatus::Pressed);
  if(event.state & ClickEvent::Released && event.state & ClickEvent::Left)
  {
    m_State.setStatus(ButtonStatus::Normal);
    m_HandleClick();
  }
}

void ButtonHandler::onMouseLeave()
{
  // setCursor(CursorType::Normal);
  m_State.setStatus(ButtonStatus::Normal);
}

const iShape & ButtonHandler::getShape()
{
  return m_Shape;
}
