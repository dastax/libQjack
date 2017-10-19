#include <math.h>
#include "vumeter.h"

Vu::Vu()
{
  setMinimumSize(10, 10);
  setOrientation(Qt::Vertical);
  setRange(0, 100);
  _peak=0;
  setValue(50);
}
void Vu::setOrientation(Qt::Orientation o)
{
  QProgressBar::setOrientation(o);
  if (o != Qt::Vertical)
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
  else
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}
void Vu::reset()
{
  setPeak(0);
}
void Vu::refresh()
{
  setPeak(_peak);
  _peak=0;
}
void Vu::setPeak(float peak)
{
  setValue((int)getDbPercent(getDbVal(peak)));
}
void Vu::processValue(float val)
{
  float vuval;
  
  vuval=fabs(val);
  if (vuval > _peak)
    _peak=vuval;
}
void Vu::processBuffer(float *buf, int size)
{
  for (int i=0; i < size; i++)
    processValue(buf[i]);
}
void Vu::paintEvent(QPaintEvent *event)
{
  QRect rect=event->rect();
    
  QPalette p=palette(); 
  QPainter painter(this);
  QRectF r;
  painter.setBrush(Qt::black);
  painter.fillRect(rect, painter.brush());
  float evol=(float)value() / (float)maximum();
  Qt::Orientation ori=orientation();
  int _brickResolution;
  float brickHeight, brickWidth;
  if (ori == Qt::Vertical) {
    _brickResolution=height() / 3;
    brickWidth=width() - 2;
    brickHeight=3;//(float)height() / (float)_brickResolution;
  }
  else {
    _brickResolution=width() / 3;
    brickHeight=height() - 2;
    brickWidth=3;//(float)width() / (float)_brickResolution;
  }
  int brickCount=(int)(evol * _brickResolution);
  QColor color(0, 255, 0);
  int red, green;
  int step=255 / _brickResolution;
  green=color.green();
  red=0;

  for (int i=0; i < brickCount; i++)
  {
    color.setGreen(green);
    color.setRed(red);
    painter.setBrush(QBrush(color));
    if (ori == Qt::Vertical)
      r.setRect(1, (height()-brickHeight*(i+1)+1), brickWidth, brickHeight - 1);
    else
      r.setRect(brickWidth * i, 1, brickWidth - 1, brickHeight);

    painter.fillRect(r, painter.brush());
    red+=step;
    green-=step;
  }  
}

//
MeterStrip::MeterStrip()
{
  setMinimumSize(30, 30);
  _orientation=Qt::Vertical;
}

void MeterStrip::paintEvent(QPaintEvent *event)
{
  QRect rect=event->rect();
    
  QPalette p=palette(); 
  QPainter painter(this);
  int  db_points[] = {-60, -50, -40, -30, -20, -15, -10, -5, 0, 4, 6};
  //painter.setBrush(QColor(71, 71, 71));
  //painter.fillRect(rect, painter.brush());
  //painter.setPen(Qt::white);
  QFont ft("Times");
  ft.setPixelSize(9);
  painter.setFont(ft);
  int pos;
  for (uint i=0; i < sizeof (db_points)/sizeof (db_points[0]); i++) {
    if (_orientation == Qt::Vertical) {
      pos=(int)(height() - (height() * (getDbPercent(db_points[i])/100)));
      if (db_points[i] > 0)
	painter.drawText(2, pos, QString("+%1").arg(db_points[i]));
      else
	painter.drawText(2, pos, QString("%1").arg(db_points[i]));
    }
    else {
      pos=(int)(width() * (getDbPercent(db_points[i])/100));
      if (db_points[i] > 0)
	painter.drawText(pos, 10, QString("+%1").arg(db_points[i]));
      else
	painter.drawText(pos, 10, QString("%1").arg(db_points[i]));
    }
  }
}

//
VuMeter::VuMeter()
{
  QHBoxLayout *lo=new QHBoxLayout;
  lo->addWidget(&_vu);
  lo->addWidget(&_meter);
  lo->setContentsMargins(0, 0, 0, 0);
  setLayout(lo);
}
VuMeter::~VuMeter()
{
  delete layout();
}
void VuMeter::setOrientation(Qt::Orientation o)
{
  delete layout();
  _vu.setOrientation(o);
  _meter.setOrientation(o);
  if (o == Qt::Vertical) {
    QHBoxLayout *lo=new QHBoxLayout;
    lo->addWidget(&_vu);
    lo->addWidget(&_meter);
    lo->setContentsMargins(0, 0, 0, 0);
    setLayout(lo);
  }
  else {
    QVBoxLayout *lo=new QVBoxLayout;
    lo->addWidget(&_vu);
    lo->addWidget(&_meter);
    lo->setContentsMargins(0, 0, 0, 0);
    setLayout(lo);
  }
}

//
StereoVuMeter::StereoVuMeter()
{
  QHBoxLayout *lo=new QHBoxLayout;
  lo->addWidget(&_vuLeft);
  lo->addWidget(&_vuRight);
  lo->addWidget(&_meter);
  lo->setContentsMargins(0, 0, 0, 0);
  setLayout(lo);
}
StereoVuMeter::~StereoVuMeter()
{
  delete layout();
}
void StereoVuMeter::setOrientation(Qt::Orientation o)
{
  delete layout();
  _vuLeft.setOrientation(o);
  _vuRight.setOrientation(o);
  _meter.setOrientation(o);
  if (o == Qt::Vertical) {
    QHBoxLayout *lo=new QHBoxLayout;
    lo->addWidget(&_vuLeft);
    lo->addWidget(&_vuRight);
    lo->addWidget(&_meter);
    lo->setContentsMargins(0, 0, 0, 0);
    setLayout(lo);
  }
  else {
    QVBoxLayout *lo=new QVBoxLayout;
    lo->addWidget(&_vuLeft);
    lo->addWidget(&_vuRight);
    lo->addWidget(&_meter);
    lo->setContentsMargins(0, 0, 0, 0);
    setLayout(lo);
  }
}
