#ifndef GLOBAL_MODEL_HXX_
#define GLOBAL_MODEL_HXX_

#include "util/Meta.hxx"

#include "model/MousePosition.hxx"
#include "model/MapEditor.hxx"

using AllModels = TypeList<
  MousePosition,
  MapEditor
  /* Add your global Models here */
  >;

using GlobalModel = TupleType<AllModels>::type;

#endif // GLOBAL_MODEL_HXX_
