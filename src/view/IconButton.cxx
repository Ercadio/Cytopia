#include <SDL2/SDL_image.h>

#include "IconButton.hxx"
#include "../util/LOG.hxx"
#include "AssetHelper.hxx"
#include "../util/filesystem.hxx"

IconButton::IconButton(const std::string & icon, const RGBAColor& color) : 
  m_IconPath(getBasePath() + icon + ".png"),
  m_Color(color),
  m_At(0)
{
}

IconButton::~IconButton() { }

void IconButton::draw(iRendererPtr & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "Drawing a button widget";
  
  std::string fimage = getBasePath();
  fimage += "resources/images/ui/buttons/button.png";

  /* First, we load the sprite */
  std::vector<uint32_t> sprite;
  auto [swidth, sheight] = AssetHelper::LoadImagePixels(fimage, std::back_inserter(sprite));
  if(swidth * sheight == 0)
  {
    LOG(LOG_WARNING) << "Could not properly load texture " << fimage;
    return;
  }
  Rectangle rect{0, 0, swidth-1, sheight-1};

  /* Next, we want to display a specific part depending on the state of our button.
   * So we crop that region */
  swidth = swidth/3;
  Rectangle spriteRect{m_At * swidth, 0, (m_At + 1) * swidth - 1, sheight};
  
  size_t size = AssetHelper::CropImage(
      sprite.data(),
      sprite.data(),
      rect,
      spriteRect
      );
  sprite.resize(size);

  /* Next, we transform magic pixels */
  AssetHelper::ColorMagicPixels(sprite.begin(), sprite.end(), m_Color);

  /* Next, we expand the center of the sprite */
  rect = getBounds();
  auto mind = std::min(rect.width(), rect.height());
  std::vector<uint32_t> pixels(rect.width() * rect.height(), 0x0);
  AssetHelper::NNExpandSprite(sprite.data(), pixels.data(), 
      spriteRect, rect, 
      Rectangle{0, 0, mind / 8, mind / 4});
  
  /* Finally, we draw the picture & icon*/
  renderer->drawPicture(rect, pixels.data());
  
  rect = Rectangle::RescaleCenter(getBounds(), (7<<16)/10);
  rect.translateY(-2);
  LOG(LOG_DEBUG) << rect;
  if(m_At == 2)
  {
    rect.translateY(5);
  }
  sprite.clear();
  std::tie(swidth, sheight) = AssetHelper::LoadImagePixels(m_IconPath, std::back_inserter(sprite));
  pixels.resize(rect.width() * rect.height());
  AssetHelper::ResizeNearest(
      sprite.data(), 
      pixels.data(), 
      Rectangle{0, 0, swidth - 1, sheight - 1},
      rect);
  renderer->drawPicture(rect, pixels.data());
}

void IconButton::update(Notification notif) noexcept
{
  auto state = std::get<ButtonStatus>(notif);
  switch(state)
  {
    case ButtonStatus::Normal:
      m_At = 0;
      LOG(LOG_DEBUG) << "Button back to normal";
      break;
    case ButtonStatus::Disabled:
      m_At = 2;
      LOG(LOG_DEBUG) << "Button disabled";
      break;
    case ButtonStatus::Pressed:
      m_At = 2;
      LOG(LOG_DEBUG) << "Button pressed";
      break;
    case ButtonStatus::Hovered:
      m_At = 1;
      LOG(LOG_DEBUG) << "Button hovered";
      break;
  }
}
