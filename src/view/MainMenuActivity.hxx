#ifndef MAIN_MENU_ACTIVITY_HXX
#define MAIN_MENU_ACTIVITY_HXX

#include "AbsoluteLayout.hxx"
#include "iActivity.hxx"

class MainMenuActivity : public AbsoluteLayout, public iActivity
{
  
public:
  MainMenuActivity(GameService::ServiceTuple &, class Window &);
  virtual ~MainMenuActivity() final;
};

#endif // MAIN_MENU_ACTIVITY_HXX
