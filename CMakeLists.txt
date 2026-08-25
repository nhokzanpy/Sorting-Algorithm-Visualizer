cmake_minimum_required(VERSION 3.19)
project(SortingVisualizer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(SortingVisualizer
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    models/sortingstatistics.h
    models/sortingstep.h
    algorithms/bubblesort.h
    algorithms/bubblesort.cpp
    widgets/sortingvisualizer.h
    widgets/sortingvisualizer.cpp
    pages/visualizerpage.h
    pages/visualizerpage.cpp
    algorithms/selectionsort.h
    algorithms/selectionsort.cpp
    algorithms/insertionsort.h
    algorithms/insertionsort.cpp
    widgets/statisticspanel.h
    widgets/statisticspanel.cpp
    widgets/controlspanel.h
    widgets/controlspanel.cpp
    algorithms/mergesort.h
    algorithms/mergesort.cpp
    models/benchmarkresult.h
    benchmark/benchmarkrunner.h
    benchmark/benchmarkrunner.cpp
    widgets/benchmarkpanel.h
    widgets/benchmarkpanel.cpp
    models/studentsortresult.h
    student/studentsortrunner.h
    student/studentsortrunner.cpp
    widgets/studentpanel.h
    widgets/studentpanel.cpp
    models/multisizebenchmarkresult.h
    benchmark/multisizebenchmarkrunner.h
    benchmark/multisizebenchmarkrunner.cpp
    widgets/multisizebenchmarkpanel.h
    widgets/multisizebenchmarkpanel.cpp

)

target_link_libraries(SortingVisualizer
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS SortingVisualizer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SortingVisualizer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
