#ifndef BUTTON_CONTROLLER_HXX
#define BUTTON_CONTROLLER_HXX

#include <functional>

#include "iMouseHandler.hxx"
#include "../GlobalModel.hxx"
#include "../model/ButtonState.hxx"
#include "../view/Shape.hxx"
#include "../view/iView.hxx"

class ButtonHandler : public iMouseHandler
{
public:
  using Callback = std::function<void()>;
  ButtonHandler(GlobalModel &, Callback, ButtonState &, const iView &);
  ~ButtonHandler() override;
  void onMouseClick(class ClickEvent &&) override;
  void onMouseHover() override;
  void onMouseLeave() override;
  const iShape & getShape() final;
private:
  GlobalModel & m_GlobalState;
  ButtonState & m_State;
  Callback m_HandleClick;  
  const iView & m_View;
};

#endif // BUTTON_CONTROLLER_HXX
