#include "ButtonState.hxx"
#include "../util/LOG.hxx"
#include "../util/Exception.hxx"

ButtonState::ButtonState() = default;

ButtonState::~ButtonState() = default;

void ButtonState::setStatus(ButtonStatus status)
{
  throw UnimplementedError{TRACE_INFO "Unimplemented"};
}
