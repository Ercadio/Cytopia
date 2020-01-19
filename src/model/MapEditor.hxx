#ifndef MAP_EDITOR_HXX
#define MAP_EDITOR_HXX

#include <betterEnums.hxx>
#include "../util/Model.hxx"

BETTER_ENUM(TerrainEditMode, char, Raise, Lower, Level, Demolish, BuildRectangle, None);

struct MapEditorModel
{
  TerrainEditMode editMode = TerrainEditMode::None;
  std::string tileType;
  int highlightColor;
};

class MapEditor : public Model<MapEditorModel>
{
  MapEditorModel m_Model;
public:
  MapEditor();
  ~MapEditor();
  void setEditMode(TerrainEditMode);
  void setHighlightColor(int);
  void setTileType(std::string&&);
  const MapEditorModel & getModel() const;
  TerrainEditMode getEditMode() const;
};

#endif // MAP_EDITOR_HXX
