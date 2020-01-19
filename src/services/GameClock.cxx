#include "GameClock.hxx"
#include "../util/LOG.hxx"

GameClock::GameClock(GameService::ServiceTuple & services) : 
  GameService(services), m_lock(), m_thread{&GameClock::clockLoop, this}
{
  LOG(LOG_DEBUG) << "Created GameClock service";
}

GameClock::~GameClock()
{
  LOG(LOG_DEBUG) << "Stopping GameClock";
  createDefferedTask(0s, Callback{nullptr});
  m_thread.join();
}

void GameClock::clockLoop()
{
  for (;;)
  {
    {
      LockGuard lock(m_lock);
      auto now = std::chrono::system_clock::now().time_since_epoch().count();
      while (!m_Deffered.empty() and m_Deffered.top().waketime < now)
      {
        if (m_Deffered.top().callback == nullptr)
          return;
        LOG(LOG_DEBUG) << "Triggering a defferred task";
        m_Deffered.top().callback();
        m_Deffered.pop();
      }
      while (!m_Repeated.empty() and m_Repeated.top().waketime < now)
      {
        RepeatedTask top {m_Repeated.top()};
        m_Repeated.pop();
        LOG(LOG_DEBUG) << "Triggering a repeated task";
        top.callback();
        top.waketime += top.interval;
        m_Repeated.emplace(std::move(top));
      }
    }
    std::this_thread::sleep_for(1s);
  }
}
