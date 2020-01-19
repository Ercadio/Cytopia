#ifndef BOX_SIZING_HXX
#define BOX_SIZING_HXX

#include "../util/Meta.hxx"

struct Measurement
{
  int px;
  int ew;
  int eh;
  int lw;
  int lh;
  int measure(const class MeasurementValuation &);
};

struct MeasurementValuation
{
  int elementWidth;
  int elementHeight;
  int layoutWidth;
  int layoutHeight;
};

struct BoxSizing
{
  Measurement width;
  Measurement height;
};

struct PositionHint
{
  Measurement top;
  Measurement right;
  Measurement bottom;
  Measurement left;
};

class MarginConfiguration : public PositionHint { };
class PaddingConfiguration : public PositionHint { };

struct AbsolutePosition
{
  Measurement top;
  Measurement left;
};

constexpr Measurement operator""_lh(unsigned long long);
constexpr Measurement operator""_lw(unsigned long long);
constexpr Measurement operator""_eh(unsigned long long);
constexpr Measurement operator""_ew(unsigned long long);
constexpr Measurement operator""_px(unsigned long long);

constexpr Measurement operator+(const Measurement &, const Measurement &);
constexpr Measurement operator-(const Measurement &, const Measurement &);

#include "BoxSizing.inl.hxx"

#endif // BOX_SIZING_HXX
