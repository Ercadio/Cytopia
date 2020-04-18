#ifndef WINDOW_HXX_
#define WINDOW_HXX_

#include <string>
#include <SDL2/SDL.h>
#include "../activity/iActivity.hxx"
#include "../renderer/iRenderer.hxx"
#include "../view/Shape.hxx"
#include "../view/CursorView.hxx"
#include "../events/UIEvents.hxx"
#include "../model/MouseState.hxx"
#include "../GlobalModel.hxx"

using std::string;

class Window
{
  SDL_Window* m_Window;
  iRendererPtr m_Renderer;
  iActivityPtr m_Activity;
  CursorViewPtr m_Cursor;
  GlobalModel & m_GlobalModel;

  void handleEvent(WindowResizeEvent&&);
  void handleEvent(WindowRedrawEvent&&);

  template <typename... Args>
  iActivityPtr fromActivityType(ActivityType, Args&&...);
  friend class Game;  
public:
  Window(const char * title, unsigned int width, unsigned int height, bool isFullScreen, const string & windowIcon, GlobalModel & globalModel);
  virtual ~Window() = 0;
  void setActivity(iActivityPtr);
  GlobalModel & getGlobalModel();
  Rectangle getBounds() const noexcept;
};

#include "Window.inl.hxx"

#endif // WINDOW_HXX_
