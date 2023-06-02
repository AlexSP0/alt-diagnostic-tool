find_package(Qt5 REQUIRED COMPONENTS Widgets Core DBus)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (HEADERS
    adtexecutable.h
    adtcheck.h
    adtresolver.h

    adtjsonconverter.h
    alteratorexecutordbusinterface.h
    adtjsonloader.h

    treemodelbuilderinterface.h
    treemodel.h
    treeitem.h
    treemodelbuilderimpl.h
)

set (SOURCES
    adtexecutable.cpp
    adtcheck.cpp
    adtresolver.cpp

    adtjsonconverter.cpp
    adtjsonloader.cpp

    treemodelbuilderinterface.cpp
    treemodel.cpp
    treeitem.cpp
    treemodelbuilderimpl.cpp
)

ADD_LIBRARY(adtcore STATIC ${SOURCES} ${HEADERS})
target_link_libraries(adtcore PRIVATE Qt5::Core Qt5::DBus Qt5::Widgets)
