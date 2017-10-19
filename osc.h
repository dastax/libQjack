/* osc.h --- 
 * 
 * Filename: osc.h
 * Description: 
 * Author: stax
 * Maintainer: 
 * Created: jeu nov 26 17:45:44 2009 (+0100)
 * Version: 
 * Last-Updated: jeu nov 26 19:59:25 2009 (+0100)
 *           By: stax
 *     Update #: 8
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

#ifndef OSC_H
#define OSC_H

#include "audio_tools.h"

class Osc
{
 protected:
  int _samplerate;
  float _freq;
  int _pos;
  int _period;

 public:
  Osc();

  void setSamplerate(int sr);
  virtual void setFreq(float f);
  virtual float stepOsc() = 0;
};

class SineOsc : public Osc
{
 private:
  float _scale;

 public:
  SineOsc();

  void setFreq(float f);
  float stepOsc();
};

class SquareOsc : public Osc
{
 private:
  float _val;
  int _halfPeriod;

 public:
  SquareOsc();

  void setFreq(float f);
  float stepOsc();
};

class TriangleOsc : public Osc
{
 private:
  bool _asc;
  int _halfPeriod;
  int _quartPeriod;

 public:
  TriangleOsc();

  void setFreq(float f);
  float stepOsc();
};


#endif


/* osc.h ends here */
