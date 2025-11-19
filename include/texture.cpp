#include "texture.hpp"


#include "texture.hpp"
#include "stb_image.h"
#include <iostream>

namespace Texture {

    Texture2D::Texture2D(const char* filePath, const char* fileType, Shader &shaderObject) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Wrapping & filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
        if (data && std::string(fileType) == "jpg") {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else if (data && std::string(fileType) == "png") {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
        }

        stbi_image_free(data);
        std::cout << "Loaded Texture: " << filePath << std::endl;
    }

    void Texture2D::bind(unsigned int unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void Texture2D::setShaderTexture(Shader &shaderObject, const std::string& uniformName, int unit) {
        shaderObject.use();
        shaderObject.setInt(uniformName, unit);
        std::cout << "Initialised Texture Shader uniform: " << uniformName << std::endl;
    }

}
