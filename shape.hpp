#include "stdlib.h"
#include "stdio.h"
#include "iostream"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"


namespace Shape {

    class Triangle {

        public:

        Triangle(const int PointA, const int PointB, const int PointC);

    };

    class Cube {

        public:

        float angle;



        Cube(glm::vec3 position); // Forget about verticies because they will make the parameters look ridiculous

        void render(glm::mat4 model, int modelLoc);

    };

    

    class Circle {

        public:

        Circle(const int radius);

    };

}


