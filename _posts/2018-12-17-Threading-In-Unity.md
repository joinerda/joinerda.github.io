---
layout: post
title: Threading
use_math: true
draft: false
---

The fundamental dynamic in any GUI driven simulation is the interplay between the GUI and the simulation.
The communication between the two can create problems in your application when the timing of the two
doesn't line up.

If your model is really simple, there is a risk that running the GUI will slow down an otherwise simple model.

If you model consumes a large deal of CPU time, there is a risk that running your model will freeze your GUI.

The best practice is to separate out modeling from GUI-ing, so that the two can run independently. Typically
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
an abstract Integrator class will be used to create a model to integrate. (If you went through the last post, we'll use that SHOIntegrator as our example.) Our threaded TimestepModel will have a member variable that extends Integrator, and will move the integration step forward in its threaded step.

If you don't have the last blogs model ready to go, it can be obtained [here](/files/blog_2018_12_11/IntegratorExample.zip)

This blog will build off of the TimestepModel class, which you can get from the UMT, or you can copy and paste from below.

```
using UnityEngine;
using System.Collections;
using System.Threading;


public abstract class TimestepModel : MonoBehaviour {

	public float modelDT = 0.01f;
	public Thread modelThread;

 	bool threadRunning = true;
	bool stepFree = true;
	bool stepRunning = false;
	public float modelT = 0.0f;

	public bool threaded = true;
	bool fastrun = true;
	bool paused = false;

	static readonly object _locker = new object();

	~TimestepModel() {
		Thread.Sleep (0);
		modelThread.Abort ();
	}

	public bool GetThreaded()
	{
		return threaded;
	}

	// Use this for initialization
	public void ModelStart()
	{
		modelT = 0.0f;
		// create thread before finishing Start
		if (threaded)
		{
			modelThread = new Thread(this.ThreadedActions);
			modelThread.Start();
		}

	}

	public void ThreadedActions()
	{
		while (threadRunning)
		{
			Thread.Sleep (0);

			try
			{
				if (stepFree || fastrun)
				{
					stepRunning = true;
					TakeStep(modelDT);
					modelT += modelDT;//am I doing this twice?
					stepRunning = false;
				}
				if (!fastrun)
					lock (_locker)
					{
						stepFree = false;
					}
			}
			//(ThreadAbortException ex) 
			catch
			{
				threadRunning = false;
			}
		}
	}
		
	void FixedUpdate()
	{
		if (threaded)
		{
			lock (_locker)
			{
				stepFree = true;
			}
		}
		else
		{
			stepRunning = true;
			TakeStep(modelDT);
			modelT += modelDT;
			stepRunning = false;
		}
	}

	public void Pause(bool yesNo)
	{
		lock (_locker)
		{
			stepFree = false;
			// would a lock be more efficient here?
			while (stepRunning) { } // wait for step to finish to avoid race condition
			// grow array if needed
			paused = yesNo;
		}
	}

	public abstract void TakeStep (float dt);
}
```

Note that our script includes System.Threading as a library, and includes a member variable of type Thread. in ModelStart, the thread is instantiated and started with a method of ThreadedActions, also defined in the class. In the destructor, the thread is stopped and destroyed. ThreadedActions uses the abstract method TakeStep, which we will define in our class that extends from TimestepModel, and also provides some logic that allows the GUI to lock the thread to avoid a race condition. We can request the thread pause using the Pause method.

To begin, let's change SHOModel from last time so that instead of extending MonoBehaviour, it extends TimestepModel. This will require providing an override for TakeStep, go ahead and do that as a placeholder so that the script will compile.

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOModel : TimestepModel {

	public GameObject objectToMove;
	SHOIntegrator theIntegrator;
	double t = 0.0;
	double h = 0.01;

	public override void TakeStep (float dt) {
	}


	// Use this for initialization
	void Start () {
		theIntegrator = new SHOIntegrator ();
		theIntegrator.SetIC (1, 0);
		
	}

	void FixedUpdate() {
		t = theIntegrator.RK4Step (theIntegrator.x, t, h);
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 pos = objectToMove.transform.position;
		pos.x = (float)theIntegrator.x [0];
		objectToMove.transform.position = pos;
	}
}
```

To use TimestepModel, we need to provide our TakeStep routine, and we need to call TimestepModel's ModelStart method in our classes Start routine. Add ModelStart() to Start, and move the RK$Step call from FixedUpdate to TakeStep. Notice that TakeStep gets its value of h from TimestepModel, so we do not want a hard-coded value of h.

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOModel : TimestepModel {

	public GameObject objectToMove;
	SHOIntegrator theIntegrator;
	double t = 0.0;

	public override void TakeStep (float dt) {
		t = theIntegrator.RK4Step (theIntegrator.x, t, dt);
	}


	// Use this for initialization
	void Start () {
		theIntegrator = new SHOIntegrator ();
		theIntegrator.SetIC (1, 0);
		ModelStart ();
	}

	void FixedUpdate() {
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 pos = objectToMove.transform.position;
		pos.x = (float)theIntegrator.x [0];
		objectToMove.transform.position = pos;
	}
}
```

Save everything and go back to your editor. Run the model. Notice the speed difference between the threaded and non-threaded version. "threaded" is a public boolean variable in TimestepModel, and you can set whether the object should run as threaded or not before playing the editor. (Note that the non-threaded action in TimestepModel runs in FixedUpdate, so if you create an extension of TimestepModel that also defines FixedUpdate you should be sure to call the base class version of the method).

```
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHOModel : TimestepModel {

	public GameObject objectToMove;
	SHOIntegrator theIntegrator;
	double t = 0.0;

	public override void TakeStep (float dt) {
		t = theIntegrator.RK4Step (theIntegrator.x, t, dt);
	}


	// Use this for initialization
	void Start () {
		theIntegrator = new SHOIntegrator ();
		theIntegrator.SetIC (1, 0);
		ModelStart ();
	}

	void FixedUpdate() {
		base.FixedUpdate (); // either do not provide FixedUpate or include call to base.FixedUpdate()
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 pos = objectToMove.transform.position;
		pos.x = (float)theIntegrator.x [0];
		objectToMove.transform.position = pos;
	}
}
```

Make Model DT smaller in the editor and compare the difference in the running speed of this simple model using threading versus using FixedUpate.

For the next blog, I'll use the N-Body problem to show how you can use threading to handle the other extreme, calculations that would otherwise take so long that it would freeze up the GUI to try to do them in the standard Unity game loop.


[Comment on Twitter](https://twitter.com/dajoiner/status/1072956878861332481)





