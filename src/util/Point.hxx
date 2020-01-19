#ifndef POINT_HXX_
#define POINT_HXX_
#include "Meta.hxx"

struct Point2D
{
  int x;
  int y;
};

struct TilePosition : public Point2D { };

struct ChunkPosition : public Point2D
{
  ChunkPosition();
  explicit ChunkPosition(const TilePosition &);
};

template<> struct std::hash<ChunkPosition>
{
  std::size_t operator()(const Point2D & p) const noexcept
  {
    auto [x, y] = p;
    return x ^ (y << 1);
  }
};

using ChunkSize = Constant<128>;

struct Point
{
  /**
   * The x coordinate.
   */
  int x;

  /**
   * The y coordinate.
   */
  int y;

  /**
   * The z coordinate.
   */
  int z;

  /**
   * The height level.
   */
  int height;
};

bool operator==(const Point2D &, const Point2D &);

#endif
