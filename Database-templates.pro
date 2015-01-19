TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cAddressBook.cpp \
    cContactCard.cpp

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    database.xml \
    Database-templates.pro.user

HEADERS += \
    cAddressBook.h \
    cContactCard.h \
    main.h

