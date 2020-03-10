#ifndef LOAD_GAME_ACTIVITY_HXX
#define LOAD_GAME_ACTIVITY_HXX

#include <functional>

#include "../view/AbsoluteLayout.hxx"
#include "../view/iActivity.hxx"
#include "../util/LOG.hxx"

class LoadGameActivity : public AbsoluteLayout, public iActivity
{
  void onBack();
public:
  LoadGameActivity(GameService::ServiceTuple &, class Window &);
  virtual ~LoadGameActivity() final;
  void setup() noexcept final;
};

#endif // LOAD_GAME_ACTIVITY_HXX
