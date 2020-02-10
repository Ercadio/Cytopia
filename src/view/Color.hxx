#ifndef COLOR_HXX_
#define COLOR_HXX_

#include <cstdint>
#include <SDL2/SDL.h>

struct RGBAColor
{
  uint32_t m_Color;
public:
  RGBAColor(uint32_t);
  SDL_Color to_SDL() const noexcept;
};

#endif // COLOR_HXX_
