#include "ButtonWidget.hxx"
#include "../util/LOG.hxx"

ButtonWidget::ButtonWidget(const char * text) : m_Text(text)
{
}

ButtonWidget::~ButtonWidget() { }

void ButtonWidget::draw(iRendererPtr & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "Drawing a button widget";
  renderer->drawShape(getBounds(), RGBAColor{0x8742f5FF});
}

