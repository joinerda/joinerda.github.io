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
