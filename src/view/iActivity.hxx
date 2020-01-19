#ifndef I_ACTIVITY_HXX
#define I_ACTIVITY_HXX

#include <memory>
#include <betterEnums.hxx>
#include "iLayout.hxx"
#include "iWidget.hxx"
#include "../GameService.hxx"

BETTER_ENUM(ActivityType, uint8_t, MainMenu, NewGame, LoadGame);

class iActivity : public virtual iLayout, public GameService
{
  class Window & m_Window;
public:
 
  iActivity(GameService::ServiceTuple &, class Window &);
  virtual ~iActivity() = 0;
  
protected:

  /**
   * @brief Switches to another iActivity
   * @param ActivityType the type of iActivity to switch to
   */
  void activitySwitch(ActivityType);
  
  virtual Rectangle getBounds() const noexcept final;

};

using iActivityPtr = std::unique_ptr<iActivity>;

#endif // I_ACTIVITY_HXX
