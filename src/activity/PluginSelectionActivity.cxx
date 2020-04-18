#include "PluginSelectionActivity.hxx"
#include "../view/TextButton.hxx"
#include "../view/IconButton.hxx"
#include "../view/ImageView.hxx"
#include "../view/BoxSizing.hxx"
#include "../view/Window.hxx"
#include "../controller/ButtonHandler.hxx"
#include "../util/LOG.hxx"
#include "../util/Exception.hxx"
#include "../util/ZipRange.hxx"
#include "../services/MouseController.hxx"

PluginSelectionActivity::PluginSelectionActivity(GameService::ServiceTuple & context, Window & w) : 
  iActivity(context, w),
  AbsoluteLayout(w.getBounds())
{
  /* Create background */
  {
    ImageViewPtr img = std::make_shared<ImageView>("/resources/images/ui/general/background", DisplayMode::RepeatXY);
    addElement(img,
        BoxSizing{100_lw, 100_lw},
        AbsolutePosition::Origin());
  }
  /* Create all text buttons */
  {
    auto texts = std::array{"Back"};
    auto topPositions = std::array{70_lh};
    auto callbacks = std::array{
      std::bind(&PluginSelectionActivity::onBack, this), 
    };
    for(auto [text, tp, cb] : ZipRange{texts, topPositions, callbacks})
    {
      TextButtonPtr button = std::make_shared<TextButton>(text);
      ButtonState & state = createState<ButtonState>();
      addElement(
          button, 
          BoxSizing{30_lw, 10_lh}, 
          AbsolutePosition{tp, 35_lw});
      createController<ButtonHandler>(getWindow().getGlobalModel(), cb, state, *button);
      state.addObserver(button);
    }
  }
}
void PluginSelectionActivity::onBack() { activitySwitch(ActivityType::MainMenu); }

PluginSelectionActivity::~PluginSelectionActivity() = default;

void PluginSelectionActivity::setup() noexcept
{
  iLayout::setup();
}

void PluginSelectionActivity::bindHandlers(class GameService & context) noexcept
{
  iLayout::bindHandlers(context);
}
