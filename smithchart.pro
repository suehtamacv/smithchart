TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle qt

QMAKE_CXXFLAGS += -std=c++11 -fopenmp
QMAKE_LFLAGS += -std=c++11 -fopenmp
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

LIBS += -lboost_system -lboost_program_options -larmadillo

HEADERS += \
    include/GeneralClasses/Impedance.h \
    include/GeneralClasses/Admittance.h \
    include/MoebiusTranformations/MoebiusTransformation.h \
    include/MoebiusTranformations/SmithChartTransformation.h \
    include/GeneralClasses/Circle.h

SOURCES += \
    src/GeneralClasses/Impedance.cpp \
    src/GeneralClasses/Admittance.cpp \
    main.cpp \
    src/MoebiusTranformations/MoebiusTransformation.cpp \
    src/MoebiusTranformations/SmithChartTransformation.cpp \
    src/GeneralClasses/Circle.cpp

OTHER_FILES += \
    .astylerc
