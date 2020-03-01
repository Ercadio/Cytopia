#include "MousePosition.hxx"
#include "../util/LOG.hxx"

MousePosition::~MousePosition()
{
  LOG(LOG_DEBUG) << "Destroying MousePosition";
}

void MousePosition::setPosition(MousePositionModel&& model)
{
  std::swap(m_Model, model);
  notifyObservers(Notification{m_Model});
}
