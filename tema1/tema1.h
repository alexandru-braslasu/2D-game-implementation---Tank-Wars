#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        struct coordonate
        {
            double xTank, x, vx, vy, g, arctg, angleTun, from;
        };

        /*struct struc_inaltimi
        {
            double Y1, Y2, Y3;
        };*/

    public:
        tema1();
        ~tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        double f(double x);
        double sgn(double x);

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        double length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        double width, height, width_mini_rectangle, scalare;
        double angleTun1, angleTun2;
        double xTank1, xTank2, life1, life2;
        bool activate1, activate2;
        double arctg1, arctg2;
        double xNor1, xNor2, xNor3;
        int N;
        std::vector<coordonate > coada;
        std::vector<std::pair<double, double > > deformari;
        //std::vector<std::pair<double, std::pair<double, struc_inaltimi > > > aplatizari;
    };
}   // namespace m1