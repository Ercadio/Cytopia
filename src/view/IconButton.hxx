#ifndef ICON_BUTTON_HXX_
#define ICON_BUTTON_HXX_

#include "iViewElement.hxx"
#include "../model/ButtonState.hxx"
#include <memory>

class IconButton : public iViewElement, public ButtonObserver
{
  std::string m_IconPath;
  RGBAColor m_Color;
  char m_At;
public:
  IconButton(const std::string &, const RGBAColor& = Palette::Gray);
  virtual void draw(iRenderer &) const noexcept override;
  virtual ~IconButton();
  void update(Notification) noexcept final;
  void setup() noexcept final;
  void bindHandlers(class GameService & context) noexcept final;
};

using IconButtonPtr = std::shared_ptr<IconButton>;

#endif // ICON_BUTTON_HXX_
