project(SDLwithOpenGLES)

set(ARM_OPENGLES_PATH CACHE PATH "Arm OpenGLES Library path.")

include_directories(${ARM_OPENGLES_PATH}/include)
link_directories(${ARM_OPENGLES_PATH})

include_directories(3rd/SDL/include)

add_subdirectory(3rd/SDL)
add_subdirectory(src)

