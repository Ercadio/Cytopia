#ifndef GAME_HXX_
#define GAME_HXX_

#ifndef VERSION
#define VERSION 0
#endif

#include "view/Window.hxx"
#include "Scripting/ScriptEngine.hxx"
#include "util/Meta.hxx"
#include "GameService.hxx"
#include "GlobalModel.hxx"
#ifdef USE_AUDIO
#include "services/AudioMixer.hxx"
#endif
#include "services/Randomizer.hxx"
#include "services/GameClock.hxx"
#include "services/ResourceManager.hxx"
#include "services/MouseController.hxx"
#include "services/LanguageManager.hxx"
#include "LOG.hxx"
#include "Exception.hxx"
#include "engine/MessageQueue.hxx"
#include "Events.hxx"

#include <thread>

using Thread = std::thread;

class Game : public Window
{

public:

  /**
   * @brief Creates a game
   * @details Initializes all GameServices and starts the threads
   */
  Game();

  /**
   * @brief Destroy a game
   */
  ~Game();

private:

  /* Global Model */
  GlobalModel m_GlobalModel;
	
  /* Services */
  GameClock m_GameClock;
  Randomizer m_Randomizer;
  ResourceManager m_ResourceManager;
#ifdef USE_AUDIO
  AudioMixer m_AudioMixer;
#endif
  MouseController m_MouseController;
  LanguageManager m_LanguageManager;
  UILoopMQ m_UILoopMQ;
  GameLoopMQ m_GameLoopMQ;

  /* Game context */
  using GameContext = GameService::ServiceTuple;
  GameContext m_GameContext;

  /* Threads */
  Thread m_UILoop;
  Thread m_EventLoop;

  template <typename MQType, typename Visitor> static void LoopMain(GameContext &context, Visitor visitor);

  struct UIVisitor
  {
    UIVisitor(Window &);
    void operator()(TerminateEvent &&event);

    void operator()(ActivitySwitchEvent &&);

    void operator()(WindowResizeEvent &&);
  private:
    Window & m_Window;
  };

  struct GameVisitor : public GameService
  {

#ifdef USE_AUDIO
    /**
     * @brief handles valid AudioEvents
     * @tparam AudioEventType the AudioEvent
     */
    template <typename AudioEventType>
    EnableIf<ContainsType<AudioEvents, AudioEventType>, void>
    operator()(AudioEventType &&event);
#endif // USE_AUDIO
    
    /**
     * @brief handles valid MouseEvents
     * @tparam MouseEventType the MouseEvent
     */
    template <typename MouseEventType>
    EnableIf<ContainsType<MouseEvents, MouseEventType>, void>
    operator()(MouseEventType &&event);
    
    void operator()(TerminateEvent &&event);

    void operator()(ActivitySwitchEvent &&);

  };
};

#include "Game.inl.hxx"

#endif
