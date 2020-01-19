#ifndef SDL_RENDERER_HXX_
#define SDL_RENDERER_HXX_
#include <SDL2/SDL.h>
#include "iRenderer.hxx"

class SDLRenderer final : public iRenderer
{
  SDL_Renderer * m_Renderer;
public:
  SDLRenderer(SDL_Window *);
  ~SDLRenderer() final;
  void drawText() final;
  void drawPicture() final;
  void drawShape(const Rectangle &, RGBAColor) final;
  void drawLine() final;
  Rectangle getDrawableSize() const noexcept final;
};

#endif // SDL_RENDERER_HXX_
