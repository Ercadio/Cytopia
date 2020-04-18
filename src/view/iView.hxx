#ifndef I_VIEW_HXX
#define I_VIEW_HXX

#include <memory>
#include "../view/Shape.hxx"
#include "../renderer/iRenderer.hxx"

class iView
{
  friend class AbsoluteLayout;
  friend class SelectionLayout;
  friend class Window;
public:
  iView();
  virtual void draw(iRenderer &) const noexcept = 0;
  virtual const Rectangle & getBounds() const noexcept = 0;
  virtual void setup() noexcept = 0;
  virtual void bindHandlers(class GameService & context) noexcept = 0;
private:
  virtual void setBounds(Rectangle &&) noexcept = 0;
};

using iViewPtr = std::shared_ptr<iView>;

#endif // I_VIEW_HXX
