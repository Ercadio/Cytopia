#ifndef PLUGIN_SELECTION_ACTIVITY_HXX
#define PLUGIN_SELECTION_ACTIVITY_HXX

#include <functional>

#include "../layout/AbsoluteLayout.hxx"
#include "../activity/iActivity.hxx"
#include "../util/LOG.hxx"

class PluginSelectionActivity : public AbsoluteLayout, public iActivity
{
  void onBack();
public:
  PluginSelectionActivity(GameService::ServiceTuple &, class Window &);
  virtual ~PluginSelectionActivity() final;
  void setup() noexcept final;
  void bindHandlers(class GameService & context) noexcept final;
};

#endif // PLUGIN_SELECTION_ACTIVITY_HXX
