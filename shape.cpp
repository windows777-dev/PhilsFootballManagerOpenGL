#include "shape.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"


namespace Shape {

    Cube::Cube(glm::vec3 position)
    {

        float angle = 0.0f ;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);


    }

    void Cube::render(glm::mat4 model, int modelLoc)
    {
        
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        glUniformMatrix4fv(modelLoc, 1 ,GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);


    }

}