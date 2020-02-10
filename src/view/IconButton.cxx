#include <SDL2/SDL_image.h>

#include "IconButton.hxx"
#include "../util/LOG.hxx"
#include "AssetHelper.hxx"

IconButton::IconButton(const std::string & icon) : m_IconPath(SDL_GetBasePath() + icon + ".png")
{
}

IconButton::~IconButton() { }

void IconButton::draw(iRendererPtr & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "Drawing a button widget";
  auto rect = getBounds();
  std::vector<uint32_t> sprite;
  auto [swidth, sheight] = AssetHelper::LoadImagePixels(m_IconPath, std::back_inserter(sprite));
  std::vector<uint32_t> pixels(rect.width() * rect.height(), 0xFFFFFF0F);
  AssetHelper::ResizeNearest(
      sprite.data(), 
      pixels.data(), 
      Rectangle{0, 0, swidth, sheight},
      rect);
  renderer->drawPicture(rect, pixels.data());
}

