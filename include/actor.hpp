#ifndef ACTOR_H
#define ACTOR_H

#include "glad/glad.h"  // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>  

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "stb_image.h"
#include "shader.hpp"


class Actor {
public:
    Shader shader;
    GLuint VAO, VBO, EBO;
    GLuint textureID;

    Actor(const char* textureFile, const char* fShader, const char* vShader)
        : shader(vShader, fShader)
    {
        // Quad vertices
        float vertices[] = {
            // positions       // colors        // tex coords
             0.5f,  0.5f, 0.0f,  1.0f,0.0f,0.0f,  1.0f,1.0f,
             0.5f, -0.5f, 0.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f,0.0f,
            -0.5f,  0.5f, 0.0f,  1.0f,1.0f,0.0f,  0.0f,1.0f
        };
        unsigned int indices[] = { 0,1,2, 0,2,3 };

        // VAO/VBO/EBO setup
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);

        // Texture setup
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture\n";
        }
        stbi_image_free(data);

        glBindVertexArray(0); // unbind
    }

    void draw() {
        shader.use();
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};




#endif