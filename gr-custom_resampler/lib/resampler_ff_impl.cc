/* -*- c++ -*- */
/* 
 * Copyright 2019 gr-custom_resampler author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <gnuradio/math.h>
#include <vector>
#include <stdio.h>
#include "resampler_ff_impl.h"

const int INTERPOLATION = 24;
const int DECIMATION = 25;

namespace gr {
  namespace custom_resampler {

    resampler_ff::sptr
    resampler_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new resampler_ff_impl());
    }

    /*
     * The private constructor
     */
    resampler_ff_impl::resampler_ff_impl()
      : gr::block("resampler_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    resampler_ff_impl::~resampler_ff_impl()
    {
    }

    void
    resampler_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items * DECIMATION / INTERPOLATION;
    }

    int
    resampler_ff_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const double OUT_SAMPLING_RATE = 48000; // 48kHz

      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      std::vector<float> samples(ninput_items[0] * (INTERPOLATION + 1));
      double cutoffFreq = 18000; // center frequency
      //long out_index = 0;


      // Interpolation
      for(int up = 0; up < ninput_items[0]; up++)
      {
        //samples.push_back(in[up]);
        samples[up * (INTERPOLATION + 1)] = in[up];

        for(int scale_index = 1; scale_index < INTERPOLATION; scale_index++)
          samples[up * (INTERPOLATION + 1) + scale_index] = 0;
          //samples.push_back(0);
        
        //out_index += INTERPOLATION;
      }

      samples.shrink_to_fit();



      // Compute Taps
      int ntaps = 15; // set to 15 for now, may need to write code to calculate later
      std::vector<float> taps(ntaps);

      int M = (ntaps - 1) / 2;
      double fwT0 = 2 * M_2_PI * cutoffFreq / OUT_SAMPLING_RATE;

      for(int n = -M; n <= M; n++)
      {
        if(n == 0)
          taps[n+M] = fwT0 / M_2_PI;

        else
        {
          taps[n+M] = sin(n * fwT0) / (n * M_2_PI);
        }
      }



      // Filter
      std::vector<float> f_samples(samples.size());

      for(int f_index = 0; f_index < samples.size(); f_index++)
      {
        //f_samples[f_index] = 0;

        for(int t_index = 0; t_index < ntaps; t_index++)
        {
          if(f_index >= t_index)
            f_samples[f_index] += taps[t_index] * samples[f_index - t_index];
        }
      }



      // Decimation
      for(int down = 0; down < noutput_items; down++)
      {
        out[down] = f_samples[DECIMATION * down];
      }

      //samples.shrink_to_fit();

/*
      // Copy Contents to Output
      for(int copy = 0; copy < noutput_items; copy++)
        out[copy] = f_samples[copy];*/



      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (ninput_items[0]);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace custom_resampler */
} /* namespace gr */

