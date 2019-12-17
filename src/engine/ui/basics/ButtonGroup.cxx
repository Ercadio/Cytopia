#include "ButtonGroup.hxx"
#include "../../services/UIManager.hxx"

ButtonGroup::ButtonGroup(UIManager & uiManager) : m_UIManager(uiManager) { }

void ButtonGroup::addToGroup(Button *widget)
{
  if (widget)
  {
    m_buttonGroup.push_back(widget);
  }
}

bool ButtonGroup::onMouseButtonDown(const SDL_Event &event)
{
  for (const auto &it : m_buttonGroup)
  {
    if (it->isVisible() && it->onMouseButtonDown(event))
    {
      return true;
    }
  }
  return false;
}

bool ButtonGroup::onMouseButtonUp(const SDL_Event &event)
{
  for (const auto &it : m_buttonGroup)
  {
    if (it->isMouseOver(event.button.x, event.button.y) && it->isVisible() && exclusive)
    {
      if (alwaysOn)
      {
        uncheckAllButtons();
      }
      else
      {
        uncheckAllButtons(it);
      }

      it->onMouseButtonUp(event);
      return true;
    }
  }

  return false;
}

void ButtonGroup::uncheckAllButtons(Button *exceptThisButton)
{
  for (const auto &it : m_buttonGroup)
  {
    // If the ButtonGroup has children, uncheck them too
    if (m_UIManager.getUiElementsOfGroup(it->getUiElementData().actionParameter) &&
        it->getUiElementData().actionID == "ToggleVisibilityOfGroup")
    {
      for (auto groupElement : *m_UIManager.getUiElementsOfGroup(it->getUiElementData().actionParameter))
      {
        Button *button = dynamic_cast<Button *>(groupElement);
        if (button)
        {
          button->setCheckState(false);
        }
      }
    }
    // skip the calling button itself if it is supplied as parameter (when alwaysOn is set)
    if (it != exceptThisButton)
    {
      it->setCheckState(false);
    }
  }
}
