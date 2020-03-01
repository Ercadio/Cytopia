#include <SDL2/SDL_image.h>

#include "TextButton.hxx"
#include "../util/LOG.hxx"
#include "AssetHelper.hxx"

TextButton::TextButton(const char * text, RGBAColor color) :
  m_At(0), 
  m_Color(color),
  m_Text(text)
{
}

TextButton::~TextButton() { }

void TextButton::draw(iRendererPtr & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "Drawing a button widget";
  std::string fimage = SDL_GetBasePath();
  fimage += "resources/images/ui/buttons/button.png";
  auto rect = getBounds();

  /* First, we load the sprite */
  std::vector<uint32_t> sprite;
  auto [swidth, sheight] = AssetHelper::LoadImagePixels(fimage, std::back_inserter(sprite));
  
  if(swidth * sheight == 0)
  {
    LOG(LOG_WARNING) << "Could not properly load texture " << fimage;
    return;
  }

  /* Next, we want to display a specific part depending on the state of our button.
   * So we crop that region */
  Rectangle spriteRect{m_At, 0, m_At + swidth/3, sheight};
  AssetHelper::CropImage(
      sprite.data(),
      Rectangle{0, 0, swidth, sheight},
      spriteRect
      );
  
  /* Next, we transform magic pixels */
  AssetHelper::ColorMagicPixels(sprite.data(), m_Color);

  /* Next, we expand the center of the sprite */
  std::vector<uint32_t> pixels(rect.width() * rect.height(), 0xFFFFFF5F);
  AssetHelper::ExpandSprite(sprite.data(), pixels.data(), 
      spriteRect, rect);
  
  /* Finally, we draw the picture & text */
  renderer->drawPicture(rect, pixels.data());
  renderer->drawText(m_Text, RGBAColor{0xFFFFFFFF}, getBounds(), PositionType::Centered);
}

void TextButton::update(Notification notif) noexcept
{
  auto state = std::get<ButtonStatus>(notif);
  switch(state)
  {
    case ButtonStatus::Normal:
      LOG(LOG_DEBUG) << "Button back to normal";
      break;
    case ButtonStatus::Disabled:
      LOG(LOG_DEBUG) << "Button disabled";
      break;
    case ButtonStatus::Pressed:
      LOG(LOG_DEBUG) << "Button pressed";
      break;
    case ButtonStatus::Hovered:
      LOG(LOG_DEBUG) << "Button hovered";
      break;
  }
}
