#include <iostream>
#include "Shape.hxx"
#include "../util/LOG.hxx"

Rectangle::Rectangle(int x1, int y1, int x2, int y2) :
  m_x1(x1),
  m_y1(y1),
  m_x2(x2),
  m_y2(y2)
{ }

bool Rectangle::contains(const Point2D & p) const noexcept
{
  return p.x <= m_x2 && p.x >= m_x1 && p.y <= m_y2 && p.y >= m_y1;
}

Rectangle Rectangle::getBounds() const noexcept
{
  return *this;
}

SDL_Rect Rectangle::to_SDL() const noexcept
{
  return SDL_Rect{m_x1, m_y1, m_x2 - m_x1, m_y2 - m_y1};
}

int Rectangle::width() const noexcept
{
  return m_x2 - m_x1 + 1;
}

int Rectangle::height() const noexcept
{
  return m_y2 - m_y1 + 1;
}

std::pair<int, int> Rectangle::p1() const noexcept { return {m_x1, m_y1}; }

std::pair<int, int> Rectangle::p2() const noexcept { return {m_x2, m_y2}; }
  
void Rectangle::translateX(int x)
{
  m_x1 += x;
  m_x2 += x;
}

void Rectangle::translateY(int y)
{
  m_y1 += y;
  m_y2 += y;
}

void Rectangle::intersect(const Rectangle & other)
{
  auto [op1x, op1y] = other.p1();
  auto [op2x, op2y] = other.p2();
  m_x1 = std::clamp(m_x1, op1x, op2x);
  m_y1 = std::clamp(m_y1, op1y, op2y);
  m_x2 = std::clamp(m_x2, op1x, op2x);
  m_y2 = std::clamp(m_y2, op1y, op2y);
}

Rectangle Rectangle::RescaleCenter(const Rectangle & rect, uint32_t zoom)
{
  auto [p1x, p1y] = rect.p1();
  auto [p2x, p2y] = rect.p2();
  int avgx = (p1x + p2x) / 2;
  int avgy = (p1y + p2y) / 2;
  p1x = avgx - (((avgx - p1x) * zoom) >> 16);
  p2x = (((p2x - avgx) * zoom) >> 16) + avgx;
  p1y = avgy - (((avgy - p1y) * zoom) >> 16);
  p2y = (((p2y - avgy) * zoom) >> 16) + avgy;
  return Rectangle{p1x, p1y, p2x, p2y};
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
  return os << "Rectangle { x1: " << r.m_x1 
    << ", x2: " << r.m_x2 << ", y1: " << r.m_y1
    << ", y2: " << r.m_y2 << " }";
}
