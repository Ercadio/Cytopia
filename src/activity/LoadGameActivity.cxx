#include "LoadGameActivity.hxx"
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

LoadGameActivity::LoadGameActivity(GameService::ServiceTuple & context, Window & w) : 
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
      std::bind(&LoadGameActivity::onBack, this), 
    };
    for(auto [text, tp, cb] : ZipRange{texts, topPositions, callbacks})
    {
      TextButtonPtr button = std::make_shared<TextButton>(text);
      ButtonState & state = createState<ButtonState>();
      addElement(
          button, 
          BoxSizing{30_lw, 10_lh}, 
          AbsolutePosition{tp, 35_lw});
      createController<ButtonHandler>(cb, state, *button);
      state.addObserver(button);
    }
  }
}
void LoadGameActivity::onBack() { activitySwitch(ActivityType::MainMenu); }

LoadGameActivity::~LoadGameActivity() = default;

void LoadGameActivity::setup() noexcept
{
  computeBoundaries();
  bindHandlers();
}
