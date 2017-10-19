// volume_meter.cpp --- 
// 
// Filename: volume_meter.cpp
// Description: 
// Author: stax
// Maintainer: 
// Created: ven nov 20 22:08:09 2009 (+0100)
// Version: 
// Last-Updated: lun. déc. 14 16:34:51 2009 (+0100)
//           By: stax
//     Update #: 25
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

#include "volume_meter.h"

VolumeMeter::VolumeMeter(QString id, QString group)
{
  _id=id;
  _limit=-1;
  _mute.setCheckable(true);
  _mute.setIcon(QIcon(QPixmap(":/listen")));
  _pan.setOrientation(Qt::Horizontal);
  _volume.setMidiGroup(group);
  _mute.setMidiGroup(group);
  _pan.setMidiGroup(group);
  QHBoxLayout *vu=new QHBoxLayout;
  vu->addWidget(&_volume);
  vu->addWidget(&_vu);
  QVBoxLayout *lo=new QVBoxLayout;
  lo->addLayout(vu, 1);
  lo->addWidget(&_pan);
  lo->addWidget(&_mute);
  setLayout(lo);

  connect(&_volume, SIGNAL(valueChanged(float)),
	  this, SLOT(volumeChanged(float)));
  connect(&_pan, SIGNAL(valueChanged(float)),
	  this, SLOT(panChanged(float)));
  connect(&_mute, SIGNAL(toggled(bool)),
	  this, SLOT(muteToggled(bool)));

  _volume.initFader(id+"_volume", 0, 1, 127);
  _pan.initFader(id+"_pan", 0, 100, 63, true, true);
  _mute.setMidiID(id+"_mute");
}
void VolumeMeter::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void VolumeMeter::volumeChanged(float val)
{
  _volume.setLabel(QString("%1\n%2%").arg(_id).arg((int)(val * 100)));
}
void VolumeMeter::panChanged(float val)
{
  if (val == 50.0)
    _pan.setLabel(tr("center"));
  else {
    int lpan=(val <= 50) ? 100 : 100 * ((100.0 - val) / 50.0);
    int rpan=(val >= 50) ? 100 : 100 * (val / 50.0);
    _pan.setLabel(QString("%1% | %2%").arg(lpan).arg(rpan));
  }
}
void VolumeMeter::muteToggled(bool checked)
{
  if (!checked)
    _mute.setIcon(QIcon(QPixmap(":/listen")));
  else
    _mute.setIcon(QIcon(QPixmap(":/mute")));
}

void VolumeMeter::processBuffers(float *buf1, float *buf2, int size)
{
  if (_mute.isChecked()) {
    memset(buf1, 0, sizeof(float) * size);
    memset(buf2, 0, sizeof(float) * size);
    return;
  }
  float volume=_volume.getParamValue();
  float pan=_pan.getParamValue();
  float lpan=(pan <= 50) ? 1.0 : (100.0 - pan) / 50.0;
  float rpan=(pan >= 50) ? 1.0 : pan / 50.0;
  for (int i=0; i < size; i++) {
    buf1[i]*=volume * lpan;
    buf2[i]*=volume * rpan;
    if (_limit != -1) {
      buf1[i]=hard_clip(buf1[i], -_limit, _limit);
      buf2[i]=hard_clip(buf2[i], -_limit, _limit);
    }
    _vu.processLeftValue(buf1[i]);
    _vu.processRightValue(buf2[i]);
  }
}


// 
// volume_meter.cpp ends here
