#include "iActivity.hxx"
#include "../engine/MessageQueue.hxx"
#include "../Events.hxx"
#include "../util/Exception.hxx"
#include "../util/LOG.hxx"
#include "Window.hxx"

iActivity::iActivity(GameService::ServiceTuple & context, Window & w) : GameService(context), m_Window(w) { }

iActivity::~iActivity() = default;

void iActivity::activitySwitch(ActivityType type)
{
  GetService<UILoopMQ>().push(ActivitySwitchEvent{type});
  GetService<GameLoopMQ>().push(ActivitySwitchEvent{type});
}

Rectangle iActivity::getBounds() const noexcept
{
  return m_Window.getBounds();
}
