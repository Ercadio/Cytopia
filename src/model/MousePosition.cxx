#include "MousePosition.hxx"

void MousePosition::setPosition(MousePositionModel&& model)
{
  std::swap(m_Model, model);
  notifyObservers(Notification{model, m_Model});
}
