#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateRhombus(
    const std::string& name,
    glm::vec3 rhombusCenter,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    rhombusCenter.z = 1;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(rhombusCenter, color),
        VertexFormat(rhombusCenter + glm::vec3(0, height, 1), color),
        VertexFormat(rhombusCenter - glm::vec3(0, height, 1), color),
        VertexFormat(rhombusCenter - glm::vec3(width, 0, 1), color),
        VertexFormat(rhombusCenter + glm::vec3(width, height / 4,  1), color),
        VertexFormat(rhombusCenter + glm::vec3(width, -height / 4,  1), color),
        VertexFormat(rhombusCenter + glm::vec3(width + height, height / 4,  1), color),
        VertexFormat(rhombusCenter + glm::vec3(width + height, -height / 4,  1), color),
    };

    std::vector<unsigned int> indices = { 1, 0 ,4, 
                                          4, 0, 5,
                                          5, 0, 2,
                                          1, 3, 2 , 
                                           6, 4, 7,
                                          7 ,4, 5};

    Mesh* combinedObject = new Mesh(name);

    if (!fill) {
        combinedObject->SetDrawMode(GL_LINE_LOOP);
    }

    combinedObject->InitFromData(vertices, indices);

    return combinedObject;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 hexagonCenter,
    float radius,
    glm::vec3 color,
    glm::vec3 smallColor,
    bool fill
)
{
    std::vector<VertexFormat> vertices;

    int sides = 6;
    float angleIncrement = 2 * M_PI / sides;

    // Add the center vertex
    vertices.push_back(VertexFormat(hexagonCenter, color));

    for (int i = 0; i < sides; i++) {
        float angle = i * angleIncrement;
        float x = hexagonCenter.x + radius * cos(angle);
        float y = hexagonCenter.y + radius * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(x, y, 1), color));
    }
    for (int i = 0; i < sides; i++) {
        float angle = i * angleIncrement;
        float x = hexagonCenter.x + (radius - 20) * cos(angle);
        float y = hexagonCenter.y + (radius - 20) * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(x, y, 2), smallColor));
    }
    std::vector<unsigned int> indices = {0, 1, 2,
                                         2, 3, 0,
                                        3, 4, 0,
                                        4, 5, 0,
                                        0, 5, 6,
                                        0, 6, 1 ,
                                        7, 8, 9,
                                        9, 10, 7,
                                        10, 11, 7,
                                        11, 12, 7,
                                        7, 12, 13,
                                        7, 13, 8 };

    Mesh* hexagonObject = new Mesh(name);

    if (!fill) {
        hexagonObject->SetDrawMode(GL_LINE_LOOP);
    }

    hexagonObject->InitFromData(vertices, indices);

    return hexagonObject;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float outerRadius,
    float innerRadius,
    glm::vec3 color,
    bool fill)
{   
    center.z = 4;
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color));

    // Calculate the coordinates of the five vertices of the pentagon.
    for (int i = 0; i < 5; ++i) {
        float angle = 2 * M_PI * i / 5 - 72.f;
        float starEdge = 2 * M_PI / 5;
        starEdge /= 2;
        glm::vec3 vertexPosition = center + glm::vec3(outerRadius * cos(angle), outerRadius * sin(angle), 4);
        vertices.push_back(VertexFormat(vertexPosition, color));
        float newAngle = angle + starEdge;
        glm::vec3 starPeak = center + glm::vec3(innerRadius * cos(newAngle), innerRadius * sin(newAngle), 4);
        vertices.push_back(VertexFormat(starPeak, color));
    }

    Mesh* pentagon = new Mesh(name);
    std::vector<unsigned int> indices = { 2, 3, 1,
                                        3, 0 , 1,
                                        3, 5, 0,
                                        3, 4, 5,
                                        0, 5, 7,
                                        5, 6, 7,
                                        0, 7, 9, 
                                        7, 8, 9,
                                        1, 0 ,9, 
                                        1, 9, 10};

    pentagon->InitFromData(vertices, indices);
    return pentagon;
}












