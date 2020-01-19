#include "Map.hxx"
#include "../engine/DefaultGenerator.hxx"

TileData & MapChunk::at(const TilePosition & tpos)
{
  return tileData.at(
      (tpos.x % ChunkSize::value) + ChunkSize::value * (tpos.y % ChunkSize::value)
  );
}

void Map::generateChunk(ChunkPosition && position)
{
  if(m_Chunks.count(position))
    throw CytopiaError(TRACE_INFO "Cannot generate a chunk that already exists");
   m_Generator->generate(std::move(position), &m_Chunks[position]);
}

void Map::setGeneratorType(MapGeneratorType type)
{
  switch(type)
  {
    case MapGeneratorType::Default:
      m_Generator = iGeneratorPtr{new DefaultGenerator};
  }
  std::swap(type, m_GeneratorType);
  notifyObservers(ChangeNotification{type, m_GeneratorType});
}

void Map::setTileData(TilePosition && position, TileData && data)
{
  auto & tile = m_Chunks
    .at(ChunkPosition(position))
    .at(position);
  std::swap(tile, data);
  notifyObservers(ChangeNotification{data, tile});
}


