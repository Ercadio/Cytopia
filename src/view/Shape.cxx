#include <iostream>
#include "Shape.hxx"

Rectangle::Rectangle(int x1, int y1, int x2, int y2) :
  m_x1(x1),
  m_y1(y1),
  m_x2(x2),
  m_y2(y2)
{ }

bool Rectangle::contains() const noexcept
{
  return true;
}

bool Rectangle::boxContains() const noexcept
{
  return true;
}

SDL_Rect Rectangle::to_SDL() const noexcept
{
  return SDL_Rect{m_x1, m_y1, m_x2 - m_x1, m_y2 - m_y1};
}

int Rectangle::width() const noexcept
{
  return m_x2 - m_x1;
}

int Rectangle::height() const noexcept
{
  return m_y2 - m_y1;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
  return os << "Rectangle { x1: " << r.m_x1 
    << ", x2: " << r.m_x2 << ", y1: " << r.m_y1
    << ", y2: " << r.m_y2 << " }";
}
