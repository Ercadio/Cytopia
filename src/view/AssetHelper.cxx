#include "AssetHelper.hxx"
#include "../util/LOG.hxx"

void AssetHelper::MakeColRepeatImage(uint32_t* orig, uint32_t* dest, const Rectangle & orig_rect, const Rectangle & dest_rect)
{
  uint32_t ow = orig_rect.width();
  uint32_t oh = orig_rect.height();
  uint32_t dw = dest_rect.width();
  uint32_t dh = dest_rect.height();

  uint32_t y_ratio = (oh - 1) << 16;
  y_ratio /= (dh - 1);
  uint32_t min_x = ow * dh / 2 / oh;
  uint32_t max_x = dw - min_x;
  
  for(size_t i = 0; i < dw * dh; ++i)
  {
    uint32_t x = i % dw;
    x = std::min(
        x,
        std::clamp(x, max_x, dw) - max_x + min_x);
    x *= y_ratio;
    x >>= 16;
    uint32_t y = (i / dw) * y_ratio >> 16;
    dest[i] = orig[x + y * ow];
  }
}

void AssetHelper::ResizeNearest(uint32_t* orig, uint32_t* dest, const Rectangle & orig_rect, const Rectangle & dest_rect)
{
  uint32_t ow = orig_rect.width();
  uint32_t oh = orig_rect.height();
  uint32_t dw = dest_rect.width();
  uint32_t dh = dest_rect.height();

  uint32_t x_ratio = ow << 16;
  x_ratio /= dw;
  uint32_t y_ratio = oh << 16;
  y_ratio /= dh;

  for(size_t i = 0; i < dw * dh; ++i)
  {
    uint32_t x = (i % dw) * x_ratio >> 16;
    uint32_t y = (i / dw) * y_ratio >> 16;
    dest[i] = orig[x + y * ow];
  }
}

void AssetHelper::RepeatXY(uint32_t* orig, uint32_t* dest, const Rectangle & orig_rect, const Rectangle & dest_rect)
{
  uint32_t ow = orig_rect.width();
  uint32_t oh = orig_rect.height();
  uint32_t dw = dest_rect.width();
  uint32_t dh = dest_rect.height();
  
  for(size_t i = 0; i < dw * dh; ++i)
  {
    uint32_t x = i % dw % ow;
    uint32_t y = i / dw % oh;
    dest[i] = orig[x + y * ow];
  }
}
