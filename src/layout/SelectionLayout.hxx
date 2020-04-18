#ifndef SELECTION_LAYOUT_HXX
#define SELECTION_LAYOUT_HXX

#include <memory>
#include "iLayout.hxx"

class SelectionLayout : public iLayout
{
protected:
  void computeBoundaries() noexcept final;
private:
  Measurement m_ElementHeight;
  int m_Scroll;
public:
  using iLayout::addElement;
  SelectionLayout(Rectangle && = Rectangle{0, 0, 0, 0}, Measurement && elementHeight = 10_lh);
  void draw(iRenderer &) const noexcept override;
  ~SelectionLayout() override;
  void bindHandlers(class GameService & context) noexcept final;  
};

using SelectionLayoutPtr = std::shared_ptr<SelectionLayout>;

#endif // SELECTION_LAYOUT_HXX
