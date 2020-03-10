#ifndef LANGUAGE_SELECTION_ACTIVITY_HXX
#define LANGUAGE_SELECTION_ACTIVITY_HXX

#include <functional>

#include "../view/AbsoluteLayout.hxx"
#include "../view/iActivity.hxx"
#include "../util/LOG.hxx"

class LanguageSelectionActivity : public AbsoluteLayout, public iActivity
{
  void onBack();
public:
  LanguageSelectionActivity(GameService::ServiceTuple &, class Window &);
  virtual ~LanguageSelectionActivity() final;
  void setup() noexcept final;
};

#endif // LANGUAGE_SELECTION_ACTIVITY_HXX
