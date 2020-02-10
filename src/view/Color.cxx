#include "Color.hxx"

RGBAColor::RGBAColor(uint32_t color) : m_Color(color) { }

SDL_Color RGBAColor::to_SDL() const noexcept
{
  return SDL_Color{
    static_cast<uint8_t>((m_Color >> 24) & 0xFF),
    static_cast<uint8_t>((m_Color >> 16) & 0xFF),
    static_cast<uint8_t>((m_Color >> 8) & 0xFF),
    static_cast<uint8_t>((m_Color >> 0) & 0xFF)
  };
}
