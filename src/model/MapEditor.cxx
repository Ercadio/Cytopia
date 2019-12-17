#include "MapEditor.hxx"

MapEditor::MapEditor() = default;

void MapEditor::setEditMode(TerrainEditMode mode) 
{ 
  MapEditorModel old = m_Model; 
  m_Model.editMode = mode; 
  notifyObservers(Notification{old, m_Model}); 
}

void MapEditor::setHighlightColor(int rgba) 
{ 
  MapEditorModel old = m_Model; 
  m_Model.highlightColor = rgba; 
  notifyObservers(Notification{old, m_Model}); 
}

void MapEditor::setTileType(std::string && tileType) 
{ 
  MapEditorModel old = m_Model; 
  m_Model.tileType = tileType; 
  notifyObservers(Notification{old, m_Model}); 
}

const MapEditorModel & MapEditor::getModel() const { return m_Model; }
