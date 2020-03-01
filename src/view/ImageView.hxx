#ifndef IMAGE_VIEW_HXX_
#define IMAGE_VIEW_HXX_

#include <memory>
#include <betterEnums.hxx>

#include "iViewElement.hxx"

BETTER_ENUM(DisplayMode, uint8_t, RepeatXY, NearestXY);

class ImageView : public iViewElement
{
  std::string m_ImagePath;
  DisplayMode m_DisplayMode;
public:
  ImageView(std::string &&, DisplayMode);
  virtual ~ImageView();
  virtual void draw(iRendererPtr &) const noexcept override;
};

using ImageViewPtr = std::shared_ptr<ImageView>;

#endif // IMAGE_VIEW_HXX_
