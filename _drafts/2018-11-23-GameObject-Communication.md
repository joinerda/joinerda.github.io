---
layout: post
title: Using the GetComponent Command
use_math: false
---

One of the most important features of [Unity](https://unity3d.com/)'s scripting language is the "GetComponent" command. Each game object in Unity has its features extended by components. Components can be used to attach a renderer, or a collider, or a special effect. Components can also be used to attach our custom scripts.

At times, you will want a script on an object to be able to access that objects other components. Sometimes, you will want your script on one gameobject to be able to access public member variables and methods of a script attached to another game object. GetComponent is the plumbing that will allow that to happen.

This blog will introduce you to the GetComponent command by having our oscillator from the first blog not just oscillate around some equilibrium, but aroudn some equilibrium bond distance to another object.

Additionally, we will show another feature of the Unity editor, which is the use of the Unity editor to set the values of public member variables in a scene. 


