#ifndef I_GENERATOR_HXX_
#define I_GENERATOR_HXX_
#include <memory>
#include "../util/Point.hxx"

class iGenerator
{
public:
  virtual ~iGenerator() = 0;
  virtual void generate(ChunkPosition &&, class MapChunk *) noexcept = 0;
};

using iGeneratorPtr = std::unique_ptr<iGenerator>;

#endif // I_GENERATOR_HXX_
