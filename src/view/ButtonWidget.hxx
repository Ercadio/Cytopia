#ifndef BUTTON_WIDGET_HXX_
#define BUTTON_WIDGET_HXX_

#include "iWidget.hxx"
#include <memory>

class ButtonWidget : public iWidget
{
  const char * m_Text;
public:
  ButtonWidget(const char *);
  virtual void draw(iRendererPtr &) const noexcept override;
  virtual ~ButtonWidget();
};

using ButtonWidgetPtr = std::unique_ptr<ButtonWidget>;

#endif // BUTTON_WIDGET_HXX_
