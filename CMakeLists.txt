cmake_minimum_required(VERSION 2.8)
project(wifi)

find_package(qibuild)

FILE(GLOB_RECURSE INC_ALL "*.h")

SET(CMAKE_CXX_FLAGS "-std=gnu++11")

set(_srcs
 "config.cpp"
 "main.cpp"
 "menu.cpp"
 "menucontrol.cpp"
 "wifi.cpp"
 "wifimanager.cpp"
 "wifiservice.cpp"
 "wifistate.cpp"
 "eventhandler.cpp"
 ${INC_ALL}
)

option(MYMODULE_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  ON)


if(MYMODULE_IS_REMOTE)
  add_definitions( " -DMYMODULE_IS_REMOTE ")
  qi_create_bin(wifi ${_srcs})

else()
  qi_create_lib(wifi SHARED ${_srcs} SUBFOLDER naoqi)
endif()


qi_use_lib(wifi ALCOMMON ALPROXIES)
