#ifndef SDL_RENDERER_HXX_
#define SDL_RENDERER_HXX_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "iRenderer.hxx"

class SDLRenderer final : public iRenderer
{
  SDL_Renderer * m_Renderer;
  TTF_Font * m_Font;
  std::vector<SDL_Texture*> m_Textures;
public:
  SDLRenderer(SDL_Window *);
  ~SDLRenderer() final;
  void drawText(const char *, RGBAColor, const Rectangle &, PositionType) final;
  void drawPicture(const Rectangle &, uint32_t*) final;
  void drawShape(const Rectangle &, RGBAColor) final;
  void drawLine() final;
  Rectangle getDrawableSize() const noexcept final;
private:
  void commit() final;
  void clear() final;
};

#endif // SDL_RENDERER_HXX_
