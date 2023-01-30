#pragma once


#include "components/simple_scene.h"

#include "lab_m1/Tema2/camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

       // void RenderMesh() override;
        void RenderScene();
    protected:
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        float x1, x2, x3;
        std::vector<float> road_inside = { -7.9 , 5.36 , -4.78 , 5.46 , -1.02 , 5.5 , 2.82 , 5.44 , 7.1 , 4.68 , 8.9 , 1.76 , 9.48 , -2.12 , 8.46 , -5.86 , 3 , -7 , 1 , -5 , 1.86 , -3.24 , 3.28 , -1.68 , 3.44 , 0.08 , 2.82 , 1.04 , 0.98 , 1.84 , -1 , 2 , -4.38 , 1.74 , -7.22 , 1.78 , -8.84 , 2.86 , -8.86 , 4.22 ,                    -11.9,3.7};
        std::vector<float> road_outside = { -8.66 , 7.17 , -4.38 , 7.64 , -1.05 , 7.73 , 3.04 , 7.85 , 8.84 , 7 , 12.18 , 1.44 , 12.56 , -2.1 , 10.69 , -7.93 , 2.31 , -9.42 , -1.49 , -5.7 , -0.61 , -2.51 , 0.41 , -1.13 , 0.58 , -0.55 , 0.2 , -0.25 , -0.4 , 0.21 , -1.08 , 0.26 , -4.38 , 0.21 , -8.34 , 0.35 , -10.68 , 2.31 , -11.06,5.22,  -9.09,3.58 };
        implemented2::Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        float orthoLeft;
        float orthoRight;
        float orthoUp;
        float orthoDown;
        bool isOrtho = false;

        float rotate;
    };
}   // namespace m1

