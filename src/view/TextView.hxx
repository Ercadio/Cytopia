#ifndef TEXT_VIEW_HXX
#define TEXT_VIEW_HXX
#include "../view/iViewElement.hxx"

class TextView : public iViewElement
{
  const char * m_Text;
  RGBAColor m_Color;
public:
  TextView(const char *, RGBAColor = Palette::White);
  virtual void draw(iRenderer &) const noexcept override;
  virtual ~TextView() override;
  void setup() noexcept final;
  void bindHandlers(class GameService & context) noexcept final;
};

using TextViewPtr = std::shared_ptr<TextView>;

#endif // TEXT_VIEW_HXX
