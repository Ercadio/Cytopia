#include "iLayout.hxx"
#include "../util/LOG.hxx"
#include "../util/Exception.hxx"

iViewElementPtr iLayout::addElement(iViewElementPtr pw)
{
  m_Elements.emplace_back(pw);
  return m_Elements.back();
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

iLayout::iLayout(Rectangle && r) : m_Bounds(r)
{
}

iLayout::~iLayout()
{
}

const Rectangle & iLayout::getBounds() const noexcept
{
  return m_Bounds;
}

void iLayout::setBounds(Rectangle && r) noexcept 
{
  std::swap(r, m_Bounds);
}
