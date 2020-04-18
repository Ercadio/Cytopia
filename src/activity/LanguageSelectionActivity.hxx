#ifndef LANGUAGE_SELECTION_ACTIVITY_HXX
#define LANGUAGE_SELECTION_ACTIVITY_HXX

#include <functional>

#include "../layout/AbsoluteLayout.hxx"
#include "../activity/iActivity.hxx"
#include "../util/LOG.hxx"

class LanguageSelectionActivity : public AbsoluteLayout, public iActivity
{
  void onBack();
public:
  LanguageSelectionActivity(GameService::ServiceTuple &, class Window &);
  virtual ~LanguageSelectionActivity() final;
  void setup() noexcept final;
  void bindHandlers(class GameService & context) noexcept final;
};

#endif // LANGUAGE_SELECTION_ACTIVITY_HXX
