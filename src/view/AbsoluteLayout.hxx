#ifndef ABSOLUTE_LAYOUT_HXX
#define ABSOLUTE_LAYOUT_HXX

#include "iLayout.hxx"

class AbsoluteLayout : public virtual iLayout
{
  std::vector<BoxSizing> m_Sizes;
  std::vector<AbsolutePosition> m_Positions;
protected:
  void computeBoundaries() noexcept final;
  void addElement(iWidgetPtr&&, BoxSizing&&, AbsolutePosition &&);
private:
  using iLayout::addElement;
};

#endif // ABSOLUTE_LAYOUT_HXX
