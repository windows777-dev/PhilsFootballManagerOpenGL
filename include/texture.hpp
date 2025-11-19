#pragma once

#include <string>
#include "glad/glad.h"
#include "shader.hpp"

namespace Texture {

    class Texture2D {
    public:
        unsigned int texture;

        // Constructor: loads a texture from file
        Texture2D(const char* filePath, const char* fileType, Shader &shaderObject);

        // Bind texture to a texture unit
        void bind(unsigned int unit = 0) const;

        // Set shader uniform to use this texture
        void setShaderTexture(Shader &shaderObject, const std::string& uniformName, int unit);
    };

}
