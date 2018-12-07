---
layout: post
title: Javaplots
use_math: true
draft: true
---

The fundamental dynamic in any GUI driven simulation is the interplay between the GUI and the simulation.
The communication between the two can create problems in your application when the timing of the two
doesn't line up.

If your model is really simple, there is a risk that running the GUI will slow down an otherwise simple model.

If you model consumes a large deal of CPU time, there is a risk that running your model will freeze your GUI.

The best practice is to spearate out modeling from GUI-ing, so that the two can run independently. Typically
we would do this by running the modle in a Thread. C# as a language does prvide threading features taht are easy to use.
There is one catch, though.

Unity is not a thread safe application. You can't call the Unity API from anything other than the main thread.
For the most part, this is a non-issue, but it can make debugging applications difficult, as your
debugger may not work well with threads, and Debug.Log (being part of the Unity API), is no longer an option for printf
style debugging.

All of this is to say that threading is worth it, but has its fair share of pain points in the process of implementing it.

This blog will introduce a class that can be used to simplify threading in Unity, called TimestepModel. Timestep model is a
MonoBehaviour that can be attahced to an object in your scene, and provides an option to perform computation either
as part of a FixedUpdate routine, or as a separate thread. Threading can be turned on or off using a simple boolean
flag. The class is abstract, and in extending it you need to provide a "TakeStep(double dt)" method.

Additionally, as a common modeling task to be threaded might be integration of a system of differential equations, 
an abstract Integrator class will be used to create a model to integrate. Our threaded TimestepModel will have a 
member variable that extends Integrator, and will move the integration step forward in its threaded step.
