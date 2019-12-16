#include "EventManager.hxx"

#include "basics/Camera.hxx"
#include "basics/isoMath.hxx"
#include "basics/mapEdit.hxx"
#include "basics/Settings.hxx"
#include "common/enums.hxx"
#include "map/MapLayers.hxx"
#include "Map.hxx"
#include "Sprite.hxx"
#include "../model/MousePosition.hxx"

#include "LOG.hxx"

#ifdef MICROPROFILE_ENABLED
#include "microprofile.h"
#endif

EventManager::EventManager(GameService::ServiceTuple &context, GlobalModel &globalModel) : GameService(context), m_GlobalModel(globalModel) { }

void EventManager::checkEvents(SDL_Event &event, Engine &engine)
{

#ifdef MICROPROFILE_ENABLED
  MICROPROFILE_SCOPEI("EventManager", "checkEvents", MP_BEIGE);
#endif

  // check for UI events first
  SDL_Point mouseCoords;
  Point clickCoords{};
  uint8_t byte;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      engine.quitGame();
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        // TODO: Toggle last opened menu or settings menu if nothing is open
        GetService<UIManager>().toggleGroupVisibility("PauseMenu");
        break;

      case SDLK_0:
        break;
      case SDLK_F11:
        GetService<UIManager>().toggleDebugMenu();
        break;
      case SDLK_1:
        MapLayers::toggleLayer(Layer::TERRAIN);
        break;
      case SDLK_2:
        MapLayers::toggleLayer(Layer::BUILDINGS);
        break;
      case SDLK_3:
        break;
      case SDLK_i:
        m_tileInfoMode = !m_tileInfoMode;
        break;
      case SDLK_f:
        engine.toggleFullScreen();
        break;
      case SDLK_w:
        if (Camera::cameraOffset.y > -2 * Settings::instance().screenHeight * Camera::zoomLevel)
        {
          Camera::cameraOffset.y -= (Settings::instance().screenHeight / 4);
          if (Engine::instance().map != nullptr)
          {
            Engine::instance().map->refresh();
          }
        }
        break;
      case SDLK_a:
        if (Camera::cameraOffset.x > -0.25 * Settings::instance().screenWidth * Camera::zoomLevel)
        {
          Camera::cameraOffset.x -= (Settings::instance().screenWidth / 4);
          if (Engine::instance().map != nullptr)
          {
            Engine::instance().map->refresh();
          }
        }
        break;

      case SDLK_s:
        if (Camera::cameraOffset.y < 1.25 * Settings::instance().screenHeight * Camera::zoomLevel)
        {
          Camera::cameraOffset.y += (Settings::instance().screenHeight / 4);
          if (Engine::instance().map != nullptr)
          {
            Engine::instance().map->refresh();
          }
        }
        break;

      case SDLK_d:
        if (Camera::cameraOffset.x < 5 * Settings::instance().screenWidth * Camera::zoomLevel)
        {
          Camera::cameraOffset.x += (Settings::instance().screenWidth / 4);
          if (Engine::instance().map != nullptr)
          {
            Engine::instance().map->refresh();
          }
        }
        break;

      default:
        break;
      }
      break;

    case SDL_MULTIGESTURE:
      if (event.mgesture.numFingers == 2)
      {
        m_panning = true;
        // check if we're pinching
        if (event.mgesture.dDist != 0)
        {
          // store pinchCenterCoords so they stay the same for all zoom levels
          if (pinchCenterCoords.x == 0 && pinchCenterCoords.y == 0)
          {
            pinchCenterCoords =
                convertScreenToIsoCoordinates({static_cast<int>(event.mgesture.x * Settings::instance().screenWidth),
                                               static_cast<int>(event.mgesture.y * Settings::instance().screenHeight)});
          }
          Camera::setPinchDistance(event.mgesture.dDist * 15.0F, pinchCenterCoords.x, pinchCenterCoords.y);
          m_skipLeftClick = true;
          break;
        }

        if (m_panning)
        {
          Camera::cameraOffset.x -= static_cast<int>(Settings::instance().screenWidth * event.tfinger.dx);
          Camera::cameraOffset.y -= static_cast<int>(Settings::instance().screenHeight * event.tfinger.dy);
          Camera::centerIsoCoordinates =
              convertScreenToIsoCoordinates({Settings::instance().screenWidth / 2, Settings::instance().screenHeight / 2});
          Engine::instance().map->refresh();
          m_skipLeftClick = true;
          break;
        }
      }
      m_skipLeftClick = true;
      break;
    case SDL_MOUSEMOTION:
      GetService<GameLoopMQ>().push(
        MousePositionEvent{ event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel }
      );
      break;
    case SDL_MOUSEBUTTONDOWN: [[fallthrough]];
    case SDL_MOUSEBUTTONUP:
      switch(event.button.button)
      {
        case SDL_BUTTON_LEFT:
          byte = ClickEvent::Left;
          break;
        case SDL_BUTTON_RIGHT:
          byte = ClickEvent::Right;
          break;
        case SDL_BUTTON_MIDDLE:
          byte = ClickEvent::Middle;
          break;
        default: continue; // We skip SDL_TOUCH_MOUSEID
      }
      byte |= (event.button.type == SDL_MOUSEBUTTONDOWN) ? ClickEvent::Pressed : ClickEvent::Released;
      GetService<GameLoopMQ>().push(
        ClickEvent{ event.button.x, event.button.y, static_cast<ClickEvent::State>(byte) }
      );
      break;
    case SDL_MOUSEWHEEL:
      GetService<GameLoopMQ>().push(
        ScrollEvent{ event.wheel.x, event.wheel.y }
      );
      break;
    default:
      break;
    }
  }
}
