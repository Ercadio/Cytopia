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
  m_UILoop(&LoopMain<UILoopMQ, UIVisitor>, std::ref(m_GameContext), UIVisitor{}),
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
      default:
        LOG(LOG_WARNING) << "Uncaught SDL Event happened with id " << event.type;
        break;
    }
  }
}


Game::~Game()
{
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
      LOG(LOG_DEBUG) << "Waiting for an event";
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
