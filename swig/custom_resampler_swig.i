/* -*- c++ -*- */

#define CUSTOM_RESAMPLER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "custom_resampler_swig_doc.i"

%{
#include "custom_resampler/resampler_ff.h"
%}


%include "custom_resampler/resampler_ff.h"
GR_SWIG_BLOCK_MAGIC2(custom_resampler, resampler_ff);
