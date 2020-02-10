#ifndef I_VIEW_HXX
#define I_VIEW_HXX

#include "Shape.hxx"
#include "iRenderer.hxx"

class iView
{
  friend class AbsoluteLayout;
  friend class Window;
public:
  iView();
  virtual void draw(iRendererPtr &) const noexcept = 0;
  virtual const Rectangle & getBounds() const noexcept = 0;
private:
  virtual void setBounds(Rectangle &&) noexcept = 0;
};

#endif // I_VIEW_HXX
