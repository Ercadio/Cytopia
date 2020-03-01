#include "MapEditor.hxx"
#include "LOG.hxx"

MapEditor::~MapEditor()
{
  LOG(LOG_DEBUG) << "Destroying MapEditor";
}

void MapEditor::setEditMode(TerrainEditMode mode) 
{ 
  MapEditorModel old = m_Model; 
  m_Model.editMode = mode; 
  notifyObservers(Notification{m_Model}); 
}

void MapEditor::setHighlightColor(int rgba) 
{ 
  MapEditorModel old = m_Model; 
  m_Model.highlightColor = rgba; 
  notifyObservers(Notification{m_Model}); 
}

void MapEditor::setTileType(std::string && tileType) 
{ 
  MapEditorModel old = m_Model; 
  m_Model.tileType = tileType; 
  notifyObservers(Notification{m_Model}); 
}

const MapEditorModel & MapEditor::getModel() const { return m_Model; }

TerrainEditMode MapEditor::getEditMode() const { return m_Model.editMode; }
