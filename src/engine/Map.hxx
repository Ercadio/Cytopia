#ifndef MAP_HXX_
#define MAP_HXX_

#include <vector>

#include "GameObjects/MapNode.hxx"
#include "map/TerrainGenerator.hxx"

class Map
{
public:
  //fixed MapNode* array to store neighbors.
  using NeighborMatrix = MapNode * [9];

  std::vector<std::unique_ptr<MapNode>> mapNodes;
  std::vector<MapNode *> mapNodesInDrawingOrder;

  Map() = default;
  Map(int columns, int rows);
  ~Map() = default;


  /** 
   * @brief Initialize the Map with node objects
   */
  void initMap();

  /** 
   * @brief Increase Height
   * @details Increases the height of the node and checks the surrounding tiles. Either draw a slope sprite or elevate the tile if 
   *          necessary. 
   * @param isoCoordinates the isometric coordinates of the tile that should be elevated
   */
  void increaseHeight(const Point &isoCoordinates);

  /** 
   * @brief Decrease Height
   * @details Decreases the height of the node and checks the surrounding tiles. Either draw a slope sprite or lower the tile if
   *          necessary.
   * @param isoCoordinates the isometric coordinates of the tile that should be elevated
   */
  void decreaseHeight(const Point &isoCoordinates);

  /** 
   * @brief Render the elements contained in the Map
   * call the render() function of the sprite in the all contained MapNode elements
   * @see Sprite::render
   */
  void renderMap() const;

  /**
   * @brief Sets a node to be highlighted
   * @details This sets a node to be highlighted, the highlighting is done during rendering
   * @param isoCoordinates which node should be highlit
   * @param rgbColor the color of the highlight
   */
  void highlightNode(const Point &isoCoordinates, const SpriteRGBColor &rgbColor);

  /**
   * @brief Sets a node to be unhighlit
   * @details This sets a node to be unhighlit, the highlighting is done during rendering
   * @param isoCoordinates which node should be unhighlit.
   */
  void unHighlightNode(const Point &isoCoordinates);

  /**
   * @brief Find a node in the map
   * @param screenCoordinates the coordinates of the Node
   * @returns Point in the map
   */
  Point findNodeInMap(const SDL_Point &screenCoordinates) const;

  /**
   * @brief Set the Tile ID of a Node
   * @details Invokes all necessary texture updates (auto-tiling, slopes, ...)
   * @param begin an iterator to the first element
   * @param end an iterator to past the last element
   * @param tileID The tileID of the node to set
   * @tparam Iterator the iterator's type
   */
  template <typename Iterator> void setTileIDOfNode(Iterator begin, Iterator end, const std::string &tileID);

  /**
   * @brief Demolish a node
   * @details Invokes the tiles demolish function
   * @param isoCoordinates the coordinate to demolish
   * @param updateNeighboringTiles whether or not to update neighbors
   * @see MapNode::demolishNode
   */
  void demolishNode(const Point &isoCoordinates, bool updateNeighboringTiles = false);

  /**
   * @brief Refresh all the map tile textures
   * @see Sprite::refresh
   */
  void refresh();

  /** 
   * @brief Save Map to file
   * @details Serializes the Map class to json and writes the data to a file.
   * @param string fileName The file the map should be written to
   */
  void saveMapToFile(const std::string &fileName);

  /** 
   * @brief Load Map from file
   * @detailsDeserializes the Map class from a json file, creates a new Map and returns it.
   * @param string fileName The file the map should be written to
   * @returns Map* Pointer to the newly created Map.
   */
  static Map *loadMapFromFile(const std::string &fileName);

  /**
   * @brief Debug MapNodeData to Console
   * @details Used as Tile-Inspector until we implement a GUI variant
   * @param isoCoordinates Tile to inspect
   */
  void getNodeInformation(const Point &isoCoordinates) const;

  /**
   * @brief check if Tile is occupied
   * @param isoCoordinates Tile to inspect
   * @param tileID tileID which should be checked
   */
  bool checkTileIDIsEmpty(const Point &isoCoordinates, const std::string &tileID) const;

private:
  
  int m_columns;
  int m_rows;

  TerrainGenerator terrainGen;

  static const size_t m_saveGameVersion;

  /**
   * @brief Update mapNode and its adjacent tiles
   * @details Updates mapNode height information, draws slopes for adjacent tiles and sets tiling for mapNode sprite if applicable
   * @param Point isoCoordinates - isometric coordinates of the tile that should be updated.
   */
  void updateNeighborsOfNode(const Point &isoCoordinates);

  /**
   * @brief Update all mapNodes 
   * @details Updates all mapNode and its adjacent tiles regarding height information, draws slopes for adjacent tiles and 
   *          sets tiling for mapNode sprite if applicable
   */
  void updateAllNodes();

  /**\brief Get neighbor MapNode Objects
    * Stores pointers to the neighboring nodes of the given coordinates in the passed parameter.
    * @param Point isoCoordinates - isometric coordinates of the tile that's neighbors should be retrieved.
    * @param NeighborMatrix result - Pass a ref of type neighbormatrix to store the found neighbors in.
    */
  void getNeighbors(const Point &isoCoordinates, NeighborMatrix &result) const;

  /** 
   * @brief Get elevated neighbor positions in a bitmask
   * @details Checks all neighboring tiles and returns the elevated neighbors in a bitmask:
   * [ BR BL TR TL  R  L  B  T ]
   * [ 0  0  0  0   0  0  0  0 ]
   * @param isoCoordinates isometric coordinates of the tile whose neighbors should be retrieved
   * @returns  Uint that stores the elevated neighbor tiles
   */
  unsigned char getElevatedNeighborBitmask(const Point &isoCoordinates);

  /** \brief Get a bitmask that represents same-tile neighbors
  * Checks all neighboring tiles and returns the elevated neighbors in a bitmask:
  * [ BR BL TR TL  R  L  B  T ]
  * [ 0  0  0  0   0  0  0  0 ]
  * @param isoCoordinates isometric coordinates of the tile whose neighbors should be retrieved
  * @returns  Uint that stores the neighbor tiles
  */
  unsigned char getNeighboringTilesBitmask(const Point &isoCoordinates);

  SDL_Color getColorOfPixelInSurface(SDL_Surface *surface, int x, int y, const SDL_Rect &clipRect) const;

  bool isClickWithinTile(const SDL_Point &screenCoordinates, int isoX, int isoY) const;

};

#include "Map.inl.hxx"

#endif
