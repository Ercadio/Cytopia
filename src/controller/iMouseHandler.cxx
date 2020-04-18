#include <SDL2/SDL.h>

#include "iMouseHandler.hxx"
#include "../view/Shape.hxx"
#include "../util/LOG.hxx"

iMouseHandler::~iMouseHandler() = default;

void iMouseHandler::onMouseClick(class ClickEvent &&) { }
void iMouseHandler::onMouseHover() { }
void iMouseHandler::onMouseLeave() { }
void iMouseHandler::onScroll(ScrollEvent &&) { }
