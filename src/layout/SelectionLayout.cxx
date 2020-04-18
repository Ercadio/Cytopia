#include "SelectionLayout.hxx"
#include "../util/LOG.hxx"
#include "../GameService.hxx"
#include "../renderer/Canvas.hxx"

SelectionLayout::SelectionLayout(Rectangle && rect, Measurement && elementHeight) :
  iLayout(std::move(rect)), 
  m_ElementHeight(elementHeight), 
  m_Scroll(0) 
{ 
}

void SelectionLayout::computeBoundaries() noexcept
{
  auto & bounds = getBounds();
  auto [x1, y1] = bounds.p1();
  auto width = bounds.width();
  auto height = m_ElementHeight.measure(
    MeasurementValuation { 0, 0, bounds.width(), bounds.height() });
  for(const auto & element : elements())
  {
    element->setBounds(Rectangle {
      x1, y1,
      x1 + width,
      y1 + height
    });
    y1 += height;
  }
}

SelectionLayout::~SelectionLayout() = default;

void SelectionLayout::draw(iRenderer & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "SELECTION_LAYOUT: " << getBounds();
  renderer.drawShape(getBounds(), 0x0000005F_rgba);

  /* Draw & clip all elements */
  Canvas canvas { getBounds() };
  {  
    for(auto it = elements().begin(); it != elements().end(); ++it)
    {
      auto & element = *it;
      /* TODO: Enable this to clip elements outside the bounds
      if(element->getBounds().maxY() < m_At)
      {
        continue;
      }
      */
      element->draw(canvas);
    }
    renderer.drawPicture(getBounds(), canvas.getData());
  }

  /*
  HEIGHT, THEIGHT, SSPEED
  1. Scrolling by a distance of HEIGHT - SHEIGHT with the scroller
     should scroll a distance of THEIGHT - HEIGHT on the layout
  2. Hence, the scrolling speed must be (THEIGHT - HEIGHT) / (HEIGHT - SHEIGHT) = SSPEED
  3. Hence, SHEIGHT is given by (HEIGHT * (1 + SSPEED) - THEIGHT) / SSPEED
  4. Ex: A SSPEED of 1 will give 2 * HEIGHT - THEIGHT. How is this even positive?
  5. Let the movement ratio MR = (TH - H) / (H - SH)
     an "ideal" movement ratio would be AL * MR = TH / H.
     Where AL is a correction factor  
  AL (TH - H) / (H - SH) = TH / H
  AL = TH (H - SH) / (H (TH - H))
  */
  int p1x = getBounds().p2().first - 15;
  int p1y = getBounds().p1().second;
  renderer.drawShape(Rectangle{p1x, p1y + m_Scroll, p1x + 10, p1y + m_Scroll + 50}, 0xFFFFFF5F_rgba);
}

void SelectionLayout::bindHandlers(class GameService & context) noexcept
{
  iLayout::bindHandlers(context);
}
