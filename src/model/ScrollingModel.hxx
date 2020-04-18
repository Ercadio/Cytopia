#ifndef SCROLLING_MODEL_HXX
#define SCROLLING_MODEL_HXX

#include "../model/DataModel.hxx"
#include "../util/Meta.hxx"


/**
@page motion-control Motion Control
@tableofcontents

\section summary Summary
We want motion animations in Cytopia to be as smooth as modern
UI applications. In order to achieve this, we've derived multiple 
mathematical models to chose from.

\section lin-friction-clamp Linear Friction-Clamp model
The following model assumes that impulses will be applied to the 
velocity of an object. A constant friction \f$\alpha\f$ is applied 
in the opposite direction of velocity.
\f{align*}{
  \dot{x_n} &= \dot{x_{n-1}} - \alpha\textup{sign}\left(x_{n-1}\right)\\
  x_n &= \textup{clamp}\left(x_n + \dot{x_n}, \min, \max\right)\\
\f}

\section exp-friction-clamp Exponential Friction-Clamp model
The following model makes the same assumptions than 
Linear Friction-Clamp. In fact, it is exactly the same
concept, except that instead of applying a constant
friction, it applies a proportional one.
The damping ratio \f$\alpha\f$ is a value between \f$[0, 1]\f$
typically close to 1. This model more closely ressembles
the physical reality of friction, and is 
also faster computationally.
\f{align*}{
  \dot{x_n} &= \alpha\dot{x_{n-1}}\\
  x_n &= \textup{clamp}\left(x_n + \dot{x_n}, \min, \max\right)\\
\f}

\section elastic Generalized Elastic Tracking
The following model is meant to track a value in an "elastic" way.
We are assuming a target \f$x_\infty\f$ is given at any point (it could change over time).
We are also given a function \f$\alpha: \mathbf{R}\rightarrow\mathbf{R}\f$ 
which is the "elasticity" of our motion. Elasticity is unbounded, however various
values will provide different behaviours.
+ Values between \f$(0,1)\f$ will make the tracker 
+ A value of 1 will make the tracker
\f{align*}{
  \dot{x_n} &= \alpha\left(x_\infty-\dot{x_{n-1}}\right)\\
  x_n &= \textup{clamp}\left(x_n + \dot{x_n}, \min, \max\right)\\
\f}

\section pid PID model
\f{align*}{
  x_n
\f}

*/

using ScrollingNotification = TypeList<uint32_t>;

class ScrollingState : public DataModel<ScrollingNotification>
{
  int32_t m_Max;
  int32_t m_Min;
  
public:
  static constexpr uint32_t FRICTION = 10;
};

#endif // SCROLLING_MODEL_HXX
