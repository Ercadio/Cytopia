#ifndef I_SHAPE_HXX
#define I_SHAPE_HXX

#include <SDL2/SDL.h>
#include <iostream>

class iShape
{
public:
  virtual bool contains() const noexcept = 0;
  virtual bool boxContains() const noexcept = 0;
};

class Rectangle : public iShape
{
  int m_x1;
  int m_y1;
  int m_x2;
  int m_y2;
public:
  Rectangle(int x1, int y1, int x2, int y2);
  virtual bool contains() const noexcept override;
  virtual bool boxContains() const noexcept override;
  SDL_Rect to_SDL() const noexcept;
  int width() const noexcept;
  int height() const noexcept;
  friend std::ostream& operator<<(std::ostream&, const Rectangle&);
};

#endif // I_SHAPE_HXX
