---
layout: post
title: Game Of Life in 3D
use_math: true
draft: true
---

Conway's Game of Life https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life s a classic problem for computer science students, and provides an early example of cellular automata as well as an opportunity to practice nested loops and multi-dimensional arrays. http://www.shodor.org/interactivate/activities/Life/ . For larger grids, it can also be an opportunity for students to think about domain decomposition and parallelism. http://www.shodor.org/petascale/materials/UPModules/GameOfLife/ .

The Game of Life can also be an interesting activity to study in 3 dimensions. https://www.complex-systems.com/abstracts/v16_i04_a07/ . 

This post will walk through creating a Unity 3D model of the Game of Life in 3D. Cells will be visualized as on (visible) or off(not visible), with color and transparency used to indicate the stability of each cell.

To begin, start with a new 3D scene in Unity. Add an empty game object in the Hierarchy, and call it "Model." Attach a script component to it, also called Model.

In the Model script, we are going to create an array to store our Game of Life grid, and some information about the Game of Life rules. Additionally, we will create a routine for counting neighbors, a key step in the Game of Life, which includes the ability to count in 2 or 3D (to compare to the classic 2D problem.) We will use the Update routine to step forward, so that we do not lose any steps in the visualization.



