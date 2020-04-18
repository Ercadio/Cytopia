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
  Measurement left;
  Measurement right;
  Measurement top;
  Measurement bottom;
};

class MarginConfiguration : public PositionHint { };
class PaddingConfiguration : public PositionHint { };

constexpr Measurement operator""_lh(unsigned long long);
constexpr Measurement operator""_lw(unsigned long long);
constexpr Measurement operator""_eh(unsigned long long);
constexpr Measurement operator""_ew(unsigned long long);
constexpr Measurement operator""_px(unsigned long long);

constexpr Measurement operator+(const Measurement &, const Measurement &);
constexpr Measurement operator-(const Measurement &, const Measurement &);

#include "BoxSizing.inl.hxx"

struct AbsolutePosition
{
  Measurement left;
  Measurement top;
  static constexpr AbsolutePosition Origin() { return {0_px, 0_px}; }
  static constexpr AbsolutePosition Center() { return {50_lw - 50_ew, 50_lh - 50_eh}; }
};


#endif // BOX_SIZING_HXX
