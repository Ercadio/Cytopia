#include "SDLRenderer.hxx"
#include "../util/Exception.hxx"
#include "../util/LOG.hxx"
#include "../util/filesystem.hxx"

SDLRenderer::SDLRenderer(SDL_Window * sdl_window)
{
  m_Renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  
  if (!m_Renderer)
    throw UIError(TRACE_INFO "Failed to create Renderer: " + string{SDL_GetError()});

  if(SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND) != 0)
    throw CytopiaError{TRACE_INFO "Failed to enable Alpha" + string{SDL_GetError()}};
  
  std::string font = getBasePath();
  font += "resources/fonts/arcadeclassics.ttf";
  m_Font = TTF_OpenFont(font.c_str(), 24);
  if(!m_Font)
    throw CytopiaError{TRACE_INFO "Failed to open font Sans.ttf: " 
      + string{TTF_GetError()}};

  if(SDL_RenderClear(m_Renderer) != 0)
    throw CytopiaError{TRACE_INFO "Failed to clear canvas" + string{SDL_GetError()}};
  SDL_RenderPresent(m_Renderer);
  
  const char * error = SDL_GetError();
  if(*error)
  {
    LOG(LOG_ERROR) << TRACE_INFO "SDL Error: " << error;
    SDL_ClearError();
  }
}

SDLRenderer::~SDLRenderer()
{
  const char * error = SDL_GetError();
  if(*error)
    LOG(LOG_ERROR) << "SDL Error: " << error;

  SDL_RenderClear(m_Renderer);
  //if(m_Font != nullptr)
  // TTF_CloseFont(m_Font);
  LOG(LOG_WARNING) << "Destroying my renderer...";
  //SDL_DestroyRenderer(m_Renderer);
  LOG(LOG_WARNING) << "Done";
}

void SDLRenderer::drawText(
    const char * text, 
    RGBAColor color, 
    const Rectangle & position,
    PositionType psType)
{
  SDL_Surface* surface = TTF_RenderUTF8_Blended(m_Font, text, color.to_SDL());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
  SDL_Rect rect = position.to_SDL();
  rect.w = surface->w;
  rect.h = surface->h;
  switch(psType)
  {
    case PositionType::Centered:
      rect.x += (position.width() - surface->w) / 2;
      rect.y += (position.height() - surface->h) / 2;
      break;
    case PositionType::Normal:
      break;
  }
  SDL_RenderCopy(m_Renderer, texture, nullptr, &rect);
  SDL_FreeSurface(surface);
  m_Textures.push_back(texture);
}

void SDLRenderer::drawPicture(const Rectangle & rect, uint32_t * data)
{
  SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
      data, 
      rect.width(), 
      rect.height(), 
      32, 4 * rect.width(),
      0xff000000,
      0x00ff0000,
      0x0000ff00,
      0x000000ff
      );
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
  SDL_Rect position = rect.to_SDL();
  SDL_RenderCopy(m_Renderer, texture, nullptr, &position);
  SDL_FreeSurface(surface);
  m_Textures.push_back(texture);
}

void SDLRenderer::drawShape(const Rectangle & r, RGBAColor c)
{
  auto color = c.to_SDL();
  SDL_SetRenderDrawColor(m_Renderer,
      color.r,
      color.g,
      color.b,
      color.a
  );
  SDL_Rect rect = r.to_SDL();
  SDL_RenderFillRect(m_Renderer, &rect);
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

void SDLRenderer::commit()
{
  SDL_RenderPresent(m_Renderer);
  const char * error = SDL_GetError();
  if(*error)
    LOG(LOG_ERROR) << "SDL Error: " << error;

}

void SDLRenderer::clear()
{
  SDL_RenderClear(m_Renderer);
  const char * error = SDL_GetError();
  if(*error)
    LOG(LOG_ERROR) << "SDL Error: " << error;

}
