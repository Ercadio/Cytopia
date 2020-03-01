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

void AssetHelper::ExpandSprite(uint32_t* from, uint32_t* to, 
    const Rectangle & rfrom, const Rectangle & rto, const Rectangle & corner)
{
  uint32_t ow = rfrom.width();
  uint32_t oh = rfrom.height();
  uint32_t dw = rto.width();
  uint32_t dh = rto.height();
  uint32_t rw = corner.width();
  uint32_t rh = corner.height();

  if(dw * dh == 0)
    return;

  // x_ratio is the amount to x-scale corners * 2^16
  uint32_t x_ratio = rw << 16;
  x_ratio /= dw / 2;
  // y_ratio is the amount to y-scale corners * 2^16
  uint32_t y_ratio = rh << 16;
  y_ratio /= dh / 2;

  uint32_t min_x = rw;
  uint32_t max_x = dw - rw;
  uint32_t min_y = rh;
  uint32_t max_y = dw - rh;
  
  for(size_t i = 0; i < dw * dh; ++i)
  {
    uint32_t x = i % dw;
    x = std::min(x,
          std::clamp(x, max_x, dw) - max_x + min_x);
    x *= x_ratio;
    x >>= 16;
    y = std::min(y,
          std::clamp(y, may_y, dw) - may_y + min_y);
    y *= y_ratio;
    y >>= 16;
    dest[i] = orig[x + y * ow];
  }
}

void AssetHelper::CropImage(uint32_t* data, const Rectangle & from, const Rectangle & to)
{
}

void AssetHelper::ColorMagicPixels(uint32_t* begin, uint32_t* end, int hue)
{
  hue %= 360;
  hue += 360; // Catch negative modulos
  hue %= 360;
  hue /= 60;  // Now hue is in [0, 5]
  
  while(begin != end)
  {
    if((*begin >> 8) & 0xFF == (*begin >> 24) & 0xFF)
    {
      /* This is a magic pixel */
      uint8_t [min, max] = std::minmax({
          *begin >> 8 & 0xFF, 
          *begin >> 16 & 0xFF, 
          *begin >> 24 & 0xFF}
      );
      uint8_t alpha = *begin & 0xFF;
      uint8_t chroma = max - min;
      uint8_t X = chroma * (1 - std::abs(hue % 2 - 1))
      uint8_t ligthness = (max + min) / 2;
      uint8_t m = ligthness - chroma / 2;
      switch(hue)
      {
        case 0:
          *begin = m * 0x01010100 
            + chroma << 24
            + X << 16
            + alpha;
          break;
        case 1:
          *begin = m * 0x01010100 
            + chroma << 16
            + X << 24
            + alpha;
          break;
        case 2:
          *begin = m * 0x01010100 
            + chroma << 16
            + X << 8
            + alpha;
          break;
        case 3:
          *begin = m * 0x01010100 
            + chroma << 8
            + X << 16
            + alpha;
          break;
        case 4:
          *begin = m * 0x01010100 
            + chroma << 8
            + X << 16
            + alpha;
          break;
        case 5:
          *begin = m * 0x01010100 
            + chroma << 16
            + X << 8
            + alpha;
          break;
      }
    }
    ++begin;
  }
}
