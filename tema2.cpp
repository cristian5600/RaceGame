#include "lab_m1/Tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/Tema2/transform3D.h"
#include "lab_m1/Tema2/object3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;
    rotate = -2 * 0.01 * 0.2;
    camera = new implemented2::Camera();
     camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    polygonMode = GL_FILL;
    cout << road_outside[1] << endl << road_inside.size();

    {
       // Mesh* mesh = object3D::CreateSquare("cristi", glm::vec3(1, 0.1, 0), 3, 4, glm::vec3(0.2, 0.3, 0.6), true);
        //AddMeshToList(mesh);

    }
    {
        Mesh* grass = object3D::CreateGrass("iarba", glm::vec3(0, 0, 0), 1, 1, glm::vec3(0.2, 0.9, 0.5), true);
        AddMeshToList(grass);
    }
    {
        Mesh* road = object3D::CreateRoad(road_inside, road_outside, glm::vec3(0.7, 0.122231, 0.5));
        AddMeshToList(road);
    }
    {
        Mesh* car = object3D::CreateCar();
        AddMeshToList(car);
    }

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;





    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}
void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
} 
void Tema2::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    //RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    //RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    //RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    RenderMesh(meshes["cristi"], shaders["VertexNormal"], modelMatrix);

    RenderMesh(meshes["iarba"], shaders["VertexColor"], modelMatrix);
    RenderMesh(meshes["road"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform3D::Translate(camera->position.x + 5*camera->forward.x,
        camera->position.y + 5 * camera->forward.y,
        camera->position.z + 5 * camera->forward.z);

    modelMatrix *= transform3D::RotateOY(rotate);
    RenderMesh(meshes["car"], shaders["VertexColor"], modelMatrix);


    // make "trees"
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(11.05f, 0.5f, 9.8f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(5.31f, 0.5f, -3.64f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-3.8f, 0.5f, 10.66f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    //upper

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(11.05f,1.5f, 9.8f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(5.31f,1.5f, -3.64f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-3.8f, 1.5f, 10.66f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 1.5f, -1.5f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 1.5f, -1.5f);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);


}

void Tema2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

  //  DrawCoordinateSystem();
    RenderScene();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport



   // DrawCoordinateSystem();
    RenderScene();

    cout << endl<< camera->forward <<" X "<<camera->position;
}

void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->MoveForward(deltaTime * 2*cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
           // camera->TranslateRight(-deltaTime * cameraSpeed);
            camera->RotateThirdPerson_OY(4 * 0.01 * 0.2);
            rotate += 4 * 0.01 * 0.2;
            //camera->RotateThirdPerson_OY(4 * 0.01 * 0.2);
           // camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
          //  camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->MoveForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->RotateThirdPerson_OY(-4 * 0.01 * 0.2);
            rotate += -4 * 0.01 * 0.2;
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(+deltaTime * cameraSpeed);
        }
    }
    // TODO(student): Add transformation logic
    if (window->KeyHold(GLFW_KEY_D)) {
        translateX += deltaTime * 10;
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        translateX += -deltaTime * 10;
    }
    if (window->KeyHold(GLFW_KEY_R)) {
        translateY += deltaTime * 10;
    }
    if (window->KeyHold(GLFW_KEY_F)) {
        translateY += -deltaTime * 10;
    }
    if (window->KeyHold(GLFW_KEY_W)) {
        translateZ += deltaTime * 10;
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        translateZ += -deltaTime * 10;
    }

    if (window->KeyHold(GLFW_KEY_1)) {
        scaleX += deltaTime * 5l;
        scaleY += deltaTime * 5l;
        scaleZ += deltaTime * 5l;
    }
    if (window->KeyHold(GLFW_KEY_2)) {
        scaleX += -deltaTime * 5l;
        scaleY += -deltaTime * 5l;
        scaleZ += -deltaTime * 5l;
    }
    if (window->KeyHold(GLFW_KEY_3)) {
        angularStepOX += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_4)) {
        angularStepOX += -deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_5)) {
        angularStepOY += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_6)) {
        angularStepOY += -deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_7)) {
        angularStepOZ += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_8)) {
        angularStepOZ += -deltaTime;
    }







}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    // miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    if (key == GLFW_KEY_O)
    {
        //  glm::mat4 Projection = glm::ortho(float left, float right, float bottom, float top, float zNear, float zFar);
        orthoLeft = -8.0f;
        orthoRight = 8.0f;
        orthoUp = 4.5f;
        orthoDown = -4.5;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
        isOrtho = true;
    }
    if (key == GLFW_KEY_P)
    {
        projectionMatrix = glm::perspective(90.f, 2.f, 2.f, 200.0f);
        isOrtho = false;
    }





    // TODO(student): Add viewport movement and scaling logic
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
            camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            // 
            camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
            camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
            //camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
            //camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);

        }
    }
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
