#include "Point.hxx"

ChunkPosition::ChunkPosition() = default;

ChunkPosition::ChunkPosition(const TilePosition & tPos) :
  Point2D { tPos.x / ChunkSize::value, tPos.y / ChunkSize::value }
{ }

bool operator==(const Point2D & p1, const Point2D & p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}
