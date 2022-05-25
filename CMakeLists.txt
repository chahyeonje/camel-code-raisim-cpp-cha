cmake_minimum_required(VERSION 3.5)
project(camel-code-raisim-cpp)

#==
# Dependencies
#==
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets)
find_package(raisim CONFIG REQUIRED)
find_package(Eigen3 REQUIRED HINTS ${Eigen3_HINT})

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../raisim/win32/mt_release/bin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../raisim/win32/mt_debug/bin")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../rsc" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../rsc" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
else()
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../rsc" DESTINATION ${CMAKE_BINARY_DIR}/camel-code-raisim-cpp)
endif()

include_directories ( ${EIGEN3_INCLUDE_DIRS} )

#==
# Build Targets
#==

function(create_executable app_name file_name)
    add_executable(${app_name} ${file_name})
    set_target_properties(${app_name} PROPERTIES MACOSX_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/../raisim/mac/lib")
    if(WIN32)
        target_link_libraries(${app_name} PUBLIC raisim::raisim Ws2_32 Winmm)
        target_compile_options(${app_name} PRIVATE "/MP")
    else()
        target_link_libraries(${app_name} PUBLIC raisim::raisim pthread)
    endif()

    if(APPLE)
        execute_process(COMMAND sysctl -q hw.optional.arm64
                OUTPUT_VARIABLE _sysctl_stdout
                ERROR_VARIABLE _sysctl_stderr
                RESULT_VARIABLE _sysctl_result
                )
        if(_sysctl_result EQUAL 0 AND _sysctl_stdout MATCHES "hw.optional.arm64: 1")
            target_compile_options(${app_name} PRIVATE -mcpu=apple-m1)
        endif()
    endif()

    target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endfunction()

create_executable(camel-rmdx8test_torque src/Test/Test_RMDX8Pro.cpp)

# if you try to include any Qt UI CLASS, you must have to add following two sentences.


add_executable(camel-simplePendulum src/SimplePendulum/SimplePendulumSimulation.cpp include/SimulationUI/simulationMainwindow.cpp include/SimulationUI/qcustomplot.cpp src/SimplePendulum/SimplePendulumPDController.cpp src/SimplePendulum/SimplePendulumRobot.cpp)
target_link_libraries(camel-simplePendulum Qt5::Widgets raisim::raisim pthread)

add_executable(camel-a1 src/A1/A1Simulation.cpp src/A1/A1Robot.cpp src/A1/A1Robot.h src/A1/A1JointPDController.cpp src/A1/A1JointPDController.h include/SimulationUI/simulationMainwindow.cpp include/SimulationUI/qcustomplot.cpp)
target_link_libraries(camel-a1 Qt5::Widgets raisim::raisim pthread)

add_executable(camel-single-leg-sim src/CAMEL-Quad-SingleLeg/SingleLeggedSimulation.cpp src/CAMEL-Quad-SingleLeg/SingleLeggedPDController.cpp src/CAMEL-Quad-SingleLeg/SingleLeggedRobot.cpp include/SimulationUI/simulationMainwindow.cpp include/SimulationUI/qcustomplot.cpp)
target_link_libraries(camel-single-leg-sim Qt5::Widgets raisim::raisim pthread)

add_executable(camel-rmd8xoperation src/RMDX8PRO/RMDX8ProOperation.cpp src/RMDX8PRO/mainwindow.cpp src/RMDX8PRO/qcustomplot.cpp)
target_link_libraries(camel-rmd8xoperation Qt5::Widgets raisim::raisim pthread)

add_executable(camel-single-leg-operation src/CAMEL-Quad-SingleLeg-Operation/SingleLeggedOperation.cpp src/CAMEL-Quad-SingleLeg-Operation/SingleLeggedRobotOperation.cpp src/CAMEL-Quad-SingleLeg-Operation/SingleLegCAN.cpp src/CAMEL-Quad-SingleLeg-Operation/mainwindow.cpp src/CAMEL-Quad-SingleLeg-Operation/qcustomplot.cpp src/CAMEL-Quad-SingleLeg-Operation/SingleLegCAN.cpp)
target_link_libraries(camel-single-leg-operation Qt5::Widgets raisim::raisim pthread)