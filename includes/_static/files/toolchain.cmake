set(CMAKE_SYSTEM_NAME Linux)

if(EXISTS ${CMAKE_SYSROOT} AND IS_DIRECTORY ${CMAKE_SYSROOT})
  execute_process(COMMAND file ${CMAKE_SYSROOT}/bin/bash.bash
		  OUTPUT_VARIABLE TARGET_BASH_OUTPUT)
  if(TARGET_BASH_OUTPUT MATCHES aarch64)
    message(STATUS "Setting architecture to aarch64")
    set(CMAKE_SYSTEM_PROCESSOR aarch64)
    set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} " CACHE STRING "" FORCE )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} " CACHE STRING "" FORCE )
  else()
    message(STATUS "Setting architecture to arm")
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-psabi" CACHE STRING "" FORCE )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi" CACHE STRING "" FORCE )
  endif()
else()
  message(FATAL_ERROR "ERROR: SYSROOT '${CMAKE_SYSROOT}' not found!!!")
endif()

 if(CMAKE_BUILD_TYPE MATCHES Debug)
    # Debug flags
    message("Enabling Debug build")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
else()
    # Enable compiler optimization flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")

    # Strip debug symbols
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${CMAKE_SYSROOT}/usr/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SYSROOT}/usr/lib")

set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/usr/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")

set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_SYSROOT}/usr/lib/libstdc++.so")

set(NODEJS_INCLUDE_DIR /usr/include/node) # make sure that nodejs is installed. If not, sudo apt-get install nodejs-dev

set(PYTHON_INCLUDE_DIRS "${CMAKE_SYSROOT}/usr/include/python3.10")
set(PYTHON_LIBRARIES "${CMAKE_SYSROOT}/usr/lib/libpython3.10.so")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
