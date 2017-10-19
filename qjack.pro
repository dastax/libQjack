TEMPLATE    = lib

SOURCES     = jack_client.cpp \
presetbox.cpp \
vumeter.cpp \
volume_meter.cpp \
osc.cpp \
timebase_widget.cpp \
metronom.cpp \
audio_tools.cpp \
midi_widgets.cpp 

HEADERS     = jack_client.h \
vumeter.h \
volume_meter.h \
midi_widgets.h \
osc.h \
timebase_widget.h \
metronom.h \
audio_tools.h \
presetbox.h \
libqjack.h

INCLUDEPATH += /usr/include/
INCLUDEPATH += /usr/local/include/

LIBS += -ljack  

QT += xml

headers.path = /usr/include/libqjack/
headers.files = ./*.h

target.path += /usr/lib/
INSTALLS += target
INSTALLS += headers

RESOURCES= resources_qjack.qrc

CONFIG += release staticlib

DESTDIR=bin
MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

