#ifndef TEXT_BUTTON_HXX_
#define TEXT_BUTTON_HXX_

#include "../model/ButtonState.hxx"
#include "iViewElement.hxx"
#include <memory>

class TextButton : public iViewElement, public ButtonObserver
{
  int m_At;
  RGBAColor m_Color;
  const char * m_Text;
public:
  TextButton(const char *, RGBAColor = Palette::Orange);
  virtual void draw(iRendererPtr &) const noexcept override;
  virtual ~TextButton();
  using MyController = class ButtonHandler;
  using MyState = ButtonState;
  void update(Notification) noexcept final;
};

using TextButtonPtr = std::shared_ptr<TextButton>;

#endif // TEXT_BUTTON_HXX_
