#include "MouseController.hxx"
#include "../util/LOG.hxx"

MouseController::MouseController(GameService::ServiceTuple & context, GlobalModel & model) :
	GameService(context), m_GlobalModel(model)
{
	LOG(LOG_DEBUG) << "Created MouseController service";
}

MouseController::~MouseController()
{
  LOG(LOG_DEBUG) << "Destroying MouseController";
}

void MouseController::handleEvent(MousePositionEvent && event)
{
}

void MouseController::handleEvent(ClickEvent && )
{
}

void MouseController::handleEvent(ScrollEvent && )
{
}
