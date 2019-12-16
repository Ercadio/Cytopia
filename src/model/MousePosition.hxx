#ifndef MOUSE_POSITION_HXX_
#define MOUSE_POSITION_HXX_

#include "../util/Model.hxx"

struct MousePositionModel
{
  int xPosition;
  int yPosition;
  int xVelocity;
  int yVelocity;
};

class MousePosition : public Model<MousePositionModel>
{
  MousePositionModel m_Model;
public:
  void setPosition(MousePositionModel &&);
};

#endif
