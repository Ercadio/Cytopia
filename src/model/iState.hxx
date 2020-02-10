#ifndef I_STATE_HXX_
#define I_STATE_HXX_

#include <memory>

class iState
{
public:
  virtual ~iState() = 0;
};

using iStatePtr = std::unique_ptr<iState>;

#endif // I_STATE_HXX_
