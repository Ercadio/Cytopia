#ifndef I_CONTROLLER_HXX
#define I_CONTROLLER_HXX

#include <memory>

class iController
{
public:
  iController();
  iController(iController&&);
  iController(const iController &) = delete;
  virtual ~iController() = 0;
};

using iControllerPtr = std::unique_ptr<iController>;

#endif // I_CONTROLLER_HXX
