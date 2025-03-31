#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"

using namespace std;
using namespace m1;

// f(x) = sin(x) + 2 * sin(0.5x) + 0.5sin(3x)

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

double tema1::f(double x) {
    double fx = 1.2 + 0.5 * sin(x) + 0.7 * sin(0.5 * x) + 0.5 * sin(3 * x);
    /*double x1 = x - 0.01, x2 = x + 0.01;
    double fx1 = 1.2 + 0.5 * sin(x1) + 0.7 * sin(0.5 * x1) + 0.5 * sin(3 * x1);
    double fx2 = 1.2 + 0.5 * sin(x2) + 0.7 * sin(0.5 * x2) + 0.5 * sin(3 * x2);*/
    bool ok = true;
    while (ok) {
        ok = false;
        for (auto it : deformari) {
            if (sqrt((it.first - x) * (it.first - x) + (it.second - fx) * (it.second - fx)) < 0.69) {
                fx = it.second - sqrt(abs(0.7 * 0.7 - (it.first - x) * (it.first - x)));
                ok = true;
            }
        }
    }
    /*ok = true;
    while (ok) {
        ok = false;
        for (auto it : deformari) {
            if (sqrt((it.first - x1) * (it.first - x1) + (it.second - fx1) * (it.second - fx1)) < 0.69) {
                fx1 = it.second - sqrt(abs(0.7 * 0.7 - (it.first - x1) * (it.first - x1)));
                ok = true;
            }
        }
    }
    ok = true;
    while (ok) {
        ok = false;
        for (auto it : deformari) {
            if (sqrt((it.first - x2) * (it.first - x2) + (it.second - fx2) * (it.second - fx2)) < 0.69) {
                fx2 = it.second - sqrt(abs(0.7 * 0.7 - (it.first - x2) * (it.first - x2)));
                ok = true;
            }
        }
    }
    if (abs(abs((fx - fx1) / 0.01) - abs((fx2 - fx) / 0.01)) > 0.1) {
        aplatizari.push_back({ x - 0.05, { x + 0.05, { fx1, fx, fx2 } } });
    }
    for (auto it : aplatizari)
        if (x >= it.first && x <= it.second.first) {
            double X1 = it.first, X3 = it.second.first;
            double X2 = (X1 + X3) / 2.0000;
            double t = 1 + (sqrt((X2 - X3) * (X2 - X3) + (X1 + X3) * (X3 - x)) + (X2 - X3)) / (X1 + X3);
            fx = (1 - t) * it.second.second.Y1 + 2 * (1 - t) * it.second.second.Y2 + t * t * it.second.second.Y3;
        }*/
    return fx;
}

tema1::tema1()
{
}


tema1::~tema1()
{
}


void tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    angleTun1 = 0;
    angleTun2 = 0;

    xTank1 = 1.5;
    xTank2 = 5;

    arctg1 = arctg2 = 0;

    activate1 = activate2 = false;
    life1 = life2 = 1.00;

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height

    glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
    length = 1;

    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-3, 0, 0), glm::vec3(0.8, 0.69, 0.53)),
        VertexFormat(glm::vec3(3, 0, 0), glm::vec3(0.8, 0.69, 0.53)),
        VertexFormat(glm::vec3(2, 1.5, 0), glm::vec3(0.8, 0.69, 0.53)),
        VertexFormat(glm::vec3(-2, 1.5, 0), glm::vec3(0.8, 0.69, 0.53)),
        VertexFormat(glm::vec3(-2, 0, 0), glm::vec3(0.46, 0.39, 0.31)),
        VertexFormat(glm::vec3(-1.7, -0.5, 0), glm::vec3(0.46, 0.39, 0.31)),
        VertexFormat(glm::vec3(1.7, -0.5, 0), glm::vec3(0.46, 0.39, 0.31)),
        VertexFormat(glm::vec3(2, 0, 0), glm::vec3(0.46, 0.39, 0.31))
    };
    int N = 100;
    vertices.push_back(VertexFormat(glm::vec3(0, 1.5, 0), glm::vec3(0.8, 0.69, 0.53)));
    for (int i = 0; i < N; ++i)
        vertices.push_back(VertexFormat(glm::vec3(sin(i * M_1_PI * 20.00 / N), 1.5 + cos(i * M_1_PI * 20.00 / N), 0), glm::vec3(0.8, 0.69, 0.53)));

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7
    };
    for (int i = 0; i < N - 1; ++i) {
        indices.push_back(i + 9);
        indices.push_back(8);
        indices.push_back(i + 10);
    }
    indices.push_back(107);
    indices.push_back(8);
    indices.push_back(9);

    meshes["tank"] = new Mesh("tank_up");
    meshes["tank"]->InitFromData(vertices, indices);

    // Actually create the mesh from the data
    CreateMesh("tank_up", vertices, indices);

    vector<VertexFormat> vertices1
    {
        VertexFormat(glm::vec3(-1, -1, 0), glm::vec3(0.227, 0.227, 0.235)),
        VertexFormat(glm::vec3(1, -1, 0), glm::vec3(0.227, 0.227, 0.235)),
        VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0.227, 0.227, 0.235)),
        VertexFormat(glm::vec3(-1, 1, 0), glm::vec3(0.227, 0.227, 0.235))
    };

    vector<unsigned int> indices1 =
    {
        0, 1, 2,
        2, 3, 0
    };

    meshes["tun"] = new Mesh("tank_up");
    meshes["tun"]->InitFromData(vertices1, indices1);

    // Actually create the mesh from the data
    CreateMesh("tun", vertices1, indices1);

    xNor1 = 1;
    xNor2 = 3.5;
    xNor3 = 6;
    vector<VertexFormat> vertices2
    {
        VertexFormat(glm::vec3(-1, -1, 0), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(3, -1, 0), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(1, -0.2, 0), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(-1, -0.2, 0), glm::vec3(0, 0, 1))
    };
    vector<unsigned int> indices2 =
    {
        0, 1, 2,
        0, 2, 3
    };
    N = 100;
    vertices2.push_back(VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 0, 1)));
    for (int i = 0; i < N; ++i)
        vertices2.push_back(VertexFormat(glm::vec3(1 + cos(i * M_1_PI * 20.00 / N), sin(i * M_1_PI * 20.00 / N), 0), glm::vec3(0, 0, 1)));
    for (int i = 0; i < N; ++i) {
        indices2.push_back(i + 5);
        indices2.push_back(4);
        indices2.push_back(i + 6);
    }
    indices2.push_back(105);
    indices2.push_back(4);
    indices2.push_back(5);

    vertices2.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1))); //106
    for (int i = 0; i < N; ++i)
        vertices2.push_back(VertexFormat(glm::vec3(cos(i * M_1_PI * 20.00 / N), sin(i * M_1_PI * 20.00 / N), 0), glm::vec3(0, 0, 1)));
    for (int i = 0; i < N; ++i) {
        indices2.push_back(i + 107);
        indices2.push_back(106);
        indices2.push_back(i + 108);
    }
    indices2.push_back(207);
    indices2.push_back(4);
    indices2.push_back(107);

    vertices2.push_back(VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1))); //208
    for (int i = 0; i < N; ++i)
        vertices2.push_back(VertexFormat(glm::vec3(-1 + cos(i * M_1_PI * 20.00 / N), sin(i * M_1_PI * 20.00 / N), 0), glm::vec3(0, 0, 1)));
    for (int i = 0; i < N; ++i) {
        indices2.push_back(i + 209);
        indices2.push_back(4);
        indices2.push_back(i + 210);
    }
    indices2.push_back(309);
    indices2.push_back(208);
    indices2.push_back(209);

    meshes["nor"] = new Mesh("nor");
    meshes["nor"]->InitFromData(vertices2, indices2);

    // Actually create the mesh from the data
    CreateMesh("nor", vertices2, indices2);


    Mesh* square = object2D::CreateSquare("square", corner, length, glm::vec3(0.824, 0.808, 0.247), 1, true);
    AddMeshToList(square);

    Mesh* square_white = object2D::CreateSquare("square_white", corner, length, glm::vec3(255, 255, 255), 1, true);
    AddMeshToList(square_white);

    vector<VertexFormat > vert;
    vector<unsigned int > ind;
    for (int i = 1; i <= 100; ++i)
        vert.push_back(VertexFormat(glm::vec3(cos(i * (20.00f * M_1_PI / 100.00f)), sin(i * (20.00f * M_1_PI / 100.00f)), 0), glm::vec3(0, 0, 0)));
    vert.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));

    for (int i = 0; i < 99; ++i) {
        ind.push_back(i);
        ind.push_back(100);
        ind.push_back(i + 1);
    }
    ind.push_back(98);
    ind.push_back(100);
    ind.push_back(0);
    meshes["disc"] = new Mesh("disc");
    meshes["disc"]->InitFromData(vert, ind);
    RenderMesh(meshes["disc"], shaders["VertexColor"], glm::vec3(0, 0, 0));
}

double tema1::sgn(double x) {
    if (x < 0)
        return -1.00;
    return 1.00;
}

void tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glDeleteBuffers(1, &VAO);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


// 2D visualization matrix
glm::mat3 tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, 0.0f,
        0.0f, sy, 0.0f,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;

    width = viewSpace.width / smin;
    height = viewSpace.height / smin;
    scalare = smin;

    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, 0.0f,
        0.0f, smin, 0.0f,
        0.0f, 0.0f, 1.0f));
}


void tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    //glEnable(GL_SCISSOR_TEST);
    //glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    //glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.55f, 0.75f, 0.89f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw - the left half of the window
    //viewSpace = ViewportSpace(0, 0, resolution.x / 2, resolution.y);
    //SetViewportArea(viewSpace, glm::vec3(0), true);

    // Compute the 2D visualization matrix
    //visMatrix = glm::mat3(1);
    //visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

    //DrawScene(visMatrix);

    // The viewport is now the right half of the window

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.5f), true);

    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawScene(visMatrix, deltaTimeSeconds);
}


void tema1::FrameEnd()
{
}


void tema1::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
    glm::ivec2 resolution = window->GetResolution();

    // desenare nori
    if (xNor1 < 0)
        xNor1 = 7.5;
    if (xNor2 < 0)
        xNor2 = 7.5;
    if (xNor3 < 0)
        xNor3 = 7.5;
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(xNor1, 3.6);
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    RenderMesh2D(meshes["nor"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(xNor2, 3.6);
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    RenderMesh2D(meshes["nor"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(xNor3, 3.6);
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    RenderMesh2D(meshes["nor"], shaders["VertexColor"], modelMatrix);

    xNor1 -= deltaTimeSeconds / 10;
    xNor2 -= deltaTimeSeconds / 10;
    xNor3 -= deltaTimeSeconds / 10;

    N = 100;
    for (int i = 0; i < ceil(width / length); ++i) {
        for (int j = 0; j < N; ++j) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(j * 1.000f / double(N) + i * length, 0);
            modelMatrix *= transform2D::Scale(1.0000f / double(N), f(j * 1.000f / double(N) + i * length));
            RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
        }
    }
    if (life1 > 0.01) {
        arctg1 = atan2(f(xTank1 + 0.01) - f(xTank1), 0.01);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
        modelMatrix *= transform2D::Rotate(arctg1);
        modelMatrix *= transform2D::Scale(0.1, 0.1);
        RenderMesh2D(meshes["tank"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
        modelMatrix *= transform2D::Rotate(arctg1);
        modelMatrix *= transform2D::Translate(0, 0.15);
        modelMatrix *= transform2D::Rotate(angleTun1 - arctg1); // daca scot arctg ramane perpendicular pe plan
        modelMatrix *= transform2D::Translate(0, 0.2);
        modelMatrix *= transform2D::Scale(0.017, 0.1);
        RenderMesh2D(meshes["tun"], shaders["VertexColor"], modelMatrix);

        Mesh* square_life_filled1;
        if (life1 > 0.5)
            square_life_filled1 = object2D::CreateSquare("square_life_filled1", corner, length, glm::vec3(255, 255, 255), life1, true);
        else
            square_life_filled1 = object2D::CreateSquare("square_life_filled1", corner, length, glm::vec3(255, 0, 0), life1, true);
        AddMeshToList(square_life_filled1);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
        modelMatrix *= transform2D::Translate(0, 0.15);
        modelMatrix *= transform2D::Translate(-0.25, 0.35);
        modelMatrix *= transform2D::Scale(0.5, 0.1);
        RenderMesh2D(meshes["square_life_filled1"], shaders["VertexColor"], modelMatrix);

        Mesh* square_life_empty1;
        if (life1 > 0.5)
            square_life_empty1 = object2D::CreateSquare("square_life_empty1", corner, length, glm::vec3(255, 255, 255), (1 - life1), false);
        else
            square_life_empty1 = object2D::CreateSquare("square_life_empty1", corner, length, glm::vec3(255, 0, 0), (1 - life1), false);
        AddMeshToList(square_life_empty1);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
        modelMatrix *= transform2D::Translate(0, 0.15);
        modelMatrix *= transform2D::Translate(-0.25, 0.35);
        modelMatrix *= transform2D::Scale(0.5, 0.1);
        modelMatrix *= transform2D::Translate(length * life1, 0);
        RenderMesh2D(meshes["square_life_empty1"], shaders["VertexColor"], modelMatrix);

        if (angleTun1 == 0) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
            modelMatrix *= transform2D::Rotate(arctg1);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Rotate(angleTun1 - arctg1);
            modelMatrix *= transform2D::Translate(0, 0.2);
            modelMatrix *= transform2D::Scale(0.01, 1.5);
            RenderMesh2D(meshes["square_white"], shaders["VertexColor"], modelMatrix);
        }
        else {
            //angleTun1 = 3.14 / 360;
            N = 100;
            double vx = sin(angleTun1) / (1.2 / abs(angleTun1));
            double vy = -cos(angleTun1) / (1.2 / abs(angleTun1));
            double g = 0.001;
            for (int i = 0; i < ceil(7 / length); ++i)
                for (int j = 0; j < N; ++j) {
                    modelMatrix = visMatrix;
                    double x = -sgn(cos(angleTun1 - 3.14 / 2)) * j / double(N) - sgn(cos(angleTun1 - 3.14 / 2)) * i * length + xTank1;
                    modelMatrix *= transform2D::Translate(x, f(xTank1) + 0.05 + vy * (x - xTank1) / vx);
                    vy = vy + g;
                    g += 0.00001;
                    modelMatrix *= transform2D::Rotate(arctg1);
                    modelMatrix *= transform2D::Translate(0, 0.15);
                    modelMatrix *= transform2D::Scale(1.000000000 / double(N), 1 / (abs(angleTun1) + 40));
                    RenderMesh2D(meshes["square_white"], shaders["VertexColor"], modelMatrix);
                }
        }
    }

    // coada de proiectile
    for (size_t i = 0; i < coada.size(); ++i) {
        modelMatrix = visMatrix;
        if (coada[i].angleTun == 0) {
            modelMatrix *= transform2D::Translate(coada[i].x, f(coada[i].xTank) + 0.05 + coada[i].vy * 0.7);
            coada[i].vy = coada[i].vy + coada[i].g;
            coada[i].g -= 0.002;
            modelMatrix *= transform2D::Rotate(coada[i].arctg);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);
            if (0.05 + coada[i].vy * 0.7 < 0 && abs(xTank1 - coada[i].xTank) < 0.1) {
                life1 -= 0.1;
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            }
            else if (0.05 + coada[i].vy * 0.7 < 0 && abs(xTank2 - coada[i].xTank) < 0.1) {
                life2 -= 0.1;
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            } else if (0.05 + coada[i].vy * 0.7 < 0) {
                deformari.push_back({ coada[i].x, f(coada[i].xTank) + 0.05 + coada[i].vy * 0.7 });
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            }
            else if (f(coada[i].xTank) + 0.05 + coada[i].vy * 0.7 < 0) {
            for (int j = i + 1; j < coada.size(); ++j)
                coada[j - 1] = coada[j];
            coada.pop_back();
        }
            continue;
        }
        coada[i].x += -sgn(cos(coada[i].angleTun - 3.14 / 2)) * 0.1;
        double fx = f(coada[i].xTank) + coada[i].vy * (coada[i].x - coada[i].xTank) / coada[i].vx;
        if (abs(xTank1 - coada[i].x) < 0.4 && abs(fx - f(xTank1)) < 0.4) {
            if (coada[i].from != 1) {
                life1 -= 0.1;
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            } else if (abs(xTank1 - coada[i].x) < 0.05 && abs(fx - f(xTank1)) < 0.05) {
                life1 -= 0.1;
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            }
        } else  if (abs(xTank2 - coada[i].x) < 0.4 && abs(fx - f(xTank2)) < 0.4) {
            if (coada[i].from != 2) {
                life2 -= 0.1;
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            }
            else if (abs(xTank2 - coada[i].x) < 0.05 && abs(fx - f(xTank2)) < 0.05) {
                life2 -= 0.1;
                for (int j = i + 1; j < coada.size(); ++j)
                    coada[j - 1] = coada[j];
                coada.pop_back();
            }
        } else if (fx < f(coada[i].x)) {
            deformari.push_back({ coada[i].x, fx });
            for (int j = i + 1; j < coada.size(); ++j)
                coada[j - 1] = coada[j];
            coada.pop_back();
        } else if (fx < 0) {
            for (int j = i + 1; j < coada.size(); ++j)
                coada[j - 1] = coada[j];
            coada.pop_back();
        } else {
            modelMatrix *= transform2D::Translate(coada[i].x, f(coada[i].xTank) + 0.05 + coada[i].vy * (coada[i].x - coada[i].xTank) / coada[i].vx);
            coada[i].vy = coada[i].vy + coada[i].g;
            coada[i].g += 0.0015;
            modelMatrix *= transform2D::Rotate(coada[i].arctg);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);
        }
    }


    if (activate1) {
        if (angleTun1 == 0) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
            modelMatrix *= transform2D::Rotate(arctg1);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Rotate(angleTun1 - arctg1); // daca scot arctg ramane perpendicular pe plan
            modelMatrix *= transform2D::Translate(0, 0.1);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);
            coada.push_back({ xTank1, xTank1, sin(angleTun1) / (1.2 / abs(angleTun1)), cos(angleTun1) / (1.2 / abs(angleTun1)), 0.1, arctg1, angleTun1, 1 });
        }
        else {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(xTank1, f(xTank1) + 0.05);
            modelMatrix *= transform2D::Rotate(arctg1);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Rotate(angleTun1 - arctg1); // daca scot arctg ramane perpendicular pe plan
            modelMatrix *= transform2D::Translate(0, 0.1);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);
            coada.push_back({ xTank1, xTank1, sin(angleTun1) / (1.2 / abs(angleTun1)), -cos(angleTun1) / (1.2 / abs(angleTun1)), 0.01, arctg1, angleTun1, 1 });
        }
        activate1 = false;
    }


    if (life2 > 0.01) {
        arctg2 = atan2(f(xTank2 + 0.01) - f(xTank2), 0.01);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
        modelMatrix *= transform2D::Rotate(arctg2);
        modelMatrix *= transform2D::Scale(0.1, 0.1);
        RenderMesh2D(meshes["tank"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
        modelMatrix *= transform2D::Rotate(arctg2);
        modelMatrix *= transform2D::Translate(0, 0.15);
        modelMatrix *= transform2D::Rotate(angleTun2 - arctg2); // daca scot arctg ramane perpendicular pe plan
        modelMatrix *= transform2D::Translate(0, 0.2);
        modelMatrix *= transform2D::Scale(0.017, 0.1);
        RenderMesh2D(meshes["tun"], shaders["VertexColor"], modelMatrix);

        Mesh* square_life_filled2;
        if (life2 > 0.5)
            square_life_filled2 = object2D::CreateSquare("square_life_filled2", corner, length, glm::vec3(255, 255, 255), life2, true);
        else
            square_life_filled2 = object2D::CreateSquare("square_life_filled2", corner, length, glm::vec3(255, 0, 0), life2, true);
        AddMeshToList(square_life_filled2);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
        modelMatrix *= transform2D::Translate(0, 0.15);
        modelMatrix *= transform2D::Translate(-0.25, 0.35);
        modelMatrix *= transform2D::Scale(0.5, 0.1);
        RenderMesh2D(meshes["square_life_filled2"], shaders["VertexColor"], modelMatrix);

        Mesh* square_life_empty2;
        if (life2 > 0.5)
            square_life_empty2 = object2D::CreateSquare("square_life_empty2", corner, length, glm::vec3(255, 255, 255), (1 - life2), false);
        else
            square_life_empty2 = object2D::CreateSquare("square_life_empty2", corner, length, glm::vec3(255, 0, 0), (1 - life2), false);
        AddMeshToList(square_life_empty2);
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
        modelMatrix *= transform2D::Translate(0, 0.15);
        modelMatrix *= transform2D::Translate(-0.25, 0.35);
        modelMatrix *= transform2D::Scale(0.5, 0.1);
        modelMatrix *= transform2D::Translate(length * life2, 0);
        RenderMesh2D(meshes["square_life_empty2"], shaders["VertexColor"], modelMatrix);

        if (angleTun2 == 0) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
            modelMatrix *= transform2D::Rotate(arctg2);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Rotate(angleTun2 - arctg2);
            modelMatrix *= transform2D::Translate(0, 0.2);
            modelMatrix *= transform2D::Scale(0.01, 1.5);
            RenderMesh2D(meshes["square_white"], shaders["VertexColor"], modelMatrix);
        }
        else {
            //angleTun2 = 3.14 / 36;
            N = 100;
            double vx = sin(angleTun2) / (1.2 / abs(angleTun2));
            double vy = -cos(angleTun2) / (1.2 / abs(angleTun2));
            double g = 0.001;
            for (int i = 0; i < ceil(7 / length); ++i)
                for (int j = 0; j < N; ++j) {
                    modelMatrix = visMatrix;
                    double x = -sgn(cos(angleTun2 - 3.14 / 2)) * j * 1.000f / double(N) - sgn(cos(angleTun2 - 3.14 / 2)) * i * length + xTank2;
                    modelMatrix *= transform2D::Translate(x, f(xTank2) + 0.05 + vy * (x - xTank2) / vx);
                    vy = vy + g;
                    g += 0.00001;
                    modelMatrix *= transform2D::Rotate(arctg2);
                    modelMatrix *= transform2D::Translate(0, 0.15);
                    modelMatrix *= transform2D::Scale(1.0000f / double(N), 1 / (abs(angleTun2) + 40));
                    RenderMesh2D(meshes["square_white"], shaders["VertexColor"], modelMatrix);
                }
        }
    }

    if (activate2) {
        if (angleTun2 == 0) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
            modelMatrix *= transform2D::Rotate(arctg2);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Rotate(angleTun2 - arctg2); // daca scot arctg ramane perpendicular pe plan
            modelMatrix *= transform2D::Translate(0, 0.1);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);
            coada.push_back({ xTank2, xTank2, sin(angleTun2) / (1.2 / abs(angleTun2)), cos(angleTun2) / (1.2 / abs(angleTun2)), 0.1, arctg2, angleTun2, 1 });
        }
        else {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(xTank2, f(xTank2) + 0.05);
            modelMatrix *= transform2D::Rotate(arctg2);
            modelMatrix *= transform2D::Translate(0, 0.15);
            modelMatrix *= transform2D::Rotate(angleTun2 - arctg2); // daca scot arctg ramane perpendicular pe plan
            modelMatrix *= transform2D::Translate(0, 0.1);
            modelMatrix *= transform2D::Scale(0.03, 0.03);
            RenderMesh2D(meshes["disc"], shaders["VertexColor"], modelMatrix);
            coada.push_back({ xTank2, xTank2, sin(angleTun2) / (1.2 / abs(angleTun2)), -cos(angleTun2) / (1.2 / abs(angleTun2)), 0.01, arctg2, angleTun2, 2 });
        }
        activate2 = false;
    }
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_UP)) {
        if (angleTun2 <= -3.14)
            angleTun2 = -angleTun2;
        angleTun2 -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (angleTun2 >= 3.14)
            angleTun2 = -angleTun2;
        angleTun2 += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_LEFT)) {
        xTank2 -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        xTank2 += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_W)) {
        if (angleTun1 >= 3.14)
            angleTun1 = -angleTun1;
        angleTun1 += deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if (angleTun1 <= -3.14)
            angleTun1 = -angleTun1;
        angleTun1 -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        xTank1 -= deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        xTank1 += deltaTime;
    }

}


void tema1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE) {
        activate1 = true;
    }

    if (key == GLFW_KEY_ENTER) {
        activate2 = true;
    }
}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}