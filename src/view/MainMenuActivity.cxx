#include "MainMenuActivity.hxx"
#include "ButtonWidget.hxx"
#include "BoxSizing.hxx"
#include "Window.hxx"
#include "../util/LOG.hxx"
#include "../util/Exception.hxx"
#include "../util/ZipRange.hxx"

MainMenuActivity::MainMenuActivity(GameService::ServiceTuple & context, Window & w) : iActivity(context, w)
{
  /* Create all buttons */
  {
    auto texts = std::array{"New Game", "Load Game", "Exit"};
    auto topPositions = std::array{5_lh, 20_lh, 35_lh};
    for(auto [text, tp] : ZipRange{texts, topPositions})
    {
      ButtonWidgetPtr button = std::make_unique<ButtonWidget>(text);
      addElement(
          std::move(button), 
          BoxSizing{70_lw, 10_lh}, 
          AbsolutePosition{tp, 15_lw});
    }
  }
}

MainMenuActivity::~MainMenuActivity() { }
