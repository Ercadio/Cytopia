#ifndef I_ACTIVITY_HXX
#define I_ACTIVITY_HXX

#include <memory>
#include <betterEnums.hxx>

#include "iLayout.hxx"
#include "iViewElement.hxx"
#include "../GameService.hxx"
#include "../controller/iController.hxx"
#include "../controller/iMouseHandler.hxx"
#include "../model/iState.hxx"

BETTER_ENUM(ActivityType, uint8_t, MainMenu, NewGame, LoadGame);

class iActivity : public GameService, public virtual iView
{
  class Window & m_Window;
  std::vector<iControllerPtr> m_Controllers;
  std::vector<iStatePtr> m_States;
  friend class Window;

public:
 
  iActivity(GameService::ServiceTuple &, class Window &);
  virtual ~iActivity() = 0;
  virtual void setup() noexcept = 0;

protected:

  /**
   * @brief Switches to another iActivity
   * @param ActivityType the type of iActivity to switch to
   */
  void activitySwitch(ActivityType);
  
  template <typename ControllerType, typename... Args>
  ControllerType & createController(Args &&... args);
  
  template <typename StateType, typename... Args>
  StateType & createState(Args &&... args);

};

using iActivityPtr = std::unique_ptr<iActivity>;

#include "iActivity.inl.hxx"

#endif // I_ACTIVITY_HXX
