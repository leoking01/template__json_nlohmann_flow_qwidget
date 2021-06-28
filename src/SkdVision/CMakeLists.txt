cmake_minimum_required(VERSION 3.5)

project(SkdVision   VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
if(0)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
endif()

add_definitions( -DUSING_CV_DEFINED_LK    )
add_definitions( -DUSING_HALCON_DEFINED_LK    )

#add_definitions( -DUSE_INTERFACE_CV_OR_CPP    )

if(MSVC)
    add_definitions( -DPLATFORM_MSVC        )
endif()

if(UNIX )
    #REQUIRED
    set(Opencv_rot_my   /home/alex/installCv3414Ubun2104FullNew  )
    set(OpenCV_DIR     ${Opencv_rot_my}/share/OpenCV     )
    find_package(   opencv    PATHS    ${Opencv_rot_my}/share/OpenCV    )
    include_directories(   ${Opencv_rot_my}/include
        ${Opencv_rot_my}/include/opencv
        ${Opencv_rot_my}/include/opencv2
        )
    link_directories( ${Opencv_rot_my}/lib )

    include_directories(     "/home/alex/halcon-19.11.0.0-linux/include/halconcpp"
        "/home/alex/halcon-19.11.0.0-linux/include"  )
    link_directories(   "/home/alex/halcon-19.11.0.0-linux/lib/x64-linux"  )
elseif(MSVC)
    #REQUIRED
    set(Opencv_rot_my   /home/alex/installCv3414Ubun2104FullNew  )
    set(OpenCV_DIR     ${Opencv_rot_my}/share/OpenCV     )
    find_package(   opencv    PATHS    ${Opencv_rot_my}/share/OpenCV    )
    include_directories(   ${Opencv_rot_my}/include
        ${Opencv_rot_my}/include/opencv
        ${Opencv_rot_my}/include/opencv2
        )
    link_directories( ${Opencv_rot_my}/lib )

    include_directories( "/home/alex/halcon-19.11.0.0-linux/include/halconcpp"
        "/home/alex/halcon-19.11.0.0-linux/include"  )
    link_directories( "/home/alex/halcon-19.11.0.0-linux/lib/x64-linux" )
endif()



if(0)
    find_package( nlohmann_json REQUIRED PATHS "../deps/Install_nlohman_json/lib/cmake/nlohmann_json")
    include_directories( ../deps/Install_nlohman_json/lib/cmake/nlohmann_json )
    include_directories( ../deps/fast-cpp-csv-parser )


    find_package( tinyxml2 REQUIRED PATHS "../deps/InstallTinyXml2/lib/cmake/tinyxml2" )
    include_directories( ../deps/InstallTinyXml2/include )
    link_directories(  ../deps/InstallTinyXml2/lib )

    include_directories( ../deps/fast-cpp-csv-parser )

    find_package(  glog  REQUIRED   PATHS    "../deps/InstallTinyXml2/lib/cmake/glog")
    include_directories( ../deps/InstallGlog/include )
    link_directories(  ../deps/InstallGlog/lib )
endif()


FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


#include_directories(     "/home/alex/halcon-19.11.0.0-linux/include/halconcpp"
#    "/home/alex/halcon-19.11.0.0-linux/include"  )
#link_directories(   "/home/alex/halcon-19.11.0.0-linux/lib/x64-linux"  )


aux_source_directory(   ./    sources_lst_my )
aux_source_directory(   ./BasicDef   sources_lst_my )

aux_source_directory(   ./algorithmsNaitive    sources_lst_my )

aux_source_directory(   ./algorithmsNaitive/imgSource    sources_lst_my )
aux_source_directory(   ./algorithmsNaitive/Locater    sources_lst_my )

aux_source_directory(   ./algorithmsNaitive/measure/fit    sources_lst_my )

aux_source_directory(   ./algorithmsNaitive/PreProc/oneImgProc    sources_lst_my )
aux_source_directory(   ./algorithmsNaitive/PreProc/filter    sources_lst_my )




include_directories( ./  ./BasicDef  )
#include_directories( ./TimeRecorder ./utility   )
include_directories(
    ./algorithmsNaitive
    ./algorithmsNaitive/imgSource
    ./algorithmsNaitive/Locater
    ./algorithmsNaitive/measure/fit
    ./algorithmsNaitive/PreProc/oneImgProc
    ./algorithmsNaitive/PreProc/filter
    )

set(HEADERS
    ./BasicDef/SKDVISION_global.h
    ./BasicDef/skd_vision_basic.h
    ./BasicDef/skd_vision_basic_cpp.h


    ./algorithmsNaitive/algorithmbaseNaitive.h


    ./algorithmsNaitive/imgSource/loadimage.h
    ./algorithmsNaitive/imgSource/api_imgSource.h


    ./algorithmsNaitive/Locater/templatematching.h


    ./algorithmsNaitive/measure/fit/fitterline.h
    ./algorithmsNaitive/measure/fit/fitline.h
    ./algorithmsNaitive/measure/fit/fitcircle.h


    ./algorithmsNaitive/PreProc/filter/filteraussian.h
    ./algorithmsNaitive/PreProc/filter/FilterGSobel.h
    ./algorithmsNaitive/PreProc/filter/filtermean.h
    ./algorithmsNaitive/PreProc/filter/filtermidean.h
    ./algorithmsNaitive/PreProc/oneImgProc/contourcanny.h
    ./algorithmsNaitive/PreProc/oneImgProc/findcontours.h
    ./algorithmsNaitive/PreProc/oneImgProc/HistEquat.h
    ./algorithmsNaitive/PreProc/oneImgProc/imgcvtcolor.h
    ./algorithmsNaitive/PreProc/oneImgProc/threashold.h
    ./algorithmsNaitive/PreProc/oneImgProc/thresholdotsu.h

   #    ./algorithmsNaitive/fitterline.h
    )
#set(FORMS   ./UI/widget.ui  )


if(UNIX )
    set(LIBS_RELATED       ${OpenCV_LIBS}
        libopencv_core.so   libopencv_highgui.so  libopencv_imgcodecs.so
        libopencv_imgproc.so   libopencv_videoio.so     libopencv_ml.so
        libopencv_features2d.so  libopencv_flann.so  libopencv_objdetect.so
        #    -lpng  -lthread -ljpeg  -lpng16
        #     nlohmann_json::nlohmann_json
        #     tinyxml2::tinyxml2
        #     glog::glog
        -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread   )
elseif(MSVC )
    set(LIBS_RELATED       ${OpenCV_LIBS}
        libopencv_core.so   libopencv_highgui.so  libopencv_imgcodecs.so
        libopencv_imgproc.so   libopencv_videoio.so     libopencv_ml.so
        libopencv_features2d.so  libopencv_flann.so  libopencv_objdetect.so
        #    -lpng  -lthread -ljpeg  -lpng16
        #     nlohmann_json::nlohmann_json
        #     tinyxml2::tinyxml2
        #     glog::glog
        -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread   )
endif()



add_library(SkdVision   SHARED
    #        main.cpp
    #    ${TS_FILES}
#    skd_vision_basic.c
#    skd_vision_basic_cpp.cpp
    ${sources_lst_my}  ${HEADERS}  ${FORMS}
    )


target_link_libraries(  SkdVision
    #  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    ${LIBS_RELATED}
    )

#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_compile_definitions(SkdVision PRIVATE SKDVISION_LIBRARY)

set(LIBRARY_OUTPUT_PATH   ${CMAKE_BINARY_DIR}/../bin   )
set(EXECUTABLE_OUTPUT_PATH   ${CMAKE_BINARY_DIR}/../bin   )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/../bin   )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY      ${CMAKE_BINARY_DIR}/../lib   )





#-------------------install  destation ---------------------------
#set( DESTINATION  "../install/")
set( CMAKE_INSTALL_PREFIX  "../install/")
#          And to the end of the top-level CMakeLists.txt we add:
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"  DESTINATION include  )









#
# Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format)
#

#add_clang_format_target()

#
# Install library for easy downstream inclusion
#

include(GNUInstallDirs)
install(
    TARGETS
    ${PROJECT_NAME}
    EXPORT
    ${PROJECT_NAME}Targets
    LIBRARY DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION
    ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION
    include
    PUBLIC_HEADER DESTINATION
    include
    )

install(
    EXPORT
    ${PROJECT_NAME}Targets
    FILE
    ${PROJECT_NAME}Targets.cmake
    NAMESPACE
    ${PROJECT_NAME}::
    DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

#
# Add version header
#

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in
    include/${PROJECT_NAME_LOWERCASE}/version.hpp
    @ONLY
    )

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME_LOWERCASE}/version.hpp
    DESTINATION
    include/${PROJECT_NAME_LOWERCASE}
    )

#
# Install the `include` directory
#

install(
    DIRECTORY
#    include/${PROJECT_NAME_LOWERCASE}
    interfaceA/${PROJECT_NAME_LOWERCASE}
    DESTINATION
    include
    )

#verbose_message("Install targets succesfully build. Install with `cmake --build <build_directory> --target install --config <build_config>`.")

#
# Quick `ConfigVersion.cmake` creation
#

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION
    ${PROJECT_VERSION}
    COMPATIBILITY
    SameMajorVersion
    )

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

#
# Generate export header if specified
#

if(${PROJECT_NAME}_GENERATE_EXPORT_HEADER)
    include(GenerateExportHeader)
    generate_export_header(${PROJECT_NAME})
    install(
        FILES
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME_LOWERCASE}_export.h
        DESTINATION
        include

        )

    message(STATUS "Generated the export header `${PROJECT_NAME_LOWERCASE}_export.h` and installed it.")
endif()

message(STATUS "Finished building requirements for installing the package.\n")

#
# Unit testing setup
#
if(  0 )
    if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
        enable_testing()
        message(STATUS "Build unit tests for the project. Tests should always be found in the test folder\n")
        add_subdirectory(test)
    endif()
endif()





