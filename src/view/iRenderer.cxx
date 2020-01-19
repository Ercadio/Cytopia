#include "iRenderer.hxx"
#include "../util/Exception.hxx"
#include "../util/LOG.hxx"

iRenderer::~iRenderer()
{
}

void iRenderer::setCursor(int dx, int dy)
{
  std::swap(m_dx, dx);
  std::swap(m_dy, dy);
}

std::pair<int, int> iRenderer::getCursor() const noexcept
{
  return {m_dx, m_dy};
}
