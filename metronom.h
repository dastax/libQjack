/* metronom.h --- 
 * 
 * Filename: metronom.h
 * Description: 
 * Author: stax
 * Maintainer: 
 * Created: ven nov 27 14:51:43 2009 (+0100)
 * Version: 
 * Last-Updated: ven nov 27 19:34:29 2009 (+0100)
 *           By: stax
 *     Update #: 18
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

#ifndef METRONOM_H
#define METRONOM_H

#include <QtGui>

class Metronom : public QObject
{
Q_OBJECT
 private:
  float *_wave;
  int _offset;
  int _size;
  int _samplerate;
  bool _playing;
  int _bpm, _beatsPerBar, _beatLength;
  bool _loaded;
  QMutex _mutex;

  void generateMetroWave(int bpm, int beats_per_bar, int beat_length);

 public:
  Metronom();
  ~Metronom();

  void setSamplerate(int sr);
  void toggleMetronom(bool);
  void setOffset(int);
  float stepMetronom();
  void processBuffers(float *buf1, float *buf2, int size);

 public slots:
  void setTimeBase(int bpm, int beats_per_bar, int beat_length);
};

class MetronomWidget : public QGroupBox
{
Q_OBJECT
 private:
  Metronom _metronom;
  QPushButton _toggler;
  
 private slots:
  void metronomToggled(bool);

 public:
  MetronomWidget();

  void setSamplerate(int sr) {_metronom.setSamplerate(sr);}
  void setOffset(int o) {_metronom.setOffset(o);}
  float stepMetronom() {return _metronom.stepMetronom();}
  void processBuffers(float *buf1, float *buf2, int size) {_metronom.processBuffers(buf1, buf2, size);}

 public slots:
  void setTimeBase(int bpm, int bpb, int bl) {_metronom.setTimeBase(bpm, bpb, bl);}
};

#endif
/* metronom.h ends here */
