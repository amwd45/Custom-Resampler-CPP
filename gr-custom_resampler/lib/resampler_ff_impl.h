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

#ifndef INCLUDED_CUSTOM_RESAMPLER_RESAMPLER_FF_IMPL_H
#define INCLUDED_CUSTOM_RESAMPLER_RESAMPLER_FF_IMPL_H

#include <custom_resampler/resampler_ff.h>

namespace gr {
  namespace custom_resampler {

    class resampler_ff_impl : public resampler_ff
    {
     private:
      // Nothing to declare in this block.

     public:
      resampler_ff_impl();
      ~resampler_ff_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int  general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace custom_resampler
} // namespace gr

#endif /* INCLUDED_CUSTOM_RESAMPLER_RESAMPLER_FF_IMPL_H */

