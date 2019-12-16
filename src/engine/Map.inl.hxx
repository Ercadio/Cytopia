

template <typename Iterator> void Map::setTileIDOfNode(Iterator begin, Iterator end, const std::string &tileID)
{
  static_assert(std::is_same_v<Point, typename std::iterator_traits<Iterator>::value_type>,
      "Iterator value must be a const Point");
  for (Iterator it = begin; it != end; ++it)
  {
    if (!checkTileIDIsEmpty(*it, tileID))
    {
      while (begin != end)
      {
        mapNodes[begin->x * m_columns + begin->y]->setTileID(tileID);
        updateNeighborsOfNode(*begin++);
      }
    }
  }
}
