#ifndef DEFAULT_GENERATOR_HXX_
#define DEFAULT_GENERATOR_HXX_
#include "iGenerator.hxx"

class DefaultGenerator : public iGenerator
{
public:
  virtual ~DefaultGenerator() override;
  virtual void generate(ChunkPosition &&, class MapChunk *) noexcept override;
};

#endif // DEFAULT_GENERATOR_HXX_
