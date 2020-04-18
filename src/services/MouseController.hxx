#ifndef MOUSE_CONTROLLER_HXX
#define MOUSE_CONTROLLER_HXX

#include <vector>
#include <unordered_map>

#include "../GameService.hxx"
#include "../events/MouseEvents.hxx"
#include "../events/UIEvents.hxx"
#include "../GlobalModel.hxx"
#include "../util/Point.hxx"
#include "../controller/iMouseHandler.hxx"

class MouseController : public GameService
{
public:
  MouseController(GameService::ServiceTuple &, GlobalModel &);
  ~MouseController();
  void addHandler(iMouseHandler *);
private:
  void handleEvent(MousePositionEvent && );
  void handleEvent(ClickEvent && );  
  void handleEvent(ScrollEvent && );
  void handleEvent(ActivitySwitchEvent && );
  
  friend class Game; 

  GlobalModel & m_GlobalModel;

  using HandlerList = std::vector<iMouseHandler *>;
  std::unordered_map<SpatialBlock, HandlerList> m_SpatialMap;
  iMouseHandler * m_LastHovered;

};

#endif // MOUSE_CONTROLLER_HXX
