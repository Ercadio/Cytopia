#ifndef BUTTON_CONTROLLER_HXX
#define BUTTON_CONTROLLER_HXX

#include <functional>

#include "iMouseHandler.hxx"
#include "../model/ButtonState.hxx"
#include "../view/Shape.hxx"

class ButtonHandler : public iMouseHandler
{
public:
  using Callback = std::function<void()>;
  ButtonHandler(Callback callback, ButtonState & state, const iShape & shape);
  ~ButtonHandler() override;
  void onMouseClick(class ClickEvent &&) override;
  void onMouseHover() override;
  void onMouseLeave() override;
  const iShape & getShape() override;
private:
  ButtonState & m_State;
  Callback m_HandleClick;  
  const iShape & m_Shape;
};

#endif // BUTTON_CONTROLLER_HXX
