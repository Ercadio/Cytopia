#ifndef MAP_HXX_
#define MAP_HXX_

#include <vector>
#include <unordered_map>
#include <betterEnums.hxx>
#include "DataModel.hxx"
#include "../util/Meta.hxx"
#include "../util/Point.hxx"
#include "../engine/iGenerator.hxx"
#include "../view/Color.hxx"

using TileType = uint32_t;

struct TileData
{
  TileType type;
  RGBAColor highlight;
};

struct MapChunk
{
  ChunkPosition position;
  std::vector<TileData> tileData;
  TileData & at(const TilePosition &);
};

BETTER_ENUM(MapGeneratorType, uint8_t, Default);

using MapNotification = TypeList<MapChunk, MapGeneratorType, TileData>;

class Map : public DataModel<MapNotification>
{

  std::unordered_map<ChunkPosition, MapChunk> m_Chunks;
  iGeneratorPtr m_Generator;
  MapGeneratorType m_GeneratorType;

public: 

  /**
   * @brief Generates a new chunk
   * @param ChunkPosition the position of the chunk
   * @throws CytopiaError if the chunk already existed
   *         or if ChunkPosition is not a valid position
   * @details Uses the Generator set by ::setGeneratorType
   */
  void generateChunk(ChunkPosition &&);
  
  /**
   * @brief sets the generator to use to create new chunks
   * @param MapGeneratorType the type of the generator
   */
  void setGeneratorType(MapGeneratorType);

  /**
   * @brief sets the data of a specific tile
   * @param TilePosition the position of the tile
   * @param TileData the data to set it to
   */
  void setTileData(TilePosition &&, TileData &&);

  /**
   * @brief sets the data of multiple tiles
   * @tparam PositionIterator an iterator to a collection of tile positions
   * @tparam DataIterator an iterator to a collection of tile data
   * @param pbegin an iterator to the first item in the position collection
   * @param pend an iterator to the first item after the last
   *        in the position collection
   * @param dbegin an iterator to the first item in the data collection
   * @param dend an iterator to the first item after the last
   *        in the data collection
   * @throws CytopiaError if 
   *         std::distance(pbegin, pend) != std::distance(dbegin, dend)
   * @post The content of (dbegin, dend) contains the overwritten data
   */
  template <typename PositionIterator, typename DataIterator>
  void setTilesData(PositionIterator pbegin, PositionIterator pend, 
      DataIterator dbegin, DataIterator dend);

};

#include "Map.inl.hxx"
#endif // MAP_HXX_
