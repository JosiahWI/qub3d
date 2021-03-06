#
#	 Copyright (C) 2018 Qub³d Engine Group.
#	 All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification,
#  are permitted provided that the following conditions are met:
# 
#  1. Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer.
#  
#  2. Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation and/or
#  other materials provided with the distribution.
#  
#  3. Neither the name of the copyright holder nor the names of its contributors
#  may be used to endorse or promote products derived from this software without
#  specific prior written permission.
#  
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Use this version because it adds some options that we use.
cmake_minimum_required(VERSION 3.0)

project(sandblox-server)

# Set include, library, and source directories.

set(libdeps ${CMAKE_CURRENT_LIST_DIR}/../libdeps)

set(source_dir ${PROJECT_SOURCE_DIR}/source/src)
set(headers_dir ${PROJECT_SOURCE_DIR}/source/include)

set(server_sources
  ${source_dir}/main.cpp
)

set(server_headers

)

if(APPLE)
  message(STATUS "Including SDL2 dependency frameworks for macOS")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework CoreAudio -framework AudioToolbox -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework ForceFeedback -framework IOKit -framework Carbon -framework AppKit -framework OpenGL -liconv")
endif()# APPLE

set(include_dirs
        ${libdeps}/SDL2/include
        ${libdeps}/yaml-cpp/include
	${libdeps}/../renderer/source/include
        ${source_dir}/../include
)

set(library_dirs
    glew_s
    yaml-cpp
    SDL2-static
    SDL2main
    Viking
)

if (UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
	find_package(Threads REQUIRED)
	list(APPEND library_dirs
		${CMAKE_DL_LIBS}
	        ${CMAKE_THREAD_LIBS_INIT}
        	${X11_LIBRARIES}
       		${X11_Xxf86vm_LIB}
       		GL
	)
endif()

if(WIN32)
	list(APPEND library_dirs 
		${library_dirs}
		imm32.lib
		ole32.lib
		oleaut32.lib
		opengl32.lib
		version.lib
		winmm.lib
    )
endif()# WIN32


# Link the "SandBlox" binary.

set(EXECUTABLE_OUTPUT_PATH ../../COMPILE/bin)

add_executable(${PROJECT_NAME} ${server_sources} ${server_headers})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

include_directories(${include_dirs})
target_link_libraries(${PROJECT_NAME} ${library_dirs})

# Install it system-wide. (Invoked by `sudo make install`)
if (UNIX)
  install(
    TARGETS sandblox-server
    RUNTIME DESTINATION /usr/bin
  )
endif()
