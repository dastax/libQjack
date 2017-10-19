/* audio_tools.h --- 
 * 
 * Filename: audio_tools.h
 * Description: 
 * Author: stax
 * Maintainer: 
 * Created: ven nov 13 05:56:47 2009 (+0100)
 * Version: 
 * Last-Updated: jeu nov 26 18:23:34 2009 (+0100)
 *           By: stax
 *     Update #: 4
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

#ifndef AUDIO_TOOLS_H
#define AUDIO_TOOLS_H

#include <math.h>

#define PI	3.14


float getDbVal(float val);
float getDbPercent(float db);
float hard_clip(float val, float min, float max);


#endif

/* audio_tools.h ends here */
