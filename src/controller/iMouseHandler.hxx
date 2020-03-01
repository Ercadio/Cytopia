#ifndef I_MOUSE_HANDLER_HXX_
#define I_MOUSE_HANDLER_HXX_

#include <memory>
#include <betterEnums.hxx>

#include "../util/Point.hxx"
#include "iController.hxx"

BETTER_ENUM(CursorType, uint8_t, Arrow, Hand)

class iMouseHandler : public iController
{
public:
  virtual ~iMouseHandler() = 0;
  virtual void onMouseClick(class ClickEvent &&);
  virtual void onMouseHover();
  virtual void onMouseLeave();
  virtual void onScroll(class ScrollEvent &&);
  virtual const class iShape & getShape() = 0;
protected:
  void setCursor(CursorType);
};

using iMouseHandlerPtr = std::unique_ptr<iMouseHandler>;

#endif // I_MOUSE_HANDLER_HXX_
