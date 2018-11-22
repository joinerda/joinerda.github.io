---
layout: post
title: Using the GetComponent Command
use_math: false
---

One of the most important features of [Unity](https://unity3d.com/)'s scripting language is the "[GetComponent](https://docs.unity3d.com/ScriptReference/GameObject.GetComponent.html)" command. Each game object in Unity has its features extended by components. Components can be used to attach a renderer, or a collider, or a special effect. Components can also be used to attach our custom scripts.

At times, you will want a script on an object to be able to access that objects other components. Sometimes, you will want your script on one gameobject to be able to access public member variables and methods of a script attached to another game object. GetComponent is the plumbing that will allow that to happen.

This blog will introduce you to the GetComponent command by having our oscillator from the first blog not just oscillate around some equilibrium, but around some equilibrium bond distance to another object.

Additionally, we will show another feature of the Unity editor, which is the use of the Unity editor to set the values of public member variables in a scene, as well as the creation of prefab objects to make it easy to create many objects with the same customizations.

This blog post assumes you have worked through the previous post, or that you know how to add a gameobject to a unity scene and attach a script to the object. We will not, however, start from where the last blog left off but rather start from a new unity game.

Open unity and create a new 3D game.

Create a sphere in the hierarchy. Save your scene. Often.

Add a component to the sphere of a new script. Name the script something that makes sense to you. This will be something that we will make a prefab out of, and what I like to do is to have the prefab and the script have the same name. I'm going to rename my sphere in the hierarchy window "Body", and add a script called Body to it. If my prefab, its script, its materials, etc. all have the same name its easier to see what goes together.

Once that is done, drag Body from the hierarchy panel to the project panel. This is the easiest way to create a prefab. Creating an object as a prefab has many advantages, especially if the object will be reused in many scenes, many programs, or if there will be multiple copies of the object in the same scene. The object in the hierarchy is now linked to this prefab, and changes in the prefab that haven't been overridden in the hierarchy will automatically updated across all instances of the prefab in the scene.

What we are going to do initially is create a string of Body objects, all in a row. Each of these objects will have a link to objects on the right and left, which we will set in the editor. Our leftmost and rightmost object will be fixed in place, and all of them will be modeled to move as if connected in line by a series of springs. Each object will move as an oscillator, as in the last blog, but the spring forces will be determined by a relaxed length of each spring and by the position of the objects to the left and right.

This will allow us to see one method of creating a model in unity, where each instance of an object has its own rules for recognizing its surroundings and interacting with them.





