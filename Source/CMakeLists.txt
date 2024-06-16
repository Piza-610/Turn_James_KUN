cmake_minimum_required(VERSION 2.8.3)
project( Turn_The_Neck )
set(SOURCE_FILE main.cpp  Motor.cpp Camera.cpp)

# OpenCVのビルド環境の設定ファイルを読み込む
find_package(OpenCV REQUIRED)

# WiringPiの設定
find_package(PkgConfig REQUIRED)
pkg_check_modules(WIRINGPI REQUIRED wiringpi)

# OpenCV関係のインクルードディレクトリのパスを設定
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${WIRINGPI_INCLUDE_DIRS}
)

# 実行ファイル名を設定
add_executable(main
    ${SOURCE_FILE}
)

# リンクするライブラリを読み込む
target_link_libraries(main
    ${OpenCV_LIBS}
    ${WIRINGPI_LIBRARIES}
)

