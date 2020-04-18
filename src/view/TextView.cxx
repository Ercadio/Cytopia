#include "TextView.hxx"

TextView::TextView(const char * text, RGBAColor color) :
  m_Text(text), m_Color(color)
{
}

TextView::~TextView() = default;

void TextView::draw(iRenderer & renderer) const noexcept
{
  renderer.drawText(m_Text, m_Color, getBounds(), PositionType::Centered);
}

void TextView::setup() noexcept { }
void TextView::bindHandlers(class GameService & context) noexcept { };
