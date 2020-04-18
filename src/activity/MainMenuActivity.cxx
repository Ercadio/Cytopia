#include "MainMenuActivity.hxx"
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

MainMenuActivity::MainMenuActivity(GameService::ServiceTuple & context, Window & w) : 
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
  /* Create logo */
  {
    ImageViewPtr logo = std::make_shared<ImageView>("/resources/images/app_icons/logo_big_textured", DisplayMode::NearestXY);
    addElement(logo,
        BoxSizing{220_px, 50_px},
        AbsolutePosition{50_lw - 50_ew, 25_lh - 50_px});
  }
  /* Create all text buttons */
  {
    auto texts = std::array{"New Game", "Load Game", "Exit"};
    auto topPositions = std::array{40_lh, 55_lh, 70_lh};
    auto callbacks = std::array{
      std::bind(&MainMenuActivity::onNewGame, this), 
      std::bind(&MainMenuActivity::onLoadGame, this),
      std::bind(&MainMenuActivity::onExit, this)
    };
    for(auto [text, tp, cb] : ZipRange{texts, topPositions, callbacks})
    {
      TextButtonPtr button = std::make_shared<TextButton>(text);
      ButtonState & state = createState<ButtonState>();
      addElement(
          button, 
          BoxSizing{30_lw, 10_lh}, 
          AbsolutePosition{35_lw, tp});
      createController<ButtonHandler>(getWindow().getGlobalModel(), cb, state, *button);
      state.addObserver(button);
    }
  }
  /* Create all icons */
  {
    auto callbacks = std::array{
      std::bind(&MainMenuActivity::onLanguageSelection, this), 
      std::bind(&MainMenuActivity::onPluginSelection, this)
    };
    auto icons = std::array{"globe", "wrench"};
    auto positions = std::array{100_lw - 110_px, 100_lw - 55_px};
    for(auto [base_icon, lp, cb] : ZipRange{icons, positions, callbacks})
    {
      std::string iconPath = "resources/images/ui/buttons/";
      iconPath += base_icon;
      IconButtonPtr button = std::make_shared<IconButton>(iconPath);
      ButtonState & state = createState<ButtonState>();
      addElement(
          button, 
          BoxSizing{50_px, 50_px}, 
          AbsolutePosition{lp, 100_lh - 55_px});
      createController<ButtonHandler>(getWindow().getGlobalModel(), cb, state, *button);
      state.addObserver(button);
    }
  }
}
void MainMenuActivity::onNewGame() { activitySwitch(ActivityType::NewGame); }
void MainMenuActivity::onLoadGame() { activitySwitch(ActivityType::LoadGame); }
void MainMenuActivity::onExit() { }
void MainMenuActivity::onLanguageSelection() { activitySwitch(ActivityType::LanguageSelection); }
void MainMenuActivity::onPluginSelection() { activitySwitch(ActivityType::PluginSelection); }

MainMenuActivity::~MainMenuActivity() = default;

void MainMenuActivity::setup() noexcept
{
  iLayout::setup();
}

void MainMenuActivity::bindHandlers(class GameService & context) noexcept
{
  iLayout::bindHandlers(context);
}
