#include "MainMenuActivity.hxx"
#include "TextButton.hxx"
#include "IconButton.hxx"
#include "ImageView.hxx"
#include "BoxSizing.hxx"
#include "Window.hxx"
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
    ImageViewPtr img = std::make_unique<ImageView>("/resources/images/ui/general/background", DisplayMode::RepeatXY);
    addElement(std::move(img),
        BoxSizing{100_lw, 100_lw},
        AbsolutePosition::Origin());
  }
  /* Create logo */
  {
    ImageViewPtr logo = std::make_unique<ImageView>("/resources/images/app_icons/logo_big_textured", DisplayMode::NearestXY);
    addElement(std::move(logo),
        BoxSizing{220_px, 50_px},
        AbsolutePosition{25_lh - 50_px, 50_lw - 50_ew});
  }
  /* Create all text buttons */
  {
    auto texts = std::array{"New Game", "Load Game", "Exit"};
    auto topPositions = std::array{40_lh, 55_lh, 70_lh};
    auto callbacks = std::array{
      &MainMenuActivity::testing,
      &MainMenuActivity::testing,
      &MainMenuActivity::testing
//      std::bind(&MainMenuActivity::onNewGame, this), 
//      std::bind(&MainMenuActivity::onLoadGame, this),
//      std::bind(&MainMenuActivity::onExit, this)
    };
    for(auto [text, tp, cb] : ZipRange{texts, topPositions, callbacks})
    {
      TextButtonPtr button = std::make_unique<TextButton>(text);
      ButtonState & state = createState<ButtonState>();
      auto & handler = createController<ButtonHandler>(cb, state, button->getBounds());
      GetService<MouseController>().addHandler(&handler);
      addElement(
          std::move(button), 
          BoxSizing{30_lw, 10_lh}, 
          AbsolutePosition{tp, 35_lw});
    }
  }
  /* Create all icons */
  {
    auto icons = std::array{"globe", "wrench"};
    auto positions = std::array{100_lw - 110_px, 100_lw - 55_px};
    for(auto [base_icon, lp] : ZipRange{icons, positions})
    {
      std::string iconPath = "resources/images/ui/buttons/";
      iconPath += base_icon;
      IconButtonPtr button = std::make_unique<IconButton>(iconPath);
      addElement(
          std::move(button), 
          BoxSizing{50_px, 50_px}, 
          AbsolutePosition{100_lh - 55_px, lp});
    }
  }
}
void MainMenuActivity::onNewGame() { }
void MainMenuActivity::onLoadGame() { }
void MainMenuActivity::onExit() { }
void MainMenuActivity::onLanguageSelection() { }
void MainMenuActivity::onPluginSelection() { }

MainMenuActivity::~MainMenuActivity() = default;

void MainMenuActivity::setup() noexcept
{
  computeBoundaries();
}

void MainMenuActivity::testing() { LOG(LOG_INFO) << "HELLO"; };
