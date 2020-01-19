#include "iView.hxx"

iView::iView() : m_Bounds(0, 0, 0, 0) { }

const Rectangle & iView::getBounds() const noexcept { return m_Bounds; }
