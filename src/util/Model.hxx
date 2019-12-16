#ifndef MODEL_HXX_
#define MODEL_HXX_

#include "Observer.hxx"

template <typename DataRepresentation>
struct ChangeNotification
{
  DataRepresentation before;
  DataRepresentation after;
};

template <typename DataRepresentation> class Model : public Subject<ChangeNotification<DataRepresentation>>
{
public:
  using ChangeNotification = ChangeNotification<DataRepresentation>;
};

#endif // MODEL_HXX_
