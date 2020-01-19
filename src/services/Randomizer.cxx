#include "Randomizer.hxx"

thread_local RNG Randomizer::generator{std::random_device{}()};

Randomizer::~Randomizer()
{
  LOG(LOG_DEBUG) << "Destroying Randomizer";
}
