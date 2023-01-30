#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object3D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float height,
        float width, glm::vec3 color, bool fill = false);
    Mesh* CreateGrass(const std::string& name, glm::vec3 leftBottomCorner, float height,
        float width, glm::vec3 color, bool fill = false);
    Mesh* CreateRoad(std::vector<float> road_inside, std::vector<float> road_outside, glm::vec3 color);
    //std::vector<VertexFormat> vertices; 
    Mesh* CreateCar();
}
