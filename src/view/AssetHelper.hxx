#ifndef ASSET_HELPER_HXX_
#define ASSET_HELPER_HXX_

#include <cstdint>
#include <tuple>
#include <SDL2/SDL_image.h>

#include "Shape.hxx"
#include "../util/LOG.hxx"

namespace AssetHelper
{
  void MakeColRepeatImage(uint32_t*, uint32_t*, const Rectangle &, const Rectangle &);
  void ResizeNearest(uint32_t*, uint32_t*, const Rectangle &, const Rectangle &);
  void RepeatXY(uint32_t*, uint32_t*, const Rectangle &, const Rectangle &);
  template <typename OutputIterator>
  static std::pair<int, int> LoadImagePixels(const std::string &, OutputIterator);
};

#include "AssetHelper.inl.hxx"

#endif // ASSET_HELPER_HXX_
