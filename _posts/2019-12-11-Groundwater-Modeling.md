---
layout: post
title: Groundwater Modeling
use_math: true
draft: true
---

Additional Authors: Xyler Ferraris

**Dave:** Way back when during my Shodor days, there was a model developed by Garrett Love that looked at a groundwater model in 2D, that was based around a groundwater modeling kit that was on the market. The model was originally developed in NetLogo, and allowed for varying hydraulic conductivity, different surface elevations, wells, and pumps. My student, Xyler, came to me with a researhc project idea on modeling groundwater flow, and he and I talked about re-working it in Unity, initially in 2D and eventually in 3D.

**Xyler:** One of the biggest challenges for this project was converting from the base of NetLogo to the Unity Gaming Engine. NetLogo uses a unique object oriented way of coding, using patches that represent space and turtles (which for ou model we called nodes) that can exist in the space. Each patch is either a square or rectangle and will have a node on each corner which is then connected to another patch so long it is not at the border of the whole grid. This can be easily adapted to use when creating flow charts and when doing 2 Dimensional simulations of, as an example, groundwater flow through permeable soil. Meanwhile, the Unity Gaming Engine can be used for practically an infinite amount of ideas, projects and assignments. This brought into light our first goal, attempt to remodel the NetLogo version. 

The creation of our patches and nodes wasn’t as difficult as I initially thought it would be, and in general worked out well. Using the sphere and object and the cube object we linearly spaced them to fit appropriately in a grid. Once the patches and nodes were created we began to implement the groundwater flow equations and Laplace’s equation for steady-state flow. 

**Dave:** I think one of the coolest aspects of this project so far is working on a design to take NetLogo style models and rework them in the Unity framework. This is still very developmental at the moment, but it would make a lot of sense to be able to take the NetLogo style and recreate it. Both are good at letting you express space and object in an object-oriented sense, both have methods of querying and affecting things nearby. The languages, however, couldn't be more different. I'm hoping we come up with a clear example project of how to take a classic NetLogo model and convert it, and add in 3D visualization feature.

**Xyler:** (Personal thoughts of the Unity engine) It amazed me after working with Unity for a few months seeing how easy everything can be implemented and created in a new setting from its original. It graphically looks cleaner and can be oriented however which way you desire it to be, and not only that but at one point it can even be visualized using virtual reality. This project has much farther to go and can go in many different paths to the desire of the user. Our end goal is to allow for a 3-Dimensional area to generate the flow fields in all directions. With this we can visualize it in VR and then be able to path the existing pollution in specific soils. My overall experience was great with the help from Dr. Joiner.

**Dave:** This one is still in progress, so no code to share yet, but we will release something soon.

![Groundwater Model Poster](/images/blog_2019_12_11/GroundwaterPoster.png)


