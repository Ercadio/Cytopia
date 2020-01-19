#include "AbsoluteLayout.hxx"
#include "../util/ZipRange.hxx"
#include "../util/LOG.hxx"

void AbsoluteLayout::addElement(iWidgetPtr&& pWid, BoxSizing&& bs, AbsolutePosition&& ap)
{
  addElement(std::move(pWid));
  m_Sizes.emplace_back(bs);
  m_Positions.emplace_back(ap);
}

void AbsoluteLayout::computeBoundaries() noexcept
{
  LOG(LOG_DEBUG) << "Computing boundaries";
  MeasurementValuation mv { 0, 0, m_Bounds.width(), m_Bounds.height() };
  for(auto [size, position, element] : 
        ZipRange{m_Sizes, m_Positions, elements()})
  {
    mv.elementWidth = size.width.measure(mv);
    mv.elementHeight = size.height.measure(mv);
    auto left = position.left.measure(mv);
    auto top = position.top.measure(mv);
    element->m_Bounds = 
      Rectangle { 
        left, top, 
        left + mv.elementWidth,
        top + mv.elementHeight
      };
    LOG(LOG_DEBUG) << "Configured an element to " << element->m_Bounds;
  }
}
