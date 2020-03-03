#include "filesystem.hxx"

std::string getBasePath() noexcept
{
  char * path = SDL_GetBasePath();
  std::string spath{path};
  SDL_free(path);
  return std::move(spath);
}
