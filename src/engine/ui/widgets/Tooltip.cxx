#include "Tooltip.hxx"
#include "../../services/GameClock.hxx"

Tooltip::Tooltip(GameClock & gameClock) : m_GameClock(gameClock) { setVisibility(false); }

void Tooltip::draw()
{
  if (isVisible())
  {
    drawTextFrame();
    renderTexture();
  }
}

void Tooltip::startTimer()
{
  setVisibility(false);
  m_active = true;
  m_GameClock.createDefferedTask(2s, [this](){ showTooltip(); });
}

void Tooltip::showTooltip() { setVisibility(true); }

void Tooltip::reset()
{
  if (m_active)
  {
    setVisibility(false);
    m_active = false;
  }
}
