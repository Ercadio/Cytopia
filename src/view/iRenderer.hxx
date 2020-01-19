#ifndef I_RENDERER_HXX_
#define I_RENDERER_HXX_
#include <memory>
#include <tuple>

#include "Shape.hxx"
#include "../util/Meta.hxx"

using RGBAColor = StrongType<uint32_t, class RGBAColorTag>;

class iRenderer
{
  int m_dx = 0;
  int m_dy = 0;
public:
  virtual ~iRenderer() = 0;
  virtual void drawText() = 0;
  virtual void drawPicture() = 0;
  virtual void drawShape(const Rectangle &, RGBAColor) = 0;
  virtual void drawLine() = 0;
  virtual Rectangle getDrawableSize() const noexcept = 0;
  void setCursor(int dx, int dy);
protected:
  std::pair<int, int> getCursor() const noexcept;
};

using iRendererPtr = std::unique_ptr<iRenderer>;

#endif // I_RENDERER_HXX_
