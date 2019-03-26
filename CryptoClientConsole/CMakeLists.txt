cmake_minimum_required(VERSION 3.12)
project(CryptoClientConsole)
set(APP_NAME CryptoConsole)

find_package(EasyCrypto REQUIRED)

add_executable(${APP_NAME} main.cpp)

set_target_properties(${APP_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${APP_NAME} PROPERTIES DEFINE_SYMBOL "EC_DLL")
target_include_directories(${APP_NAME} PUBLIC ${EasyCrypto_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} EasyCrypto::EasyCrypto)

