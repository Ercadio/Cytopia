#ifndef MODEL_HXX_
#define MODEL_HXX_

#include "Observer.hxx"

template <typename DataRepresentation>
struct ChangeNotification
{
  DataRepresentation before;
  DataRepresentation after;
  ChangeNotification(DataRepresentation & before, DataRepresentation & after) : before(before), after(after) { }
};

template <typename... DataRepresentations> class Model : public Subject<TypeList<ChangeNotification<DataRepresentations>...>>
{
};

#endif // MODEL_HXX_
