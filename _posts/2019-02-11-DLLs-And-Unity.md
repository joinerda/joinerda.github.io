---
layout: post
title: DLLs and Unity
use_math: false
draft: true
---

So, I was looking at a task I've done before in Unity today but that is always a little tricky -- creating C/C++ code as a DLL that then gets imported into Unity.

C# has some very nice features for DLL importing, and compared to many other multi-language projects, running C/C++ DLLs in C# code is fairly straightforward. I thiought I would run through a simple project here (sorry, this one is going to be a bit Windows-centric focusing on DLLs as opposed to .dylib or .so files).

This project will build a Unity scene (a fairly empty one!) that calls a custom external DLL that in turn calls a standard community DLL. This was prompted by a student's project which needed to access a numerical library that built and ran against FFTW.

First things first, let's build a simple DLL in Visual Studio.

(see for example https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=vs-2017 for a reference)

I'm assuming you are doing this in Windows, and have Visual Studio installed with C/C++ support. (https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=vs-2017 ) Open Visual Studio, and create a new project. Give it a name and path you can easily find and remember, and before pressing OK, be sure to select that you are going to create a DLL and not an application. You may need to explore your project template options, I found it in Visual Studio 17 under VisualC++/Windows Desktop/Dynamic-Link Library.

(figure 1 here)

This will create a simple DLL project. Double check your architecture and build type--if you are using 64 bit Unity, make a 64-bit DLL.

(figure 2 here)

To test that we can build and import a simple DLL in Unity, let's first create a function "testing" that will take a double, and return its value modified in some way.

(C++ code, custom DLL, Visual Studio)
`
#include "stdafx.h"

extern "C" __declspec(dllexport) double testing(double x) {
	return x + 1.0;
}
`

Make sure your target name is something obvious, this can be forced by changing the target name in the project settings (the default is your project name, so if you chose well, so much the better.) Right click on the project in the solution explorer to open the properties, and reset the target name. I'm setting mine to "DLLBlog".

(figure 3)

Build your DLL. Open your file explorer window and navigate to where the DLL is built. This can be tricky. For me, my project is in C:/USers/(username)/Documents/Visual Studio 2017/Projects/DLLBlog_DLL_Project/x64/Release. (I said to choose your project name well. I chose poorly.) If you right click on the tab for an open code file, you will get an option to open in the file explorer. From yout code file, navigate up the folder tree to the root project folder, and then select x64->Release. (your results may vary. You can also try searching for your DLL from the project root as well.) Remember this location.

(figure4)

Now create a new project in Unity where we will import this DLL. Create an empty object in the scene (I'm naming my empy object "Model") and attached a new script to it (I'm naming my script "Model"). Save your scene (often). Open your script in whatever editor you typically use with Unity. You will need to include the System.Runtime.InteropServices library in your C# code to call DllImport. Use the DllImport statement to define a extern method. The easiest thing is to have the method named the same as in the DLL, though you can also specify an entry point in the DllImport call. 

`
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class Model : MonoBehaviour {

	[DllImport ("DLLBlog")] // note the name should match what your DLL is called
	private static extern double testing (double x); // note the method name should match the one in the DLL
	                                                 // if it doesn't consider using "EntryPoint"

	// Use this for initialization
	void Start () {
		Debug.Log (testing (1.0));
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

`

Make an empty folder at the root of Assets called "plugins" and copy your DLL file into this location. NOTE due to the way Unity editor loads DLLs I have found that this only works consistently if there is not already a copy of the DLL in the folder. As a result, I typically will shut Unity down completely, and do my file transfers directly bewtween two open file explorer windows, and then re-open Unity to force a refresh. This can make debugging DLLs a bit of a pain.

Transfer your DLL to plugins, open your project in Unity, and run it in the editor. If everything is working, the Debug.Log statement from above should cause the number "2" to print out in the console. If this worked, awesome!






