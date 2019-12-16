#ifndef EVENTMANAGER_HXX_
#define EVENTMANAGER_HXX_

#include <SDL.h>
#include <set>

#include "Engine.hxx"
#include "UIManager.hxx"
#include "../GameService.hxx"
#include "../GlobalModel.hxx"

/**
 * @todo This class should eventually be removed. All the code handling events should be inside of Game::run
 *       and the logic should be replaced by dispatching events that are handled by controllers
 */
class EventManager : public GameService
{
public:

  EventManager(GameService::ServiceTuple &, GlobalModel &);

  void checkEvents(SDL_Event &event, Engine &engine);

private:
  UIElement *m_lastHoveredElement = nullptr;

  bool m_panning = false;
  bool m_skipLeftClick = false;
  bool m_tileInfoMode = false;
  Point pinchCenterCoords = {0, 0, 0, 0};
  Point m_clickDownCoords = {0, 0, 0, 0};
  Point m_highlitNode = {0, 0, 0, 0};
  std::vector<Point> m_highlightedNodes = {};
  GlobalModel & m_GlobalModel;
};

#endif
