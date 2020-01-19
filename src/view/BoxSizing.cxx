#include "BoxSizing.hxx"

int Measurement::measure(const MeasurementValuation & mv)
{
  return 
    px 
    + (ew * mv.elementWidth) / 100
    + (eh * mv.elementHeight) / 100
    + (lw * mv.layoutWidth) / 100
    + (lh * mv.layoutHeight) / 100;
}
