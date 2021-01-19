/**
@page motion-control Motion Control
@tableofcontents

\section summary Summary
We want motion animations in Cytopia to be as smooth as modern
UI applications. In order to achieve this, we've derived multiple 
mathematical models to chose from. For each of these models, we assume
that we want to restrict motion over a range \f$[\mathrm{min}, \mathrm{max}]\f$
of values. Upon reaching or trespassing this range, the motion will simply block.
Also keep in mind that \f$x_n\f$ represents the position and
\f$\dot{x_n}\f$ represents the velocity at frame \f$n\f$.

\section lin-friction-clamp Linear Friction-Clamp model
A constant friction \f$\alpha\f$ is applied 
in the opposite direction of velocity. If \f$\dot{x_{n-1}}=0\f$, then we must enforce
that \f$\mathrm{sign}(0)=0\f$. Otherwise, we would never reach a steady-state for certain systems.
\f{align*}{
  \dot{x_n} &= \dot{x_{n-1}} - \alpha\ \mathrm{sign}\left(\dot{x_{n-1}}\right)\\
  x_n &= \mathrm{clamp}\left(x_n + \dot{x_n}, \min, \max\right)\\
\f}
A steady-state is reached when \f$\dot{x_n}=0\f$. Assuming a large enough range, It's pretty obvious that a steady-state can only
be reached if \f$\alpha\f$ divides \f$\dot{x_0}\f$. If that's the case, the steady state is reached
at \f$n_{\infty}=\left|\frac{\dot{x_0}}{\alpha}\right|\f$ with a value of \f[
x_{\infty}=x_0+\sum_{i=0}^{n_{\infty}-1} \dot{x_0}-i\alpha=x_0+n_{\infty}\dot{x_0}-\frac{\alpha(n_{\infty}-1)n_{\infty}}{2}
\f]

The following model assumes that impulses will be applied to the 
velocity of an object. 

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
  x_n &= \mathrm{clamp}\left(x_n + \dot{x_n}, \min, \max\right)\\
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
  x_n &= \mathrm{clamp}\left(x_n + \dot{x_n}, \min, \max\right)\\
\f}
*/
