#include "../util/Exception.hxx"
#include "../util/LOG.hxx"

template <typename PositionIterator, typename DataIterator>
void Map::setTilesData(PositionIterator pbegin, PositionIterator pend, 
    DataIterator dbegin, DataIterator dend)
{
  if(std::distance(pbegin, pend) != std::distance(dbegin, dend))
    throw CytopiaError{TRACE_INFO "Cannot set the tiles with iterators pointing to different lengths"};
  while(pbegin != pend)
    m_Chunks
      .at(ChunkPosition{*pbegin})
      .tileData
      .at(*pbegin++) = *dbegin++;
}

