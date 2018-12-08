---
layout: post
title: Solving ODEs in Unity
use_math: true
draft: true
---

One of the most common tasks in modeling and simulation is the integration of a system of ODEs.

Unity has a built-in runtime loop with some level of flexibility, with two different options for iterated methods (Update every screem, FixedUpdate at attempted regular time intervals). While a fully threaded approach to separating out computation from GUI is ideal (there will be a later blog post about this), when introducing students to modeling in Unity I typically start simple, with an Euler's method solution to a simple problem iterated in the Update routine.

Quickly, however, most student projects will reach a point where Euler's method, though simple to implement, is not usable for any project of interest.

The Integrator object presented in this blog provides an abstract object that can be extended to include a method calculating rates of change, and has built in methods for stepping those rates of change forward with a range of numerical integration algorithms. (As of this writing it includes only Runge Kutta 4th order and Adams-Baskforth-Moulton Predictor-Corrector algorithms, but that should shortly expand to include additional options for adaptive, backwards euler, and 4th order symplectic routines.)

