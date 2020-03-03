#include "ImageView.hxx"
#include "AssetHelper.hxx"
#include "../util/filesystem.hxx"
#include <vector>

ImageView::ImageView(std::string && image, DisplayMode mode) : 
  m_ImagePath(getBasePath() + image + ".png"),
  m_DisplayMode(mode)
{ }

ImageView::~ImageView() { }

void ImageView::draw(iRendererPtr & renderer) const noexcept
{
  auto rect = getBounds();
  std::vector<uint32_t> sprite;
  auto [swidth, sheight] = AssetHelper::LoadImagePixels(m_ImagePath, std::back_inserter(sprite));
  std::vector<uint32_t> pixels(rect.width() * rect.height(), 0xFFFFFF0F);
  switch(m_DisplayMode)
  {
    case DisplayMode::NearestXY:
      AssetHelper::ResizeNearest(
          sprite.data(), 
          pixels.data(), 
          Rectangle{0, 0, swidth-1, sheight-1},
          rect);
      break;
    case DisplayMode::RepeatXY:
      AssetHelper::RepeatXY(
          sprite.data(), 
          pixels.data(), 
          Rectangle{0, 0, swidth-1, sheight-1},
          rect);
      break;
  }
  renderer->drawPicture(rect, pixels.data());
}
