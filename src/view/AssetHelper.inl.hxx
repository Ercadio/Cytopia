
template <typename OutputIterator>
std::pair<int, int> AssetHelper::LoadImagePixels(const std::string & filepath, OutputIterator it)
{
  auto surface = IMG_Load(filepath.c_str());
  if(!surface)
  {
    LOG(LOG_WARNING) << TRACE_INFO "Couldn't load image pixels: " << IMG_GetError();
    return {0, 0};
  }
  auto format = surface->format;
  auto pixels = static_cast<uint32_t*>(surface->pixels);
  for(uint32_t i = 0; i < surface->w * surface->h; ++i)
  {
    *it++ = 
      (pixels[i] & format->Rmask) >> format->Rshift << 24 |
      (pixels[i] & format->Gmask) >> format->Gshift << 16 |
      (pixels[i] & format->Bmask) >> format->Bshift << 8  |
      (pixels[i] & format->Amask) >> format->Ashift << 0;
  }
  int w = surface->w, h = surface->h;
  SDL_FreeSurface(surface);
  return {w, h};
}
