#ifndef BUTTON_STATE_HXX
#define BUTTON_STATE_HXX

#include <betterEnums.hxx>

#include "../util/Model.hxx"
#include "iState.hxx"

BETTER_ENUM(ButtonStatus, uint8_t, Normal, Disabled, Pressed, Hovered);

class ButtonState : public iState
{
  ButtonStatus m_Status = ButtonStatus::Normal;
public:
  ButtonState();
  void setStatus(ButtonStatus);
  ~ButtonState() final;
};

#endif // BUTTON_STATE_HXX
