#include "ButtonHandler.hxx"
#include "../util/LOG.hxx"
#include "../events/MouseEvents.hxx"
#include "../model/MouseState.hxx"

ButtonHandler::ButtonHandler(GlobalModel& globalState, Callback callback, ButtonState & state, const iView & view) :
  m_GlobalState(globalState),
  m_HandleClick(callback),
  m_State(state),
  m_View(view)
{ }

ButtonHandler::~ButtonHandler() = default;

void ButtonHandler::onMouseHover()
{
  std::get<MouseState>(m_GlobalState).setCursor(CursorType::Pointer);
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
  std::get<MouseState>(m_GlobalState).setCursor(CursorType::Arrow);
  m_State.setStatus(ButtonStatus::Normal);
}

const iShape & ButtonHandler::getShape()
{
  return m_View.getBounds();
}
