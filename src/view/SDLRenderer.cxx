#include "SDLRenderer.hxx"
#include "../util/Exception.hxx"
#include "../util/LOG.hxx"

#include <SDL2/SDL.h>

SDLRenderer::SDLRenderer(SDL_Window * sdl_window)
{
  m_Renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

  if (!m_Renderer)
    throw UIError(TRACE_INFO "Failed to create Renderer: " + string{SDL_GetError()});

  if(SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND) != 0)
    throw CytopiaError{TRACE_INFO "Failed to enable Alpha" + string{SDL_GetError()}};
  if(SDL_RenderClear(m_Renderer) != 0)
    throw CytopiaError{TRACE_INFO "Failed to clear canvas" + string{SDL_GetError()}};
  SDL_RenderPresent(m_Renderer);
}

SDLRenderer::~SDLRenderer()
{
  SDL_DestroyRenderer(m_Renderer);
}

void SDLRenderer::drawText()
{
  throw UnimplementedError{TRACE_INFO "Unimplemented"};
}

void SDLRenderer::drawPicture()
{
  throw UnimplementedError{TRACE_INFO "Unimplemented"};
}

void SDLRenderer::drawShape(const Rectangle & r, RGBAColor c)
{
  uint32_t color = c.get();
  SDL_SetRenderDrawColor(m_Renderer, 
      (color >> 24) & 0xFF,
      (color >> 16) & 0xFF,
      (color >> 8) & 0xFF,
      (color >> 0) & 0xFF
  );
  SDL_Rect rect = r.to_SDL();
  SDL_RenderFillRect(m_Renderer, &rect);
  SDL_RenderPresent(m_Renderer);
}

void SDLRenderer::drawLine()
{
  throw UnimplementedError{TRACE_INFO "Unimplemented"};
}

Rectangle SDLRenderer::getDrawableSize() const noexcept
{
  int w, h;
  SDL_GetRendererOutputSize(m_Renderer, &w, &h);
  return Rectangle{ 0, 0, w, h };
}
