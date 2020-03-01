#include "AbsoluteLayout.hxx"
#include "../util/ZipRange.hxx"
#include "../util/LOG.hxx"

iViewElementPtr AbsoluteLayout::addElement(iViewElementPtr pWid, BoxSizing&& bs, AbsolutePosition&& ap)
{
  m_Sizes.emplace_back(bs);
  m_Positions.emplace_back(ap);
  return addElement(pWid);
}

void AbsoluteLayout::computeBoundaries() noexcept
{
  LOG(LOG_DEBUG) << "Computing boundaries";
  const auto & bounds = getBounds();
  MeasurementValuation mv { 0, 0, bounds.width(), bounds.height() };
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
