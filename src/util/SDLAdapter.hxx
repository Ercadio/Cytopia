#ifndef SDL_ADAPTER_HXX
#define SDL_ADAPTER_HXX

class MousePositionEvent;
class ScrollEvent;
class ClickEvent;
class RGBAColor;
class Rectangle;
class SDL_MouseMotionEvent;
class SDL_MouseWheelEvent;
class SDL_MouseButtonEvent;
class SDL_Color;
class SDL_Rect;

namespace sdl
{
  MousePositionEvent toMousePositionEvent(const SDL_MouseMotionEvent&) noexcept;
  ScrollEvent toScrollEvent(const SDL_MouseWheelEvent &) noexcept;
  ClickEvent toClickEvent(const SDL_MouseButtonEvent &) noexcept;
  RGBAColor toColor(const SDL_Color &) noexcept;
  SDL_Color toColor(RGBAColor) noexcept;
  Rectangle toRect(const SDL_Rect &) noexcept;
  SDL_Rect toRect(const Rectangle &) noexcept;
};

#endif // SDL_ADAPTER_HXX
