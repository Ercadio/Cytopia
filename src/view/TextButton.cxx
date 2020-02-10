#include <SDL2/SDL_image.h>

#include "TextButton.hxx"
#include "../util/LOG.hxx"
#include "AssetHelper.hxx"

TextButton::TextButton(const char * text) : m_Text(text)
{
}

TextButton::~TextButton() { }

void TextButton::draw(iRendererPtr & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "Drawing a button widget";
  std::string fimage = SDL_GetBasePath();
  fimage += "resources/images/ui/buttons/text_button.png";
  auto rect = getBounds();
  std::vector<uint32_t> sprite;
  auto [swidth, sheight] = AssetHelper::LoadImagePixels(fimage, std::back_inserter(sprite));
  std::vector<uint32_t> pixels(rect.width() * rect.height(), 0xFFFFFF5F);
  if(swidth * sheight != 0)
    AssetHelper::MakeColRepeatImage(
        sprite.data(), pixels.data(), 
        Rectangle{0, 0, swidth, sheight },
        rect);
  else
    LOG(LOG_WARNING) << "Could not load texture";
  renderer->drawPicture(rect, pixels.data());
  renderer->drawText(m_Text, RGBAColor{0xFFFFFFFF}, getBounds(), PositionType::Centered);
}

void TextButton::update(Notification notif) noexcept
{
  LOG(LOG_WARNING) << "IDK how to update :(";
}
