# libQjack
A Qt4 lib wrapper for jack audio api

This library is used in many of my audio projects.
It's purpose is to wrap the jack client api into a Qt4 Object, with signals/slots facilities

It also comes with some widgets like midi-learn able QPushButton, QDial, QComboBox ...
And also a preset manager widget ...

It's not documented yet, but the code speaks ; )

To compile: you need to have libqt4-dev and libjack-jackd2-dev installed
then in the source directory type
make
sudo make install
