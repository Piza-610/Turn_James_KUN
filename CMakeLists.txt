cmake_minimum_required(VERSION 2.8.3)
project( Turn_The_Neck )
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp  Motor.cpp Camera.cpp)

# OpenCVのビルド環境の設定ファイルを読み込む
find_package(OpenCV REQUIRED)

# WiringPiの設定
find_package(PkgConfig REQUIRED)
# pkg_check_modules(WIRINGPI REQUIRED wiringpi)

# インクルードディレクトリを設定
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    /home/piza67/WiringPi/wiringPi
)

# 実行ファイル名を設定
add_executable(main
    ${SOURCE_FILES}
)

# リンクするライブラリを読み込む
target_link_libraries(main
    ${OpenCV_LIBS}
    wiringPi
)

# コンパイルオプションを設定
# add_definitions(-std=c++0x -L/home/pi/wiringPi/wiringPi -lwiringPi )