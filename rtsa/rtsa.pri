################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
###################################################################

RTSA_ROOT = $$PWD

INCLUDEPATH += $${RTSA_ROOT}/include
DEPENDPATH  += $${RTSA_ROOT}/lib

HEADERS += \
    $${RTSA_ROOT}/include/wsaInterface.h \

win32: LIBS += -L$${RTSA_ROOT}/lib -lwsaInterface
win32: PRE_TARGETDEPS += $${RTSA_ROOT}/lib/wsaInterface.lib

