---
layout: post
title: Game Of Life in 3D
use_math: true
draft: true
---

Conway's Game of Life ([see Wikipedia entry](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)) is a classic problem for computer science students, and provides an early example of cellular automata as well as an opportunity to practice nested loops and multi-dimensional arrays. http://www.shodor.org/interactivate/activities/Life/ . For larger grids, it can also be an opportunity for students to think about domain decomposition and parallelism. http://www.shodor.org/petascale/materials/UPModules/GameOfLife/ .

The Game of Life can also be an interesting activity to study in 3 dimensions. https://www.complex-systems.com/abstracts/v16_i04_a07/ . 

This post will walk through creating a Unity 3D model of the Game of Life in 3D. Cells will be visualized as on (visible) or off(not visible), with color and transparency used to indicate the stability of each cell.

To begin, start with a new 3D scene in Unity. Add an empty game object in the Hierarchy, and call it "Model." Attach a script component to it, also called Model.

In the Model script, we are going to create an array to store our Game of Life grid, and some information about the Game of Life rules. Additionally, we will create a routine for counting neighbors, a key step in the Game of Life, which includes the ability to count in 2 or 3D (to compare to the classic 2D problem.) We will use the Update routine to step forward, so that we do not lose any steps in the visualization.

The member variables we will need include arrays for both the grid itself as well as a count of neighbors at each grid position. We need to store all of the counts before updating each cell, as changing the cells during counting will affect our count. We also need a list of GameObjects for each cell to show in the screen, and variables to determine the size of the cell. A boolean will be used to turn off counting in the up-down (y) direction, and the Game of Life rules will be stored in two arrays giving allowed values for the next iteration if the cell is in an on or off state. Timer variables will be used to speed up or slow down the simulation, and we will need to provide some information about material and color for our objects.

```
	int [,,] theGrid; // length each cell has been on (0 for off)
	int [,,] neighbors; // storage for count of neighbors
	GameObject [,,] theObjects; // array of objects to show cells on screen
	int nx=30; // grid size
	int ny=1;
	int nz=30;
	bool useY = false; // should we count in y direction (for 2D comparison)
	int [] onRule = new int[]{2,3}; // On rule, if on how many neighbors to stay on
	int [] offRule = new int[]{3}; // Off rule. if off how many neighbors to turn on
	int onMax = 100; // maximum stored "age" of cell (to avoid overflow)
	float delay = 0.01f; // preferred delay between frames
	float time = 0.0f; // time counter for delaying frames
	public Material theMaterial;
	public Color youngColor = Color.green;
	public Color oldColor = Color.blue;
```

To set initial values, we will just use a random number call.

```
	void Reset() {
		float threshhold = 0.5f; // random threshhold for creating on cell
		for (int i = 0; i < nx; i++) // for every cell
			for (int j = 0; j < ny; j++)
				for (int k = 0; k < nz; k++)
					// set cell at random
					if (Random.Range (0.0f, 1.0f) < threshhold)
						theGrid [i, j, k] = 1;
					else
						theGrid [i, j, k] = 0;
				
	}
```

We will use the age of each cell to determine how to draw it. Cells with zero age (turned off) will not be shown, cells that are on will be drawn with an interpolated color based on how long they have been on, up to some "old age".

```
	void SetVisibility() {
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					if (theGrid [i, j, k] > 0) { // if cell is on, show it
						theObjects [i, j, k].SetActive (true);
						Color cellColor = Color.Lerp (youngColor,oldColor, (float)theGrid [i, j, k] / onMax);

						theObjects [i, j, k].GetComponent<Renderer> ().material.color = cellColor;
					} else {
						theObjects [i, j, k].SetActive (false);
					}
				}
			}
		}
	}
```

Our initialization will allocate each of the arrays, and set up the game objects. Note that we will need three public variables set for this to work, a Material and two colors. The Material is so that we can add transparency, the default material in Unity is opaque. In your unity scene, create a new material, and change it from standard to sprite->diffuse (which is both faster than standard and allows transparency). Once your model script is set up and compiling, you can set it's public variable to the material you just created.

```
// Use this for initialization
	void Start () {
		// allocate grid space
		theGrid = new int[nx, ny, nz];

		// allocate neighbor count space
		neighbors = new int[nx, ny, nz];

		// set initial grid to random
		Reset ();

		// allocate and place game objects for each cell
		theObjects = new GameObject[nx, ny, nz];
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					// start with a cube
					theObjects[i,j,k] = GameObject.CreatePrimitive (PrimitiveType.Cube);
					// parent the cube to the Model object
					theObjects [i, j, k].transform.parent = transform;
					// use the largest spacing to set the scale
					float scale = Mathf.Min (1.0f / nx, Mathf.Min (1.0f / ny, 1.0f / nz));
					theObjects [i, j, k].transform.localScale = scale * Vector3.one;
					// place the cells, centering in x and z
					float xpos = i * scale - 0.5f;
					float ypos = j * scale;
					float zpos = k * scale - 0.5f;
					theObjects [i, j, k].transform.position = new Vector3 (xpos, ypos, zpos);
					theObjects [i, j, k].GetComponent<Renderer> ().material = theMaterial;
				}
			}
		}

		// turn objects on or off based on initial values
		SetVisibility ();

	}
```

Our algorithm has two key routines, counting, and checking the rules. For the count, we will loop over every cell, and use modular arithmetic to "wrap" the edges. Additionally, we will put in a check to see whether or not to use the y direction in our count. This makes it easy to compare to 2D models by not counting in y and setting ny to 1.

```
	void Count() {
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					neighbors [i, j, k] = 0; // start count at zero
					for (int l = -1; l < 2; l++) { // nearby in x
						int wi = ((i + l) + nx) % nx; // wrapped neighbor index
						int start = -1;
						int stop = 2;
						if (!useY) { // adjust loop for y if ignoring in count
							start = 0;
							stop = 1;
						}
						for (int m = start; m < stop; m++) { // nearby in y
							int wj = ((j + m) + ny) % ny; // wrapped neighbor index
							for (int n = -1; n < 2; n++) { // nearby in z
								int wk = ((k + n) + nz) % nz; // wrapped neighbor index
								if (l != 0 || m != 0 || n != 0) { // don't count self
									// if nearby cell isn't zero add one to count
									neighbors [i, j, k] += 
										System.Math.Min (theGrid [wi, wj, wk], 1);
								}
							}
						}
					}
				}
			}
		}
	}
```

To use the rules, for every cell we will compare the neighbor count to the allowed values in our member variables.

```
	void Step() {
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					if (theGrid [i, j, k] > 0) { // if cell is on
						bool stayOn = false; // assume off til proven otherwise
						for (int l = 0; l < onRule.Length; l++) { // check allowed values
							if (neighbors [i, j, k] == onRule [l]) {
								stayOn = true;
							}
						}
						// adjust cell value
						if (stayOn) { 
							theGrid [i, j, k] = System.Math.Min (onMax, theGrid [i, j, k] + 1);
						} else {
							theGrid [i, j, k] = 0;
						}
					} else { // if cell is off
						bool turnOn = false; // assume off til proven otherwise
						for (int l = 0; l < offRule.Length; l++) { // check allowed values
							if (neighbors [i, j, k] == offRule [l]) {
								turnOn = true;
							}
						}
						// adjust cell value
						if (turnOn) {
							theGrid [i, j, k] = 1;
						} 
					}
				}
			}
		}
	}
```

Finally, our update will set up each iteration.

```
	// Update is called once per frame
	void Update () {
		// update timer by frame rate
		time += Time.deltaTime;
		if(time>delay) { // if its time to take a step, do so
			Count (); // count neighbors first
			Step (); // update values based on neighbors
			SetVisibility (); // update view

			time = 0.0f; // reset timer
		}
	}
```


When you put it all together it will look like the following

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Model : MonoBehaviour {

	int [,,] theGrid; // length each cell has been on (0 for off)
	int [,,] neighbors; // storage for count of neighbors
	GameObject [,,] theObjects; // array of objects to show cells on screen
	int nx=30; // grid size
	int ny=1;
	int nz=30;
	bool useY = false; // should we count in y direction (for 2D comparison)
	int [] onRule = new int[]{2,3}; // On rule, if on how many neighbors to stay on
	int [] offRule = new int[]{3}; // Off rule. if off how many neighbors to turn on
	int onMax = 100; // maximum stored "age" of cell (to avoid overflow)
	float delay = 0.01f; // preferred delay between frames
	float time = 0.0f; // time counter for delaying frames
	public Material theMaterial;
	public Color youngColor = Color.green;
	public Color oldColor = Color.blue;

	// Use this for initialization
	void Start () {
		// allocate grid space
		theGrid = new int[nx, ny, nz];

		// allocate neighbor count space
		neighbors = new int[nx, ny, nz];

		// set initial grid to random
		Reset ();

		// allocate and place game objects for each cell
		theObjects = new GameObject[nx, ny, nz];
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					// start with a cube
					theObjects[i,j,k] = GameObject.CreatePrimitive (PrimitiveType.Cube);
					// parent the cube to the Model object
					theObjects [i, j, k].transform.parent = transform;
					// use the largest spacing to set the scale
					float scale = Mathf.Min (1.0f / nx, Mathf.Min (1.0f / ny, 1.0f / nz));
					theObjects [i, j, k].transform.localScale = scale * Vector3.one;
					// place the cells, centering in x and z
					float xpos = i * scale - 0.5f;
					float ypos = j * scale;
					float zpos = k * scale - 0.5f;
					theObjects [i, j, k].transform.position = new Vector3 (xpos, ypos, zpos);
					theObjects [i, j, k].GetComponent<Renderer> ().material = theMaterial;
				}
			}
		}

		// turn objects on or off based on initial values
		SetVisibility ();

	}

	void Count() {
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					neighbors [i, j, k] = 0; // start count at zero
					for (int l = -1; l < 2; l++) { // nearby in x
						int wi = ((i + l) + nx) % nx; // wrapped neighbor index
						int start = -1;
						int stop = 2;
						if (!useY) { // adjust loop for y if ignoring in count
							start = 0;
							stop = 1;
						}
						for (int m = start; m < stop; m++) { // nearby in y
							int wj = ((j + m) + ny) % ny; // wrapped neighbor index
							for (int n = -1; n < 2; n++) { // nearby in z
								int wk = ((k + n) + nz) % nz; // wrapped neighbor index
								if (l != 0 || m != 0 || n != 0) { // don't count self
									// if nearby cell isn't zero add one to count
									neighbors [i, j, k] += 
										System.Math.Min (theGrid [wi, wj, wk], 1);
								}
							}
						}
					}
				}
			}
		}
	}

	void Step() {
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					if (theGrid [i, j, k] > 0) { // if cell is on
						bool stayOn = false; // assume off til proven otherwise
						for (int l = 0; l < onRule.Length; l++) { // check allowed values
							if (neighbors [i, j, k] == onRule [l]) {
								stayOn = true;
							}
						}
						// adjust cell value
						if (stayOn) { 
							theGrid [i, j, k] = System.Math.Min (onMax, theGrid [i, j, k] + 1);
						} else {
							theGrid [i, j, k] = 0;
						}
					} else { // if cell is off
						bool turnOn = false; // assume off til proven otherwise
						for (int l = 0; l < offRule.Length; l++) { // check allowed values
							if (neighbors [i, j, k] == offRule [l]) {
								turnOn = true;
							}
						}
						// adjust cell value
						if (turnOn) {
							theGrid [i, j, k] = 1;
						} 
					}
				}
			}
		}
	}

	void Reset() {
		float threshhold = 0.5f; // random threshhold for creating on cell
		for (int i = 0; i < nx; i++) // for every cell
			for (int j = 0; j < ny; j++)
				for (int k = 0; k < nz; k++)
					// set cell at random
					if (Random.Range (0.0f, 1.0f) < threshhold)
						theGrid [i, j, k] = 1;
					else
						theGrid [i, j, k] = 0;
				
	}

	void SetVisibility() {
		for (int i = 0; i < nx; i++) { // for every cell
			for (int j = 0; j < ny; j++) {
				for (int k = 0; k < nz; k++) {
					if (theGrid [i, j, k] > 0) { // if cell is on, show it
						theObjects [i, j, k].SetActive (true);
						Color cellColor = Color.Lerp (youngColor,oldColor, (float)theGrid [i, j, k] / onMax);

						theObjects [i, j, k].GetComponent<Renderer> ().material.color = cellColor;
					} else {
						theObjects [i, j, k].SetActive (false);
					}
				}
			}
		}
	}


	// Update is called once per frame
	void Update () {
		// update timer by frame rate
		time += Time.deltaTime;
		if(time>delay) { // if its time to take a step, do so
			Count (); // count neighbors first
			Step (); // update values based on neighbors
			SetVisibility (); // update view

			time = 0.0f; // reset timer
		}
	}
}

```

Make these changes to Model, and save and compile your code. Once it compiles correctly, you should be able to set your public variables in the scene. Change the transparency of your "young" color to something low, and set your young and old colors to whatever you like. Set the material public variable to a material you create that you have changed the shader to sprite->diffuse. Run and view the model. You may need to move your camera to a more useful spot, or you may want to add in a camera rig from one of our previous posts.

Some interesting rules to check are the classic 2-D (as shown above), or the 5,6,7/6 rule in 3D (count in Y, set nx, ny, nz > 1, onRule = {5,6,7} offRule = {6}). You may need to also change the "threshhold" variable in Reset() to make the initial field more dense or sparse as you try different rules.

What other interesting 3D rules can you find?

[Click here for the final Unity project](/files/blog_2019_01_10/LifeBlog.zip)

[Comments on Twitter](https://twitter.com/dajoiner/status/1075842914926911488)

