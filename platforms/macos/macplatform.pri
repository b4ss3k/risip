##################################################################################
#    Copyright (C) 2016 - 2017 Petref Saraci
#    http://risip.io
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You have received a copy of the GNU General Public License
#    along with this program. See LICENSE.GPLv3
#    A copy of the license can be found also here <http://www.gnu.org/licenses/>.
#
###################################################################################

message("Running the mac-platform settings!")

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13

CONFIG += app_bundle

QMAKE_MAC_SDK = macosx10.12
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13
QMAKE_CXXFLAGS += -mmacosx-version-min=10.13
QMAKE_LFLAGS += -mmacosx-version-min=10.13

INCLUDEPATH += $$PWD/pjsip/include

# static linking with PJSIP
LIBS += -L$$PWD/pjsip/staticlibs \
    -lpjsua2-x86_64-apple-darwin17.2.0 \
    -lpjsua-x86_64-apple-darwin17.2.0 \
    -lpjsip-simple-x86_64-apple-darwin17.2.0 \
#    -lpjsdp-x86_64-apple-darwin17.2.0 \
    -lwebrtc-x86_64-apple-darwin17.2.0 \
    -lpjmedia-x86_64-apple-darwin17.2.0 \
    -lpjsip-x86_64-apple-darwin17.2.0 \
    -lpjmedia-audiodev-x86_64-apple-darwin17.2.0 \
    -lpjsip-ua-x86_64-apple-darwin17.2.0 \
    -lpjnath-x86_64-apple-darwin17.2.0 \
    -lpjmedia-x86_64-apple-darwin17.2.0 \
    -lpj-x86_64-apple-darwin17.2.0 \
    -lpjmedia-x86_64-apple-darwin17.2.0 \
    -lpjmedia-codec-x86_64-apple-darwin17.2.0 \
    -lpjmedia-videodev-x86_64-apple-darwin17.2.0 \
    -lilbccodec-x86_64-apple-darwin17.2.0 \
    -lgsmcodec-x86_64-apple-darwin17.2.0 \
    -lspeex-x86_64-apple-darwin17.2.0 \
    -lresample-x86_64-apple-darwin17.2.0 \
    -lsrtp-x86_64-apple-darwin17.2.0 \
    -lpjlib-util-x86_64-apple-darwin17.2.0 \
    -lg7221codec-x86_64-apple-darwin17.2.0 \
    -framework CoreAudio \
    -framework AudioToolbox \
    -framework AudioUnit

# dynamic linking with PJSIP
#LIBS += -L$$PWD../../macos-64/dylibs \
#    -lpjsua2 \
#    -lpjsua \
#    -lpjsip-ua \
#    -lpjsip-simple \
#    -lpjsip \
##    -lpjsdp \
#    -lpjmedia \
#    -lpjmedia-audiodev \
#    -lpjmedia \
#    -lpjmedia-codec \
#    -lpj \
#    -lpjnath \
#    -lilbccodec \
#    -lgsmcodec \
#    -lspeex \
#    -lresample \
#    -lsrtp \
#    -lpjlib-util \
#    -lg7221codec \
