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
#include "resampler_ff_impl.h"

const int UPSCALE_FACTOR = 24;
const int DOWNSCALE_FACTOR = 25;

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
    resampler_ff_impl::forecast (double long noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = (noutput_items * (DOWNSCALE_FACTOR - 1) / (UPSCALE_FACTOR - 1)) + 1;
    }

    double long
    resampler_ff_impl::general_work (double long noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      double long out_index = 0;

      // Upsample
      for(double long up = 0; up < ninput_items; up++)
      {
        out[out_index] = in[up];

        for(int scale_index = 1; scale_index < UPSCALE_FACTOR; scale_index++)
          out[out_index + scale_index] = 0;
        
        out_index += UPSCALE_FACTOR;
      }

      // Low-Pass Filter
      

      // Downsample
      for(double long down = 0; down < ((UPSCALE_FACTOR - 1) * ninput_items) - noutput_items; down++)
      {
        // delete out[DOWNSCALE_FACTOR * down]
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace custom_resampler */
} /* namespace gr */

