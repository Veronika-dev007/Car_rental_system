#-------------------------------------------------
#
# Project created by QtCreator 2023-05-06T12:13:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = car_rental_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    car.cpp \
    carmodel.cpp \
    formcar.cpp \
    formcustomer.cpp \
    customermodel.cpp \
    customer.cpp \
    formrent.cpp \
    rentmodel.cpp \
    rent.cpp \
    calculationfacade.cpp \
    calcfactory.cpp \
    abstractcalc.cpp \
    sedancalcfactory.cpp \
    sedancalc.cpp \
    limousinecalcfactory.cpp \
    offroadcarcalcfactory.cpp \
    minivancalcfactory.cpp \
    offroadcarcalc.cpp \
    minivancalc.cpp \
    limousinecalc.cpp \
    reportmodel.cpp

HEADERS  += mainwindow.h \
    car.h \
    carmodel.h \
    formcar.h \
    formcustomer.h \
    customermodel.h \
    customer.h \
    formrent.h \
    rentmodel.h \
    rent.h \
    calculationfacade.h \
    calcfactory.h \
    abstractcalc.h \
    sedancalcfactory.h \
    sedancalc.h \
    limousinecalcfactory.h \
    offroadcarcalcfactory.h \
    minivancalcfactory.h \
    offroadcarcalc.h \
    minivancalc.h \
    limousinecalc.h \
    reportmodel.h

FORMS    += mainwindow.ui \
    formcar.ui \
    formcustomer.ui \
    formrent.ui
