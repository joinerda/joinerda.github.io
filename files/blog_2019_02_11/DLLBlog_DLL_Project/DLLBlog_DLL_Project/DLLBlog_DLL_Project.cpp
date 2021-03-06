// DLLBlog_DLL_Project.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "stdafx.h"
#include "fftw3.h"



double example()
{
	fftw_complex *in, *out;
	fftw_plan p;
	int N = 1024;
	double retval = 0.0;

	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	for (int i = 0; i < N; i++) {
		in[i][0] = 1.0;
		in[i][1] = 0.0;
	}
	fftw_execute(p); /* repeat as needed */

	retval = out[0][0];
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
	return retval;
}

extern "C" __declspec(dllexport)  double testing(double x) {
	double y = example();
	return x + y;

}