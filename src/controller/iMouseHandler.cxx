#include "iMouseHandler.hxx"
#include "../view/Shape.hxx"

iMouseHandler::~iMouseHandler() = default;

void iMouseHandler::onMouseClick(class ClickEvent &&) { }
void iMouseHandler::onMouseHover() { }
void iMouseHandler::onMouseLeave() { }
void iMouseHandler::onScroll(ScrollEvent &&) { }
