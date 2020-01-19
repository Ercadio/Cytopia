#include "Window.hxx"
#include "SDLRenderer.hxx"
#include "../util/LOG.hxx"
#include <SDL_image.h>

Window::Window(const char * title, unsigned int width, unsigned int height, bool isFullScreen, const string & windowIcon)
{
  m_Window = SDL_CreateWindow(title, 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      width, height, 
      isFullScreen ? SDL_WINDOW_FULLSCREEN : 0);
  if (!m_Window)
    throw UIError(TRACE_INFO "Failed to create window: " + string{SDL_GetError()});

  m_Renderer = std::make_unique<SDLRenderer>(m_Window);
  string iconFName = SDL_GetBasePath() + windowIcon;
  SDL_Surface *icon = IMG_Load(iconFName.c_str());

  if (!icon)
    throw UIError(TRACE_INFO "Could not load icon " + iconFName + ": " + IMG_GetError());

  SDL_SetWindowIcon(m_Window, icon);
  SDL_FreeSurface(icon);
}

Window::~Window()
{
  /* This will destroy the renderer first (required for SDLRenderer) */
  m_Renderer = nullptr;
  SDL_DestroyWindow(m_Window);
}

void Window::setActivity(iActivityPtr activity)
{
  std::swap(m_Activity, activity);
  m_Activity->m_Bounds = getBounds();
  LOG(LOG_DEBUG) << "Setting up new activity";
  m_Activity->setup();
  LOG(LOG_DEBUG) << "Drawing new activity";
  m_Activity->draw(m_Renderer);
}

Rectangle Window::getBounds() const noexcept
{
  return m_Renderer->getDrawableSize();
}
