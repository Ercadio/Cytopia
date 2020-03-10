#include <noise.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.hxx"
#include "LOG.hxx"
#include "view/MainMenuActivity.hxx"
#ifdef USE_ANGELSCRIPT
#include "Scripting/ScriptEngine.hxx"
#endif
#ifdef MICROPROFILE_ENABLED
#include "microprofile.h"
#endif

template void Game::LoopMain<GameLoopMQ, Game::GameVisitor>(Game::GameContext &, Game::GameVisitor);
template void Game::LoopMain<UILoopMQ, Game::UIVisitor>(Game::GameContext &, Game::UIVisitor);

Game::Game() :
  Window(VERSION, 640, 480, false, "resources/images/app_icons/cytopia_icon.png"),
  m_GlobalModel(MousePosition{m_UILoopMQ}, MapEditor{m_UILoopMQ}, Settings{m_UILoopMQ}),
  m_GameContext(
      &m_UILoopMQ, 
      &m_GameLoopMQ, 
#ifdef USE_AUDIO
      &m_AudioMixer, 
#endif // USE_AUDIO
      &m_Randomizer, 
      &m_GameClock, 
      &m_ResourceManager, 
      &m_MouseController,
      &m_LanguageManager),
  m_GameClock{m_GameContext}, 
  m_Randomizer{m_GameContext}, 
  m_ResourceManager{m_GameContext, m_GlobalModel},
#ifdef USE_AUDIO
  m_AudioMixer{m_GameContext, m_GlobalModel},
#endif // USE_AUDIO
  m_MouseController{m_GameContext, m_GlobalModel},
  m_LanguageManager{m_GameContext, m_GlobalModel},
  m_UILoop(&LoopMain<UILoopMQ, UIVisitor>, std::ref(m_GameContext), UIVisitor{*this}),
  m_EventLoop(&LoopMain<GameLoopMQ, GameVisitor>, std::ref(m_GameContext), GameVisitor{m_GameContext})
{

  LOG(LOG_DEBUG) << "Created Game Object";
  setActivity(std::make_unique<MainMenuActivity>(m_GameContext, *this));
  SDL_Event event;
  while(SDL_WaitEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        return;
      case SDL_MOUSEMOTION:
        m_GameLoopMQ.push(MousePositionEvent{event});
        break;
      case SDL_MOUSEBUTTONUP: [[fallthrough]];
      case SDL_MOUSEBUTTONDOWN:
        m_GameLoopMQ.push(ClickEvent{event});
        break;
      case SDL_MOUSEWHEEL:
        m_GameLoopMQ.push(ScrollEvent{event});
        break;
      case SDL_WINDOWEVENT:
        switch(event.window.event)
        {
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            m_UILoopMQ.push(WindowResizeEvent{});
            break;
          case SDL_WINDOWEVENT_EXPOSED:
            m_UILoopMQ.push(WindowRedrawEvent{});
            break;
          default:
            break;
        }
        break;
      default:
        LOG(LOG_WARNING) << "Uncaught SDL Event happened with id " << event.type;
        break;
    }
  }
}


Game::~Game()
{
  const char * error = SDL_GetError();
  if(*error)
    LOG(LOG_ERROR) << "SDL Error: " << error;
  LOG(LOG_DEBUG) << "Destroying Game Object";
  m_UILoopMQ.push(TerminateEvent{});
  m_GameLoopMQ.push(TerminateEvent{});
  m_UILoop.join();
  m_EventLoop.join();
}

template <typename MQType, typename Visitor> void Game::LoopMain(GameContext &context, Visitor visitor)
{
  LOG(LOG_DEBUG) << "Launching a loop";
  try
  {
    while (true)
    {
      for (auto event : std::get<MQType *>(context)->getEnumerable())
      {
        if (std::holds_alternative<TerminateEvent>(event))
        {
          return;
        }
        else
        {
          std::visit(visitor, std::move(event));
        }
      }
    }
  }
  catch (std::exception &ex)
  {
    LOG(LOG_ERROR) << ex.what();
    // @todo: Call shutdown() here in a safe way
  }
}

Game::UIVisitor::UIVisitor(Window & window) :
  m_Window(window)
{
}

void Game::GameVisitor::operator()(TerminateEvent &&event) { }

void Game::UIVisitor::operator()(TerminateEvent &&event) { }

void Game::GameVisitor::operator()(ActivitySwitchEvent &&event)
{
  LOG(LOG_WARNING) << TRACE_INFO "Unimplemented method";
}

void Game::UIVisitor::operator()(ActivitySwitchEvent &&event)
{
  LOG(LOG_WARNING) << TRACE_INFO "Unimplemented method";
}

void Game::UIVisitor::operator()(WindowResizeEvent &&event)
{ 
  m_Window.handleEvent(std::move(event));
}

void Game::UIVisitor::operator()(WindowRedrawEvent &&event)
{ 
  m_Window.handleEvent(std::move(event));
}

void Game::UIVisitor::operator()(UIChangeEvent && change)
{ 
  change.apply();
  m_Window.handleEvent(WindowRedrawEvent{});
}
