#ifndef ICON_BUTTON_HXX_
#define ICON_BUTTON_HXX_

#include "iViewElement.hxx"
#include <memory>

class IconButton : public iViewElement
{
  std::string m_IconPath;
public:
  IconButton(const std::string &);
  virtual void draw(iRendererPtr &) const noexcept override;
  virtual ~IconButton();
};

using IconButtonPtr = std::shared_ptr<IconButton>;

#endif // ICON_BUTTON_HXX_
