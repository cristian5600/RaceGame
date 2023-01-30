#include "object3D.h"

#include <vector>
#include <iostream>
#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object3D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width , 0, 0), color),
        VertexFormat(corner + glm::vec3(width , 0, height), color),
        VertexFormat(corner + glm::vec3(0, 0, height), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
};
Mesh* object3D::CreateGrass(const std::string& name, glm::vec3 leftBottomCorner, float height,
    float width, glm::vec3 color, bool fill )
{   
    int count = 0;
    float size = 0.2;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 corner = glm::vec3(-200/2,0,-200/2);
    for (int i = 2; i < 1000; i++) {
        for (int j = 2; j < 1000; j++) {
            vertices.push_back(VertexFormat(corner + glm::vec3(size*(i-1), -0.1, size*(j-1)), color));
            vertices.push_back(VertexFormat(corner + glm::vec3(size*i, -0.1, size * (j - 1)), color));
            vertices.push_back(VertexFormat(corner + glm::vec3(size*i, -0.1, size*j), color));
            vertices.push_back(VertexFormat(corner + glm::vec3(size * (i - 1), -0.1, size*j), color));
            indices.push_back(count);
            indices.push_back(count+1);
            indices.push_back(count+2);
            indices.push_back(count + 3);
            indices.push_back(count);
            indices.push_back(count+2);
            count = count + 4;
        }
   }

    Mesh* grass = new Mesh(name);
    grass->InitFromData(vertices, indices);
    return grass;
    
}
Mesh* object3D::CreateRoad(std::vector<float> road_inside, std::vector<float> road_outside , glm::vec3 color) {
    Mesh* road = new Mesh("road");
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    int count = 0;
    for (int i = 0; i < road_inside.size(); i++) { // make road larger and wider
        road_inside[i] *= 2;
        road_outside[i] *= 3;
    }
    for ( int i = 0; i < road_inside.size() -4  ; i=i+2) { 
        
        vertices.push_back(VertexFormat(glm::vec3(road_inside[i],0.1,road_inside[i+1]), color));
        vertices.push_back(VertexFormat(glm::vec3(road_inside[i+2], 0.1, road_inside[i + 3]), color));
        vertices.push_back(VertexFormat(glm::vec3(road_outside[i], 0.1, road_outside[i + 1]), color));
        vertices.push_back(VertexFormat(glm::vec3(road_outside[i + 2], 0.1, road_outside[i + 3]), color));
        indices.push_back(count);
        indices.push_back(count + 1);
        indices.push_back(count + 2);
        indices.push_back(count + 2);
        indices.push_back(count+3);
        indices.push_back(count + 1);
        count = count + 4;
        std::cout << std::endl<<i << " "<< road_outside[i + 2];
        
    }
    // end the road
    count = count - 4;
    indices.push_back(count+1);
    indices.push_back(count+3);
    indices.push_back(0);
    indices.push_back(0);

    indices.push_back(2);
    indices.push_back(count + 3);

    road->InitFromData(vertices, indices);
    return road;
}
Mesh* object3D::CreateCar(){
    std::vector<VertexFormat> vertices =
    {
        // VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(0,0,1.5),glm::vec3(0, 0.12, 1), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(1,0,1.5),glm::vec3(1, 0.3, 0.243), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(0,1,1.5),glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(1,1,1.5),glm::vec3(0.4, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(0,0,0),glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(1,0,0),glm::vec3(0, 1, 0.43), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(0,1,0),glm::vec3(0.3, 1, 0.32), glm::vec3(0.2, 0.8, 0.6)),
         VertexFormat(glm::vec3(1,1,0),glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
         // TODO(student): Complete the vertices data for the cube mesh

    };

    std::vector <unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
        1, 3, 2, // indices for second triangle
        // TODO(student): Complete indices data for the cube mesh
        2,3,7,
        2,7,6,
        1,7,3,
        1,5,7,
        6,7,4,
        7,5,4,
        0,4,1,
        1,4,5,
        2,6,4,
        0,2,4,
    };
    Mesh* car = new Mesh("car");
    car->InitFromData(vertices, indices);
    return car;
}
