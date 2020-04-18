#include "CursorView.hxx"
#include "../util/filesystem.hxx"
#include "../view/AssetHelper.hxx"
#include "../util/ZipRange.hxx"

CursorView::CursorView()
{
  /* Load all cursors */
  std::vector<uint32_t> pixels;
  int swidth = 0, sheight = 0;
  {
    std::string path = getBasePath();
    path += "resources/images/ui/general/cursors.png";
    std::tie(swidth, sheight) = AssetHelper::LoadImagePixels(path, 
        std::back_inserter(pixels));
  }
  swidth /= 5;
  std::array cropsFrom = {
    Rectangle{0*swidth, 0, 1*swidth-1, sheight-1},
    Rectangle{1*swidth, 0, 2*swidth-1, sheight-1},
    Rectangle{2*swidth, 0, 3*swidth-1, sheight-1},
    Rectangle{3*swidth, 0, 4*swidth-1, sheight-1},
    Rectangle{4*swidth, 0, 5*swidth-1, sheight-1},
    Rectangle{0, 0, 0, 0}
  };
  Rectangle rto {0, 0, swidth-1, sheight-1};
  Rectangle rscaled {
    0, 0, 
    ((rto.width() * CursorScaleSize::value) >> 16) - 1,
    ((rto.height() * CursorScaleSize::value) >> 16) - 1
  };
  std::array hot_xs = {1, 3, 5, 5};
  std::array hot_ys = {1, 1, 8, 10};
  auto range = ZipRange{CursorType::_values(), hot_xs, hot_ys, cropsFrom};
  for(auto [type, hotx, hoty, rfrom] : range)
  {
    std::vector<uint32_t> sprite(rto.width() * rto.height(), 0x0);
    AssetHelper::CropImage(pixels.data(), sprite.data(), 
        rfrom, rto);
    sprite.resize(rscaled.width() * rscaled.height());
    AssetHelper::ResizeNearest(sprite.data(), sprite.data(), rto, rscaled);
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        sprite.data(), 
        rscaled.width(), 
        rscaled.height(), 
        32, 4 * rscaled.width(),
        0xff000000,
        0x00ff0000,
        0x0000ff00,
        0x000000ff
        );
    CursorPtr cursor { SDL_CreateColorCursor(surface, hotx, hoty) };
    m_Cursors[type._to_integral()] = std::move(cursor);
  }
}

void CursorView::update(Notification notif) noexcept
{
  CursorType type = std::get<MouseStateModel>(notif).cursorType;
  SDL_Cursor* cursor = m_Cursors[type._to_integral()].get();
  LOG(LOG_DEBUG) << "Setting cursor";
  SDL_SetCursor(cursor);
}

void CursorView::CursorDeleter::operator()(SDL_Cursor * ptr) const noexcept
{ SDL_FreeCursor(ptr); }
