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


#ifndef INCLUDED_CUSTOM_RESAMPLER_RESAMPLER_FF_H
#define INCLUDED_CUSTOM_RESAMPLER_RESAMPLER_FF_H

#include <custom_resampler/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace custom_resampler {

    /*!
     * \brief <+description of block+>
     * \ingroup custom_resampler
     *
     */
    class CUSTOM_RESAMPLER_API resampler_ff : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<resampler_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of custom_resampler::resampler_ff.
       *
       * To avoid accidental use of raw pointers, custom_resampler::resampler_ff's
       * constructor is in a private implementation
       * class. custom_resampler::resampler_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace custom_resampler
} // namespace gr

#endif /* INCLUDED_CUSTOM_RESAMPLER_RESAMPLER_FF_H */

