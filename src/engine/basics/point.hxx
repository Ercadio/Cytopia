#pragma once

#ifndef POINT_HXX_
#define POINT_HXX_

struct Point
{
  Point() = default;
  /**
   * The x coordinate.
   */
  int x = 0;

  /**
   * The y coordinate.
   */
  int y = 0;

  /**
   * The z coordinate.
   */
  int z = 0;

  /**
   * The height level.
   */
  int height = 0;
};

#endif
