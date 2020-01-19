#include "DefaultGenerator.hxx"
#include "../model/Map.hxx"

DefaultGenerator::~DefaultGenerator() { }

void DefaultGenerator::generate(ChunkPosition && cPos, MapChunk * pChunk) noexcept
{
  for(TileData & tile : pChunk->tileData)
    tile = TileData{0, RGBAColor{0} };
}
