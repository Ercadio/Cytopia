#ifndef I_WIDGET_HXX
#define I_WIDGET_HXX

#include <memory>
#include "iView.hxx"
#include "BoxSizing.hxx"

class iWidget : public iView
{
public:
  virtual ~iWidget() = 0;
};

using iWidgetPtr = std::unique_ptr<iWidget>;

#endif // I_WIDGET_HXX
