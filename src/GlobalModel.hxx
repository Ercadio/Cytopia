#ifndef GLOBAL_MODEL_HXX_
#define GLOBAL_MODEL_HXX_

#include "util/Meta.hxx"

#include "model/MousePosition.hxx"
#include "model/MapEditor.hxx"
#include "model/Settings.hxx"

using AllModels = TypeList<
  MousePosition,
  MapEditor,
  Settings
  /* Add your global Models here */
  >;

/**
 * @todo No state should be kept as "global"
 *       We should remove all of these states
 *       and couple them with a Controller
 */
using GlobalModel = TupleType<AllModels>::type;

#endif // GLOBAL_MODEL_HXX_
