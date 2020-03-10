#ifndef NEW_GAME_ACTIVITY_HXX
#define NEW_GAME_ACTIVITY_HXX

#include <functional>

#include "../view/AbsoluteLayout.hxx"
#include "../view/iActivity.hxx"
#include "../util/LOG.hxx"

class NewGameActivity : public AbsoluteLayout, public iActivity
{
  void onBack();
public:
  NewGameActivity(GameService::ServiceTuple &, class Window &);
  virtual ~NewGameActivity() final;
  void setup() noexcept final;
};

#endif // NEW_GAME_ACTIVITY_HXX
