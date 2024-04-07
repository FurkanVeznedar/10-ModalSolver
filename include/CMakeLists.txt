project(ModalSolver)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(core
    OpenGLCore/VertexBuffer.cpp
    OpenGLCore/IndexBuffer.cpp
    OpenGLCore/VertexArray.cpp
    OpenGLCore/Shader.cpp
    OpenGLCore/Renderer.cpp
    OpenGLCore//Texture.cpp
    stb_image/stb_image.cpp)