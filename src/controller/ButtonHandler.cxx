#include "ButtonHandler.hxx"
#include "../util/LOG.hxx"
#include "../events/MouseEvents.hxx"

ButtonHandler::ButtonHandler(Callback callback, ButtonState & state, const iView & view) :
  m_HandleClick(callback),
  m_State(state),
  m_View(view)
{ }

ButtonHandler::~ButtonHandler() = default;

void ButtonHandler::onMouseHover()
{
  setCursor(CursorType::Hand);
  m_State.setStatus(ButtonStatus::Hovered);
}

void ButtonHandler::onMouseClick(ClickEvent && event)
{
  if(event.state & ClickEvent::Pressed && event.state & ClickEvent::Left)
    m_State.setStatus(ButtonStatus::Pressed);
  if(event.state & ClickEvent::Released && event.state & ClickEvent::Left)
  {
    m_State.setStatus(ButtonStatus::Hovered);
    m_HandleClick();
  }
}

void ButtonHandler::onMouseLeave()
{
  setCursor(CursorType::Arrow);
  m_State.setStatus(ButtonStatus::Normal);
}

const iShape & ButtonHandler::getShape()
{
  return m_View.getBounds();
}
