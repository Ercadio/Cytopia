#ifndef GLOBAL_MODEL_HXX_
#define GLOBAL_MODEL_HXX_

#include "util/Meta.hxx"

#include "model/MouseState.hxx"
#include "model/MapEditor.hxx"
#include "model/Settings.hxx"

using AllModels = TypeList<
  MouseState,
  MapEditor,
  Settings
  /* Add your global Models here */
  >;

using GlobalModel = TupleType<AllModels>::type;

#endif // GLOBAL_MODEL_HXX_
