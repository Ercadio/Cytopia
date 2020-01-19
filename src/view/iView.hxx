#ifndef I_VIEW_HXX
#define I_VIEW_HXX

#include "Shape.hxx"
#include "iRenderer.hxx"

class iView
{
  Rectangle m_Bounds;
  friend class AbsoluteLayout;
  friend class Window;
public:
  iView();
  virtual void draw(iRendererPtr &) const noexcept = 0;
  const Rectangle & getBounds() const noexcept;
};

#endif // I_VIEW_HXX
