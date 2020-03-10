#ifndef WINDOW_HXX_
#define WINDOW_HXX_

#include <string>
#include <SDL2/SDL.h>
#include "iActivity.hxx"
#include "iRenderer.hxx"
#include "Shape.hxx"
#include "../events/UIEvents.hxx"

using std::string;

class Window
{
  SDL_Window* m_Window;
  iRendererPtr m_Renderer;
  iActivityPtr m_Activity;

  void handleEvent(WindowResizeEvent&&);
  void handleEvent(WindowRedrawEvent&&);

  template <typename... Args>
  iActivityPtr fromActivityType(ActivityType, Args&&...);
  friend class Game;  
public:
  Window(const char * title, unsigned int width, unsigned int height, bool isFullScreen, const string & windowIcon);
  virtual ~Window() = 0;
  void setActivity(iActivityPtr);
  Rectangle getBounds() const noexcept;
};

#include "Window.inl.hxx"

#endif // WINDOW_HXX_
