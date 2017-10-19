// audio_tools.cpp --- 
// 
// Filename: audio_tools.cpp
// Description: 
// Author: stax
// Maintainer: 
// Created: ven nov 13 05:57:59 2009 (+0100)
// Version: 
// Last-Updated: jeu nov 19 16:20:05 2009 (+0100)
//           By: stax
//     Update #: 3
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.
// 
// 
#include "audio_tools.h"

float getDbVal(float val)
{
  float db=20.0f * log10f(val);
  return db;
}
float getDbPercent(float db) 
{
  float def = 0.0f; /* Meter deflection %age */

  if (db < -70.0f) {
    def = 0.0f;
  } else if (db < -60.0f) {
    def = (db + 70.0f) * 0.25f;
  } else if (db < -50.0f) {
    def = (db + 60.0f) * 0.5f + 2.5f;
  } else if (db < -40.0f) {
    def = (db + 50.0f) * 0.75f + 7.5;
  } else if (db < -30.0f) {
    def = (db + 40.0f) * 1.5f + 15.0f;
  } else if (db < -20.0f) {
    def = (db + 30.0f) * 2.0f + 30.0f;
  } else if (db < 6.0f) {
    def = (db + 20.0f) * 2.5f + 50.0f;
  } else {
    def = 115.0f;
  }
  /* 115 is the deflection %age that would be 
     when db=6.0. this is an arbitrary
     endpoint for our scaling.
  */

  return def/115.0f * 100.0f;
}
float hard_clip(float val, float min, float max)
{
  if (val > max)
    return max;
  if (val < min)
    return min;
  return val;
}



// 
// audio_tools.cpp ends here
