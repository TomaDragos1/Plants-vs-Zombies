#include "lab_m1/lab5/lab5.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab5::Lab5()
{
}


Lab5::~Lab5()
{
}


void Lab5::Init()
{
    renderCameraTarget = false;
    fov = 60;
    orthoWidth = 10.0f; // Initial width for orthographic projection
    orthoHeight = 10.0f; // Initial height for orthographic projection
    nearPlane = 0.1f;  // Initial near plane for both projections
    farPlane = 100.0f; // Initial far plane for both projections

    isOrthographic = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

}


void Lab5::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab5::Update(float deltaTimeSeconds)
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));

        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
        RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
    }
    {
        // Desenează primul obiect adițional
        glm::mat4 modelMatrix = glm::mat4(1);

        // Definirea matricei de modelare pentru primul obiect adițional
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 0, -2)); // Translație
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(0, 1, 0)); // Rotație
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f)); // Scalare

        // Randarea primului obiect adițional
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }

    {
        // Desenează al doilea obiect adițional
        glm::mat4 modelMatrix = glm::mat4(1);

        // Definirea matricei de modelare pentru al doilea obiect adițional
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 1, -3)); // Translație
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0)); // Rotație
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f)); // Scalare

        // Randarea al doilea obiect adițional
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }



    // TODO(student): Draw more objects with different model matrices.
    // Attention! The `RenderMesh()` function overrides the usual
    // `RenderMesh()` that we've been using up until now. This new
    // function uses the view matrix from the camera that you just
    // implemented, and the local projection matrix.

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }
}


void Lab5::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Lab5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
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


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab5::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f * deltaTime;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(cameraSpeed);
        }
    }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.
    if (window->KeyHold(GLFW_KEY_9)) {  // Poate fi și altă tastă, nu doar '+' de pe numpad
        // Mărirea FoV-ului cu o valoare delta
        fov += 1.0f;  // Poate fi o valoare diferită în funcție de cât de mult vreți să măriți
        projectionMatrix = glm::perspective(glm::radians(fov), window->props.aspectRatio, 0.01f, 200.0f);
    }

    // Tasta pentru a micșora FoV-ul
    if (window->KeyHold(GLFW_KEY_0)) {  // Poate fi și altă tastă, nu doar '-' de pe numpad
        // Scăderea FoV-ului cu o valoare delta
        fov -= 1.0f;  // Poate fi o valoare diferită în funcție de cât de mult vreți să micșorați
        projectionMatrix = glm::perspective(glm::radians(fov), window->props.aspectRatio, 0.01f, 200.0f);
    }
    //if (window->KeyHold(GLFW_KEY_M)) {
    //    // Modificați lățimea și înălțimea ferestrei de proiecție în cazul proiecției ortografice
    //    left = -10.0f * deltaTime;  // Modificați valorile după necesitate
    //    right = 10.0f * deltaTime;
    //    bottom = -10.0f * deltaTime;
    //    top = 10.0f * deltaTime;

  
    //}
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        orthoWidth += 1.0f; // Increase width
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        orthoWidth -= 1.0f; // Decrease width
    }
    if (window->KeyHold(GLFW_KEY_UP)) {
        orthoHeight += 1.0f; // Increase height
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        orthoHeight -= 1.0f; // Decrease height
    }

    // Ensure that width and height are not negative
    orthoWidth = glm::max(orthoWidth, 1.0f);
    orthoHeight = glm::max(orthoHeight, 1.0f);

    // If in orthographic mode, update the projection matrix
    if (isOrthographic) {
        projectionMatrix = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearPlane, farPlane);
    }


}


void Lab5::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    //if (key == GLFW_KEY_O) {
    //    // Setează proiecția ortografică
    //    glm::mat4 Projection = glm::ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    //    // Setează parametrii proiecției ortografice
    //    // ...

    //    // Redesenează scena pentru a aplica noua proiecție
    //    Render(); // Sau cheamă funcția de randare relevantă.
    //}

    //if (key == GLFW_KEY_P) {
    //    // Setează proiecția perspectivă
    //    camera->SetProjectionType(Camera::PERSPECTIVE);
    //    // Setează parametrii proiecției perspektive
    //    // ...

    //    // Redesenează scena pentru a aplica noua proiecție
    //    Render(); // Sau cheamă funcția de randare relevantă.
    //}
    if (key == GLFW_KEY_O) {
        // Switch to orthographic projection
        // Recalculate the projection matrix for orthographic projection
        isOrthographic = true;
        projectionMatrix = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, nearPlane, farPlane);
    }

    if (key == GLFW_KEY_P) {
        // Switch to perspective projection
        // Recalculate the projection matrix for perspective projection
        isOrthographic = false;
        projectionMatrix = glm::perspective(glm::radians(fov), window->props.aspectRatio, nearPlane, farPlane);
    }

}


void Lab5::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(-sensivityOY * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOX * deltaX);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-sensivityOY * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOX * deltaX);

        }
    }
}


void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab5::OnWindowResize(int width, int height)
{
}
