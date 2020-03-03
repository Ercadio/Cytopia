#ifndef FILESYSTEM_HXX_
#define FILESYSTEM_HXX_

#include <ciso646>
#include "SDL2/SDL.h"

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#pragma message("Warning: Your compiler does not support the filesystem library. Please report this incident to the Cytopia Team")
#endif

std::string getBasePath() noexcept;

#endif
