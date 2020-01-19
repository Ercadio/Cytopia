#ifndef MOUSE_CONTROLLER_HXX
#define MOUSE_CONTROLLER_HXX

#include <vector>

#include "../GameService.hxx"
#include "../events/MouseEvents.hxx"
#include "../GlobalModel.hxx"
#include "../util/Point.hxx"

class MouseController : public GameService
{

  void handleEvent(MousePositionEvent && );
  
  void handleEvent(ClickEvent && );
  
  void handleEvent(ScrollEvent && );
 
  friend class Game; 

  class UIElement *m_lastHoveredElement = nullptr;

  GlobalModel & m_GlobalModel;

  Point m_HighlightedNode = {0, 0, 0, 0};
  std::vector<Point> m_HighlightedNodes;
  Point m_clickDownCoords = {0, 0, 0, 0};

public:

  MouseController(GameService::ServiceTuple &, GlobalModel &);
  ~MouseController();
  
};

#endif // MOUSE_CONTROLLER_HXX
