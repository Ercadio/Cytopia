#include "iLayout.hxx"
#include "../util/LOG.hxx"
#include "../util/Exception.hxx"

void iLayout::addElement(iWidgetPtr&& pw)
{
  m_Elements.emplace_back(std::move(pw));
}

void iLayout::setPadding(PaddingConfiguration && pc) noexcept
{
  std::swap(m_PaddingConfiguration, pc);
}

iLayout::ElementRange::ElementRange(iLayout & layout) :
  m_Begin(layout.m_Elements.begin()),
  m_End(layout.m_Elements.end())
{ }

iLayout::ElementRange::iterator iLayout::ElementRange::begin() { return m_Begin; }

iLayout::ElementRange::iterator iLayout::ElementRange::end() { return m_End; }

const PaddingConfiguration & iLayout::getPadding() const
{
  return m_PaddingConfiguration;
}

void iLayout::setup() noexcept
{
  computeBoundaries();
}

void iLayout::draw(iRendererPtr & renderer) const noexcept
{
  LOG(LOG_DEBUG) << "Drawing a iLayout";
  for(auto & element : m_Elements)
    element->draw(renderer);
}

iLayout::ElementRange iLayout::elements() noexcept
{
  return ElementRange{*this};
}

iLayout::~iLayout()
{
}
