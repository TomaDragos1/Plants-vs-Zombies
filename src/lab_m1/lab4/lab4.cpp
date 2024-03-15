#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init()
{
    polygonMode = GL_FILL;

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

void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Lab4::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    //modelMatrix = glm::mat4(1);
    //modelMatrix *= transform3D::Translate(translateX,translateY,translateZ);
    //modelMatrix *= transform3D::Translate(2.5f , -0.5f ,1.5f );
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::Translate(-2.5f , 0.0f , -1.5f);

    //modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);

    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene();
    DrawCoordinateSystem();
}

void Lab4::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Add transformation logic
    // First
    float translationSpeed = 2.0f * deltaTime; // Adjust speed as needed
    if (window->KeyHold(GLFW_KEY_W)) {
        translateX += translationSpeed; // Update translateX for the first cube
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        translateX -= translationSpeed; // Update translateX for the first cube
    }
    if (window->KeyHold(GLFW_KEY_R)) {
        translateY -= translationSpeed; // Update translateY for the first cube
    }
    if (window->KeyHold(GLFW_KEY_F)) {
        translateY += translationSpeed; // Update translateY for the first cube
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        translateZ += translationSpeed; // Update translateX for the first cube
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        translateZ -= translationSpeed; // Update translateX for the first cube
    }
    // Second

    float scalingSpeed = 0.5f * deltaTime; // Adjust the scaling speed as needed
    if (window->KeyHold(GLFW_KEY_1)) {
        scaleX -= scalingSpeed; // Update scaleX for the second cube
        scaleY -= scalingSpeed; // Update scaleY for the second cube
        scaleZ -= scalingSpeed; // Update scaleZ for the second cube
    }
    if (window->KeyHold(GLFW_KEY_2)) {
        scaleX += scalingSpeed; // Update scaleX for the second cube
        scaleY += scalingSpeed; // Update scaleY for the second cube
        scaleZ += scalingSpeed; // Update scaleZ for the second cube
    }

    // Third 
    float rotationSpeed = glm::radians(90.0f) * deltaTime; // Adjust the rotation speed as needed
    if (window->KeyHold(GLFW_KEY_3)) {
        angularStepOX += rotationSpeed; // Update angularStepOX for the third cube
    }
    if (window->KeyHold(GLFW_KEY_4)) {
        angularStepOX -= rotationSpeed; // Update angularStepOX for the third cube
    }
    if (window->KeyHold(GLFW_KEY_5)) {
        angularStepOY += rotationSpeed; // Update angularStepOY for the third cube
    }
    if (window->KeyHold(GLFW_KEY_6)) {
        angularStepOY -= rotationSpeed; // Update angularStepOY for the third cube
    }
    if (window->KeyHold(GLFW_KEY_7)) {
        angularStepOZ += rotationSpeed; // Update angularStepOZ for the third cube
    }
    if (window->KeyHold(GLFW_KEY_8)) {
        angularStepOZ -= rotationSpeed; // Update angularStepOZ for the third cube
    }


    if (window->KeyHold(GLFW_KEY_0)) {
        angularStepOY += rotationSpeed;
    } 
    if (window->KeyHold(GLFW_KEY_9)) {
        angularStepOY -= rotationSpeed;
    }

}


void Lab4::OnKeyPress(int key, int mods)
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

    // TODO(student): Add viewport movement and scaling logic
    // Viewport movement and scaling logic
    float movementSpeed = 10.0f;
    float scalingSpeed = 0.1f;

    if (key == GLFW_KEY_I) {
        miniViewportArea.y += movementSpeed; // Move the small viewport up
    }
    else if (key == GLFW_KEY_K) {
        miniViewportArea.y -= movementSpeed; // Move the small viewport down
    }
    else if (key == GLFW_KEY_J) {
        miniViewportArea.x -= movementSpeed; // Move the small viewport left
    }
    else if (key == GLFW_KEY_L) {
        miniViewportArea.x += movementSpeed; // Move the small viewport right
    }
    else if (key == GLFW_KEY_U) {
        // Increase the size of the small viewport
        miniViewportArea.width *= (1.0f + scalingSpeed);
        miniViewportArea.height *= (1.0f + scalingSpeed);
    }
    else if (key == GLFW_KEY_O) {
        // Decrease the size of the small viewport
        miniViewportArea.width *= (1.0f - scalingSpeed);
        miniViewportArea.height *= (1.0f - scalingSpeed);
    }
}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
