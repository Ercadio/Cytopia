#ifndef MOUSE_POSITION_HXX_
#define MOUSE_POSITION_HXX_

#include "DataModel.hxx"

struct MousePositionModel
{
  int xPosition;
  int yPosition;
  int xVelocity;
  int yVelocity;
};

using MousePositionNotification = TypeList<MousePositionModel>;

class MousePosition : public DataModel<MousePositionNotification>
{
  MousePositionModel m_Model;
public:
  using DataModel::DataModel;
  void setPosition(MousePositionModel &&);
  ~MousePosition();
};

#endif
