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

Let's return to the Simple Harmonic Oscillator model, using the Integrator class. The process will be as follows. We will create a general Model object that contains a reference to SHOIntegrator, which we will also build. The Model will be a monobehaviour that connects to objects in the scene. One member variable of Model will be the SHOIntegrator, which will derive from Integrator, and provides a routine RK4Step that will calculate the next step forward in the integration.

The Integrator class can be downloaded from github at https://github.com/joinerda/unity-modeling-toolkit , or you can copy and paste into a file in your Assets folder called Integrator.cs.

Open a new Unity project, and copy Interator.cs into the Assets folder.

```
// Integrator.cs
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Integrator is an abstract class for integrating a system of ODEs
/// </summary>
abstract public class Integrator  {

	int nEquations;
	double [] store;
	double [] k1;
	double [] k2;
	double [] k3;
	double [] k4;
	double [] ym1;
	double [] ym2;
	double [] ym3;
	double [] P;
	double [] dm1;
	double [] dm2;
	double [] dm3;
	double [] dp1;
	int abmSteps =0;
	double abmRms2;

	public Integrator() {
		Init (1);
	}

	public double [] getK3() {
		return k3;
	}

	/// <summary>
	/// Allocate memory for all storage arrays and set number of equations
	/// </summary>
	/// <param name="nEquations">N equations.</param>
	public void Init (int nEquations) {
		// set up temp arrays
		this.nEquations = nEquations;
		store = new double[nEquations];
		k1 = new double[nEquations];
		k2 = new double[nEquations];
		k3 = new double[nEquations];
		k4 = new double[nEquations];
		ym1 = new double[nEquations];
		ym2 = new double[nEquations];
		ym3 = new double[nEquations];
		P = new double[nEquations];
		dm1 = new double[nEquations];
		dm2 = new double[nEquations];
		dm3 = new double[nEquations];
		dp1 = new double[nEquations];
		abmSteps = 0;
	}

	/// <summary>
	/// Abstract void, override this method to set the ODEs to be
	/// integrated.
	/// </summary>
	/// <param name="x">The values being integrated.</param>
	/// <param name="xdot">The derivatives being calculated.</param>
	abstract public void RatesOfChange (double[] x, double[] xdot, double t);
		
	/// <summary>
	/// Step forward using Euler's method
	/// </summary>
	/// <param name="x">The values being integrated.</param>
	/// <param name="h">The time step.</param>
	public void EulerStep(double [] x, double t, double h) {
		RatesOfChange(x,k1,t);
		for(int i=0;i<nEquations;i++) {
			x[i] += k1[i]*h;
		}
	}

	/// <summary>
	/// Step forward using 4th order Runge Kutta method
	/// </summary>
	/// <param name="x">The values being integrated.</param>
	/// <param name="h">The time step.</param>
	public double RK4Step(double [] x, double t, double h) {
		RatesOfChange (x,k1,t);
		for (int i = 0; i < nEquations; i++) {
			store [i] = x [i] + k1 [i] * h / 2.0;
		}
		RatesOfChange (store,k2,t);
		for (int i = 0; i < nEquations; i++) {
			store [i] = x [i] + k2 [i] * h / 2.0;
		}
		RatesOfChange (store,k3,t);
		for (int i = 0; i < nEquations; i++) {
			store [i] = x [i] + k3 [i] * h;
		}
		RatesOfChange (store, k4, t);
		for (int i = 0; i < nEquations; i++) {
			x [i] = x [i] + (k1[i] +2.0*k2[i]+ 2.0*k3 [i]+k4[i]) * h/6.0;
		}
		return t + h;
	}


	/**
	 * Calculates a single step using Adams Bashforth Moulton,
	 * 
	 * @param x Array of values being integrated.
	 * @param t Time at which step begins
	 * @param h Duration of step
	 * @return Error prediction at end of step
	 */
	public double abmStep(double [] x, double t, double h) {
		abmRms2 = 0.0;
		if(abmSteps==0) {
			for(int i=0;i<x.Length;i++) {
				ym3[i] = x[i];
				ym2[i] = x[i];
			}
			RatesOfChange(dm3,ym3,t);
			t = RK4Step(ym2,t,h);
			RatesOfChange(dm2,ym2,t);
			for(int i=0;i<x.Length;i++) {
				x[i] = ym2[i];
			}
			abmSteps+=1;
			return 1.0;
		} else if(abmSteps==1) {
			for(int i=0;i<x.Length;i++) {
				ym1[i] = ym2[i];
			}
			t = RK4Step(ym1,t,h);
			RatesOfChange(dm1,ym1,t);
			for(int i=0;i<x.Length;i++) {
				x[i] = ym1[i];
			}
			abmSteps +=1;
			return 1.0;
		} else {
			RatesOfChange(k1,x,t);
			for(int i=0;i<x.Length;i++) {
				P[i] = x[i] + (h/24.0)*
					(55.0*k1[i]-59.0*dm1[i]+37.0*dm2[i]-9.0*dm3[i]);
			}
			RatesOfChange(dp1,P,t+h);
			abmRms2 = 0.0;
			for(int i=0;i<x.Length;i++) {
				store[i] = x[i];
				x[i] += (h/24.0)*(9*dp1[i]+19.0*k1[i]-5.0*dm1[i]+dm2[i]);
				dm3[i] = dm2[i];
				dm2[i] = dm1[i];
				dm1[i] = k1[i];
				ym3[i] = ym2[i];
				ym2[i] = ym1[i];
				ym1[i] = store[i];
				abmRms2 += (x[i]-P[i])*(x[i]-P[i])/(x[i]+P[i])/(x[i]+P[i]);
			}
			abmRms2 /= x.Length;
			if(abmSteps<5) abmSteps += 1;
			return t+h;
		}
	}

	public double abmError() {
		return abmRms2;
	}

}
```

We will create a script that extends Integrator, called SHOIntegrator. Right click in the project panel and create a new C# script called SHOIntegrator. Change the class heading created by default so that instead of extending MonoBehaviour, extend Integrator.

Remove the default Update and Start routines as those are related to MonoBehaviour, and SHOIntegrator is not extending MonoBehaviour.

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOIntergator : Integrator {

}
```

We will add member variables to SHOIntegrator for the SHO simulation, for the spring stiffness $k$ and oscillator mass $m$. We will also override the RatesOfChange method in Integrator to return the rates of change in the SHO simulation.

$$
\dot{x} = v 
\dot{v} = -(k/m) x
$$

The RatesOfChange routine will take as an argument an array of all of the dependent varaiables being integrated, as a 1-D array. Anytime we use a standard integrator library, this will be a common practice--to map the variables being integrated to a 1-D array. Sometimes this will be fairly straightforward, such as mapping $x$ to position 0 and $v$ to position 1. Other systems of ODEs may not be as straight forward to map to a 1-D array.

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOIntergator : Integrator {

	double k = 1;
	double m = 1;

	public override void RatesOfChange (double[] x, double[] xdot, double t)
	{
		xdot [0] = x [1];
		xdot [1] = -(k / m) * x [0];
	}

}

```

We will add an array x to store our state variables, and allocate it to be 2 elements long. Additionally, it will be easier to set up the initialization of the Integrator class (called with the Init(int nEquations) method) and all initial conditions if we have a single method to do so.

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOIntergator : Integrator {

	double k = 1;
	double m = 1;
	double [] x;

	public void SetIC(double x0, double v0) {
		x = new double[2];
		Init (2); // allocates memory for Integrator varaibles
		x [0] = x0;
		x [1] = v0;
	}

	public override void RatesOfChange (double[] x, double[] xdot, double t)
	{
		xdot [0] = x [1];
		xdot [1] = -(k / m) * x [0];
	}

}
```

To put this into our scene, we need something with a MonoBehaviour. Let's create a empty game object called SHOModel, and attach a new C# script to it, also called SHOModel. Also add a sphere to the scene, and name it ObjectToMove.

In the SHOModel script, add a variable to hold a reference to the sphere in our scene.

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOModel : MonoBehaviour {

	public GameObject objectToMove;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
```

Save everything and drag ObjectToMove into the space for "ObjectToMove" in the inspector for SHOModel. Save your scene if you haven't already.






