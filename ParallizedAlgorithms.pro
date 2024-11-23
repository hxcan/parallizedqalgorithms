#-------------------------------------------------
#
# Project created by QtCreator 2012-11-02T09:13:43
#
#-------------------------------------------------

QT       += gui 

TARGET = ParallizedAlgorithms
TEMPLATE = lib

DEFINES += PARALLIZEDALGORITHM_LIBRARY

SOURCES +=

HEADERS +=\
    GameType.h \
    PaGlobal.h \
    PaPreCompile.h \
    RangeSortSearch.h \
    PaComparator.h \
    CompareResultRelation.h \
    PaMapReduceFunctions.h \
    PaCompareResult.h \
    CompareWithComparatorMap.h \
    PickComparedDataReduce.h \
    PaComparePickResult.h \
    PaSignalProxy.h \
    PaSignalProxySolid.h

export_header_files.path=/usr/include
export_header_files.files+=GameType.h \
  Xy_global.h \
  LlPreCompile.h \
    GameInfo.h \
RangeSortSearch.h \
PaPreCompile.h \
PaComparator.h \
CompareResultRelation.h \
PaMapReduceFunctions.h \
PaCompareResult.h \
PaGlobal.h \
CompareWithComparatorMap.h \
PickComparedDataReduce.h \
PaComparePickResult.h \
PaSignalProxy.h \
PaSignalProxySolid.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target \
  export_header_files
}

CONFIG+=precompile_header

PRECOMPILED_HEADER+=PaPreCompile.h

TRANSLATIONS+=Xy.ts

VERSION = 2002.2024.8

QT+=concurrent

CONFIG += c++11
