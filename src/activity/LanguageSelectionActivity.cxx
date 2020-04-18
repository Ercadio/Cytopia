#include "LanguageSelectionActivity.hxx"
#include "../view/TextButton.hxx"
#include "../view/IconButton.hxx"
#include "../view/ImageView.hxx"
#include "../view/BoxSizing.hxx"
#include "../view/Window.hxx"
#include "../layout/SelectionLayout.hxx"
#include "../view/TextView.hxx"
#include "../controller/ButtonHandler.hxx"
#include "../util/LOG.hxx"
#include "../util/Exception.hxx"
#include "../util/ZipRange.hxx"
#include "../services/MouseController.hxx"

LanguageSelectionActivity::LanguageSelectionActivity(GameService::ServiceTuple & context, Window & w) : 
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
  /* Create title */
  {
    TextViewPtr text = std::make_shared<TextView>("Select a language");
    addElement(text,
        BoxSizing{50_lw, 10_lh},
        AbsolutePosition{50_lw - 50_ew, 5_lh});
  }
  /* Create all text buttons */
  {
    auto texts = std::array{"Back"};
    auto topPositions = std::array{87_lh};
    auto callbacks = std::array{
      std::bind(&LanguageSelectionActivity::onBack, this), 
    };
    for(auto [text, tp, cb] : ZipRange{texts, topPositions, callbacks})
    {
      TextButtonPtr button = std::make_shared<TextButton>(text);
      ButtonState & state = createState<ButtonState>();
      addElement(
          button, 
          BoxSizing{30_lw, 10_lh}, 
          AbsolutePosition{50_lw - 50_ew, tp});
      createController<ButtonHandler>(getWindow().getGlobalModel(), cb, state, *button);
      state.addObserver(button);
    }
  }
  /* Create Scrolling layout with language elements */
  {
    SelectionLayoutPtr layout = std::make_shared<SelectionLayout>();
    for(LanguageType lang : LanguageType::_values())
    {
      TextViewPtr textView = std::make_shared<TextView>(lang._to_string());
      layout->addElement(textView);
    }
    addElement(layout, 
        BoxSizing{70_lw, 70_lh},
        AbsolutePosition{15_lw, 15_lh});
  }
}
void LanguageSelectionActivity::onBack() { activitySwitch(ActivityType::MainMenu); }

LanguageSelectionActivity::~LanguageSelectionActivity() = default;

void LanguageSelectionActivity::setup() noexcept
{
  iLayout::setup();
}
  
void LanguageSelectionActivity::bindHandlers(class GameService & context) noexcept
{
  iLayout::bindHandlers(context);
}
