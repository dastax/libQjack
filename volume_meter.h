/* volume_meter.h --- 
 * 
 * Filename: volume_meter.h
 * Description: 
 * Author: stax
 * Maintainer: 
 * Created: ven nov 20 22:05:07 2009 (+0100)
 * Version: 
 * Last-Updated: lun. déc. 14 16:33:51 2009 (+0100)
 *           By: stax
 *     Update #: 16
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

#ifndef VOLUME_METER_H
#define VOLUME_METER_H

#include "vumeter.h"
#include "midi_widgets.h"

class VolumeMeter : public QWidget
{
Q_OBJECT
 private:
  StereoVuMeter _vu;
  Midifader _volume;
  Midifader _pan;
  Midibut _mute;
  QString _id;
  float _limit;

  void paintEvent(QPaintEvent *);

 private slots:
  void volumeChanged(float);
  void panChanged(float);
  void muteToggled(bool);

 public:
  VolumeMeter(QString id, QString group="");

  void setLimit(float l) {_limit=l;}
  QString getID() {return _id;}
  void processBuffers(float *buf1, float *buf2, int size);

 public slots:
  void refresh() {_vu.refresh();}
};

#endif

/* volume_meter.h ends here */
