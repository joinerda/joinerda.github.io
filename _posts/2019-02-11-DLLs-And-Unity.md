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

