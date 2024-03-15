#pragma once

#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Star.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    squareSide = 125;
    mouse_x = 0;
    mouse_y = 0;
    time_for_star_spawn = 0;
    lifes = 3;
    number_of_points = 0;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    starx = 0;
    stary = 0;  

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    //initialie de vec with the above square
    above_squares.push_back(glm::vec3(0, 550, 0));
    above_squares.push_back(glm::vec3(200, 550, 0));
    above_squares.push_back(glm::vec3(400, 550, 0));
    above_squares.push_back(glm::vec3(600, 550, 0));

    //initialize the vec with green squares

    green_squares.push_back(glm::vec3(100, 0, 0));
    green_squares.push_back(glm::vec3(100, 150, 0));
    green_squares.push_back(glm::vec3(100, 300, 0));


    green_squares.push_back(glm::vec3(300, 0, 0));
    green_squares.push_back(glm::vec3(300, 150, 0));
    green_squares.push_back(glm::vec3(300, 300, 0));

    green_squares.push_back(glm::vec3(500, 0, 0));
    green_squares.push_back(glm::vec3(500, 150, 0));
    green_squares.push_back(glm::vec3(500, 300, 0));

    star_pressed = glm::vec3(-1, -1, 0);

    time_for_enemy_spawn = 0;
    all_colors.operator=({ "orange", "blue", "yellow", "purple" });
    three_lines.operator=({0 + 65, 150 + 65, 300 + 65});


    // Initialize angularStep
    angularStep = 0;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);

    Mesh* red_square = object2D::CreateSquare("red_square", corner, 75, glm::vec3(1, 0, 0), true);
    AddMeshToList(red_square);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, 50, 425, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);

    Mesh* diamond = object2D::CreateRhombus("diamond", corner, 30, 45, glm::vec3(255.0 / 255.0, 165.0 / 255.0, 0.0), true);
    AddMeshToList(diamond);

    Mesh* blue_gun = object2D::CreateRhombus("blue_gun", corner, 30, 45, glm::vec3(0, 0, 1), true);
    AddMeshToList(blue_gun);

    Mesh* yellow_gun = object2D::CreateRhombus("yellow_gun", corner, 30, 45, glm::vec3(1.0, 1.0, 0.0), true);
    AddMeshToList(yellow_gun);

    Mesh* purple_gun = object2D::CreateRhombus("purple_gun", corner, 30, 45, glm::vec3(1.0, 0.0, 1.0), true);
    AddMeshToList(purple_gun);



    Mesh* orange_star = object2D::CreateStar("orange_star", corner, 10, 20 , glm::vec3(255.0 / 255.0, 165.0 / 255.0, 0.0), true);
    AddMeshToList(orange_star);

    Mesh* blue_star = object2D::CreateStar("blue_star", corner, 10, 20, glm::vec3(0, 0, 1), true);
    AddMeshToList(blue_star);

    Mesh* yellow_star = object2D::CreateStar("yellow_star", corner, 10, 20, glm::vec3(1.0, 1.0, 0.0), true);
    AddMeshToList(yellow_star);

    Mesh* purple_star = object2D::CreateStar("purple_star", corner, 10, 20, glm::vec3(1.0, 0.0, 1.0), true);
    AddMeshToList(purple_star);


    Mesh* pink_star = object2D::CreateStar("pink_star", corner, 20, 40, glm::vec3(1.0, 0.0, 1.0), true);
    AddMeshToList(pink_star);

    Mesh* star = object2D::CreateStar("star", corner, 10, 20, glm::vec3(1.0, 1.0, 1.0), true);
    AddMeshToList(star);

    Mesh* empty_square = object2D::CreateSquare("empty_square", corner, squareSide, glm::vec3(1, 1, 1), false);
    AddMeshToList(empty_square);

    Mesh* blue_enemy = object2D::CreateHexagon("blue_enemy", corner, 50, glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), true);
    AddMeshToList(blue_enemy);

    Mesh* yellow_enemy = object2D::CreateHexagon("yellow_enemy", corner, 50, glm::vec3(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), true);
    AddMeshToList(yellow_enemy);


    Mesh* purple_enemy = object2D::CreateHexagon("purple_enemy", corner, 50, glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), true);
    AddMeshToList(purple_enemy);

    Mesh* orange_enemy = object2D::CreateHexagon("orange_enemy", corner, 50, glm::vec3(255.0 / 255.0, 165.0 / 255.0, 0.0), glm::vec3(1.0, 1.0, 1.0), true);
    AddMeshToList(orange_enemy);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void::Tema1::DrawScene() 
{

    if (lifes == 0) {
        cout << "am pierdut";
        exit(0);
    }

    if (lifes == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(800, 580);
        RenderMesh2D(meshes["red_square"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(925, 580);
        RenderMesh2D(meshes["red_square"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1050, 580);
        RenderMesh2D(meshes["red_square"], shaders["VertexColor"], modelMatrix);
    }
    else if (lifes == 2) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(800, 580);
		RenderMesh2D(meshes["red_square"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(925, 580);
		RenderMesh2D(meshes["red_square"], shaders["VertexColor"], modelMatrix);
    }
    else if (lifes == 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(800, 580);
		RenderMesh2D(meshes["red_square"], shaders["VertexColor"], modelMatrix);
	}

    int cont = 0;
    for (int i = 0; i < number_of_points; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(780 + cont, 540);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
        cont += 40;
    }




    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 300);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 150);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    //second row 
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 300);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 150);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    //thrid row

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 300);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 150);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    //rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    //star

    //top squares

    //first one with the gun and stars

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 550);
    RenderMesh2D(meshes["empty_square"], shaders["VertexColor"], modelMatrix);

    //gunns
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(45, 615);
    RenderMesh2D(meshes["diamond"], shaders["VertexColor"], modelMatrix);

    //star

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    //second top square

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 550);
    RenderMesh2D(meshes["empty_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(245, 615);
    RenderMesh2D(meshes["blue_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(220, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(260, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    /////third top sqare


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 550);
    RenderMesh2D(meshes["empty_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(445, 615);
    RenderMesh2D(meshes["yellow_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(420, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(460, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    //forth

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 550);
    RenderMesh2D(meshes["empty_square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(645, 615);
    RenderMesh2D(meshes["purple_gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(620, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(660, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 520);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
}


bool Tema1::hit_enemy(float x_star, float y_star, string color, float star_radius) {

    for (auto& j : all_enemies) {
        if (j.getColor() == color) {
            if (y_star == j.getYCenter() && glm::distance(glm::vec3(x_star, y_star, 0), (glm::vec3(j.getXCenter(), j.getYCenter(), 0))) < (star_radius + j.getRadius())) {
				j.setLives(j.getLives() - 1);
                if (j.getLives() == 0) {
					j.setFinished(true);
				}
				return true;
			}
		}
    }
    return false;
}

bool Tema1::starInFront(Gun currentGun) {
    int x_gun = currentGun.getPosition().x + 45;
    int y_gun = currentGun.getPosition().y + 65;
    for (auto i : all_enemies) {
        if (i.getColor() == currentGun.getColor()) {
            if (i.getYCenter() == y_gun) {
                if (i.getXCenter() > x_gun) {
					return true;
				}
			}
		}
	}
    return false;
}


void Tema1::Update(float deltaTimeSeconds)
{
    DrawScene();

    time_for_enemy_spawn += deltaTimeSeconds * 100;
    if (time_for_enemy_spawn > 500) {
        Enemy new_enemy;
		new_enemy.setColor(all_colors[rand() % 4]);
        int line = rand() % 3;
		new_enemy.setPosition(glm::vec3(1280, three_lines[line], 0));
		all_enemies.push_back(new_enemy);
		time_for_enemy_spawn = 0;
    }
    time_for_star_spawn += deltaTimeSeconds * 125;
    cout << time_for_star_spawn << "\n";

    if (time_for_star_spawn > 100) {
        for (int i = 0; i < 3; i++) {
            int line = rand () % 1280;
            int col = rand() % 720;
            if (stars_points_on_screen.size() < 10)
            {
                Star newStar;
                newStar.setXCenter(line);
                newStar.setYCenter(col);
                newStar.setRadius(40);
                stars_points_on_screen.push_back(newStar);
			}
        }
        time_for_star_spawn = 0;
	}
   /* cout << stars_points_on_screen.size() << "\n";*/

    for (auto it = stars_points_on_screen.begin(); it != stars_points_on_screen.end();) {
        if (star_pressed.x == it->getXCenter() && star_pressed.y == it->getYCenter() && (star_pressed.y != -1 && star_pressed.x != -1)) {
			it = stars_points_on_screen.erase(it);
            star_pressed = glm::vec3(-1, -1, 0);
		}
		else {
            it++;
        }
    }

    for (auto i : stars_points_on_screen) {
        modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(i.getXCenter(), i.getYCenter());
		RenderMesh2D(meshes["pink_star"], shaders["VertexColor"], modelMatrix);
    }

    for (auto& i : all_enemies) {
        if (i.getColor() == "orange") {
			modelMatrix = glm::mat3(1);
			float time = i.getTime();
			time += deltaTimeSeconds * 100;
			i.setTime(time);
			modelMatrix *= transform2D::Translate(-time, 0);
			modelMatrix *= transform2D::Translate(i.getPosition().x, i.getPosition().y);
			RenderMesh2D(meshes["orange_enemy"], shaders["VertexColor"], modelMatrix);
			glm::vec2 translation = glm::vec2(modelMatrix[2]);
			i.setXCenter(translation.x);
			i.setYCenter(translation.y);
		}
        else if (i.getColor() == "blue") {
			modelMatrix = glm::mat3(1);
			float time = i.getTime();
			time += deltaTimeSeconds * 100;
			i.setTime(time);
			modelMatrix *= transform2D::Translate(-time, 0);
			modelMatrix *= transform2D::Translate(i.getPosition().x, i.getPosition().y);
			RenderMesh2D(meshes["blue_enemy"], shaders["VertexColor"], modelMatrix);
			glm::vec2 translation = glm::vec2(modelMatrix[2]);
			i.setXCenter(translation.x);
			i.setYCenter(translation.y);
		}
        else if (i.getColor() == "yellow") {
			modelMatrix = glm::mat3(1);
			float time = i.getTime();
			time += deltaTimeSeconds * 100;
			i.setTime(time);
			modelMatrix *= transform2D::Translate(-time, 0);
			modelMatrix *= transform2D::Translate(i.getPosition().x, i.getPosition().y);
			RenderMesh2D(meshes["yellow_enemy"], shaders["VertexColor"], modelMatrix);
            glm::vec2 translation = glm::vec2(modelMatrix[2]);
            i.setXCenter(translation.x);
            i.setYCenter(translation.y);
        } 
        else if (i.getColor() == "purple") {
            modelMatrix = glm::mat3(1);
            float time = i.getTime();
            time += deltaTimeSeconds * 100;
            i.setTime(time);
            modelMatrix *= transform2D::Translate(-time, 0);
            modelMatrix *= transform2D::Translate(i.getPosition().x, i.getPosition().y);
            RenderMesh2D(meshes["purple_enemy"], shaders["VertexColor"], modelMatrix);
            glm::vec2 translation = glm::vec2(modelMatrix[2]);
            i.setXCenter(translation.x);
            i.setYCenter(translation.y);
        }
    }
    /*Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, 50, 425, glm::vec3(1, 0, 0), true);*/
    for (auto it = all_enemies.begin(); it != all_enemies.end();) {
        if (it->getFinished() == true || it->getLives() == 0 || it->getXCenter() < 50) {
            if (it->getXCenter() < 50)
            {
				lifes--;
			}
            it->setTime(0);
            enemy_slain.push_back(*it);
            it = all_enemies.erase(it);

		}
        else {
			it++;
		}
    }
    for (auto it = enemy_slain.begin(); it != enemy_slain.end();) {
        float time = it->getTime();
        if (1.0f / time > 0.1) {
            string color = it->getColor();
            float time = it->getTime();
            time += deltaTimeSeconds * 10;
            it->setTime(time);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(it->getXCenter(), it->getYCenter());
            if (time < 1) {
                modelMatrix *= transform2D::Scale(1, 1);
            }
            else {
                modelMatrix *= transform2D::Scale(1 / time, 1 / time);
            }
            glm::vec2 translation = glm::vec2(modelMatrix[2]);

            if (color == "orange") {
                RenderMesh2D(meshes["orange_enemy"], shaders["VertexColor"], modelMatrix);
            }
            else if (color == "blue") {
                RenderMesh2D(meshes["blue_enemy"], shaders["VertexColor"], modelMatrix);
            }
            else if (color == "yellow") {
                RenderMesh2D(meshes["yellow_enemy"], shaders["VertexColor"], modelMatrix);
            }
            else if (color == "purple") {
                RenderMesh2D(meshes["purple_enemy"], shaders["VertexColor"], modelMatrix);
            }
            it++;
        }
        else {
			it = enemy_slain.erase(it);
		}
	}

    

    if (color != "") {
        if (color == "orange") {
            // Do something specific for the color orange
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(mouse_x, mouse_y);
            RenderMesh2D(meshes["diamond"], shaders["VertexColor"], modelMatrix);
        }
        else if (color == "blue") {
            // Do something specific for the color blue
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(mouse_x, mouse_y);
            RenderMesh2D(meshes["blue_gun"], shaders["VertexColor"], modelMatrix);
        }
        else if (color == "yellow") {
            // Do something specific for the color yellow
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(mouse_x, mouse_y);
            RenderMesh2D(meshes["yellow_gun"], shaders["VertexColor"], modelMatrix);
        }
        else if (color == "purple") {
            // Do something specific for the color purple
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(mouse_x, mouse_y);
            RenderMesh2D(meshes["purple_gun"], shaders["VertexColor"], modelMatrix);
        }
    }
    else {
        int ok = 0;
        for (auto gun : guns_in_use) {
            if (gun.getPosition().x == save_green_square_drop.x && gun.getPosition().y == save_green_square_drop.y ||
                (save_green_square_drop.y == -1 && save_green_square_drop.x == -1)) {
                ok = 1;
            }
        }

        if (ok == 0 && save_color != "") {
            Gun newGun;
            newGun.setColor(save_color);
            newGun.setPosition(save_green_square_drop);
            guns_in_use.push_back(newGun);
        }
        save_color = "";
        save_green_square_drop = glm::vec3(-1, -1, 0);
    }

    for (auto i : guns_in_use) {
        /*cout << i.first;*/
        if (i.getColor() == "orange") {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(i.getPosition().x + 45, i.getPosition().y + 65);
            RenderMesh2D(meshes["diamond"], shaders["VertexColor"], modelMatrix);
        }
        else if (i.getColor() == "blue") {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(i.getPosition().x + 45, i.getPosition().y + 65);
            RenderMesh2D(meshes["blue_gun"], shaders["VertexColor"], modelMatrix);
        }
        else if (i.getColor() == "yellow") {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(i.getPosition().x + 45, i.getPosition().y + 65);
            RenderMesh2D(meshes["yellow_gun"], shaders["VertexColor"], modelMatrix);
        }
        else if (i.getColor() == "purple") {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(i.getPosition().x + 45, i.getPosition().y + 65);
            RenderMesh2D(meshes["purple_gun"], shaders["VertexColor"], modelMatrix);
        }
        else {
            continue;
        }
       
    }

    for (auto& i : guns_in_use) {
        if (starInFront(i) == true) {
            //i need to see if i have an enemy in front of me
            if (i.getColor() != "") {
                if (i.getFirstShoot() == true) {
                    /*cout << "new shooting star\n";*/
                    Star new_shooting_star;
                    new_shooting_star.setColor(i.getColor());
                    new_shooting_star.setPosition(i.getPosition());
                    new_shooting_star.setTimePassed(0);
                    i.shooting_stars.push_back(new_shooting_star);
                    i.setTimeToShoot(0);
                    i.setFirstShoot(false);
                }
                else {
                    if (i.getTimeToShoot() > 200) {
                        /* cout << "new shooting star if time gets by\n";*/
                        Star new_shooting_star;
                        new_shooting_star.setColor(i.getColor());
                        new_shooting_star.setPosition(i.getPosition());
                        new_shooting_star.setTimePassed(0);
                        i.shooting_stars.push_back(new_shooting_star);
                        i.setTimeToShoot(0);
                    }
                    else {
                        i.setTimeToShoot(i.getTimeToShoot() + deltaTimeSeconds * 100);
                    }
                }
            }
        }
    }

    //delete stars that are out of the screen

       for (auto &i : guns_in_use) {
           //cout << "am intrat" << "\n";
           auto& shootingStars = i.getShootingStars();
           for (auto it = shootingStars.begin(); it != shootingStars.end();) {
               /*cout << it->getXCenter() << " " << it->getYCenter() << "\n"; */
               if (it->getXCenter() > 1280 || hit_enemy(it->getXCenter(), it->getYCenter(), it->getColor(), it->getRadius()) == true) {
                   cout << "am sters\n";
                   it = i.getShootingStars().erase(it);
               }
               else {
                   it++;
               }
           }
       }

    for (auto &i : guns_in_use) {
        auto& shootingStars = i.getShootingStars();
        for (auto& j : shootingStars) {
            if (j.getColor() == "orange") {
                modelMatrix = glm::mat3(1);
                float new_time = j.getTimePassed();
                new_time += deltaTimeSeconds * 100;
                j.setTimePassed(new_time);
                modelMatrix *= transform2D::Translate(new_time, 0);
                modelMatrix *= transform2D::Translate(j.getPosition().x + 45, j.getPosition().y + 65);
                modelMatrix *= transform2D::Rotate(-new_time / 100);
                modelMatrix *= transform2D::Translate(0,0);
                RenderMesh2D(meshes["orange_star"], shaders["VertexColor"], modelMatrix);
                glm::vec2 translation = glm::vec2(modelMatrix[2]);
                j.setXCenter(translation.x);
                j.setYCenter(translation.y);
            }
            else if (j.getColor() == "blue") {
                modelMatrix = glm::mat3(1);
                float time = j.getTimePassed();
                time += deltaTimeSeconds * 100;
                j.setTimePassed(time);
                modelMatrix *= transform2D::Translate(time, 0);
                modelMatrix *= transform2D::Translate(j.getPosition().x + 45, j.getPosition().y + 65);
                modelMatrix *= transform2D::Rotate(-time / 100);
                modelMatrix *= transform2D::Translate(0, 0);
                RenderMesh2D(meshes["blue_star"], shaders["VertexColor"], modelMatrix);
                glm::vec2 translation = glm::vec2(modelMatrix[2]);
                j.setXCenter(translation.x);
                j.setYCenter(translation.y);
            }
            else if (j.getColor() == "yellow") {
                modelMatrix = glm::mat3(1);
                float time = j.getTimePassed();
                time += deltaTimeSeconds * 100;
                j.setTimePassed(time);
                modelMatrix *= transform2D::Translate(time, 0);
                modelMatrix *= transform2D::Translate(j.getPosition().x + 45, j.getPosition().y + 65);
                modelMatrix *= transform2D::Rotate(-time / 100);
                modelMatrix *= transform2D::Translate(0, 0);
                RenderMesh2D(meshes["yellow_star"], shaders["VertexColor"], modelMatrix);
                glm::vec2 translation = glm::vec2(modelMatrix[2]);
                j.setXCenter(translation.x);
                j.setYCenter(translation.y);
            }
            else if (j.getColor() == "purple") {
                modelMatrix = glm::mat3(1);
                float time = j.getTimePassed();
                time += deltaTimeSeconds * 100;
                j.setTimePassed(time);
                modelMatrix *= transform2D::Translate(time, 0);
                modelMatrix *= transform2D::Translate(j.getPosition().x + 45, j.getPosition().y + 65);
                modelMatrix *= transform2D::Rotate(-time / 100);
                modelMatrix *= transform2D::Translate(0, 0);
                RenderMesh2D(meshes["purple_star"], shaders["VertexColor"], modelMatrix);
                glm::vec2 translation = glm::vec2(modelMatrix[2]);
                j.setXCenter(translation.x);
                j.setYCenter(translation.y);
            }
        }
    }

    //enemy hit with a gun and then de deletion of a gun
    for (auto it = guns_in_use.begin(); it != guns_in_use.end();) {
        if (enemy_hit_gun(it->getPosition().x, it->getPosition().y) == true || 
            (delete_gun.x == it->getPosition().x && delete_gun.y == it->getPosition().y)) {
            if (delete_gun.x == it->getPosition().x && delete_gun.y == it->getPosition().y) {
				delete_gun = glm::vec3(-1, -1, 0);
			}
            gun_slain.push_back(*it);
            it = guns_in_use.erase(it);
        }
        else {
            it++;
        }
    }

    //animation for gun slain

    for (auto it = gun_slain.begin(); it != gun_slain.end();) {
        float time = it->getTime();
        if (1.0f / time > 0.1) {
            string color = it->getColor();
            float time = it->getTime();
            time += deltaTimeSeconds * 10;
            it->setTime(time);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(it->getPosition().x + 45, it->getPosition().y + 65);
            if (time < 1) {
                modelMatrix *= transform2D::Scale(1, 1);
            }
            else {
                modelMatrix *= transform2D::Scale(1 / time, 1 / time);
            }
            glm::vec2 translation = glm::vec2(modelMatrix[2]);

            if (color == "orange") {
                RenderMesh2D(meshes["diamond"], shaders["VertexColor"], modelMatrix);
            }
            else if (color == "blue") {
                RenderMesh2D(meshes["blue_gun"], shaders["VertexColor"], modelMatrix);
            }
            else if (color == "yellow") {
                RenderMesh2D(meshes["yellow_gun"], shaders["VertexColor"], modelMatrix);
            }
            else if (color == "purple") {
                RenderMesh2D(meshes["purple_gun"], shaders["VertexColor"], modelMatrix);
            }
            it++;
        }
        else {
            it = gun_slain.erase(it);
        }
    }




}

bool Tema1::enemy_hit_gun(float x, float y) {
    for (auto i : all_enemies) {
        if (glm::distance(glm::vec3(i.getXCenter(), i.getYCenter(), 0), glm::vec3(x + 45, y + 65, 0)) < 75) {
            cout << "s-au lovit";
			return true;
		}
    }
    return false;

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    float scene_y = 720 - mouseY;

    mouse_y = scene_y;
    mouse_x = mouseX;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    float scene_y = 720 - mouseY;
    float scene_x = mouseX;

    for (auto i : above_squares) {
        float x_square = i.x;
        float y_square = i.y;

        if ((x_square < scene_x && scene_x < x_square + 125) && (y_square < scene_y && scene_y < y_square + 125) && button == 1)
        {
            if (x_square == 0 && y_square == 550) {
                if (number_of_points >= 1) {
                    number_of_points--;
                    color = "orange";
                }
            }
            else if (x_square == 200 && y_square == 550) {
                if (number_of_points >= 2) {
                    number_of_points-= 2;
                    color = "blue";
                }
            }
            else if (x_square == 400 && y_square == 550) {
                if (number_of_points >= 2) {
                    number_of_points-= 2;
                    color = "yellow";
                }
            }
            else if (x_square == 600 && y_square == 550) {
                if (number_of_points >= 3) {
                    number_of_points -= 3;
                    color = "purple";
                }
            }
        }
    }

    for (auto i : guns_in_use) {
        float current_x = i.getPosition().x;
        float current_y = i.getPosition().y;
        if ((current_x < scene_x && scene_x < current_x + 125) && (current_y < scene_y && scene_y < current_y + 125) && button == 2) {
			delete_gun = glm::vec3(current_x, current_y, 0);
		}
    }
    for (auto i : stars_points_on_screen) {
        float current_x = i.getXCenter();
		float current_y = i.getYCenter();
        if ((current_x - 40 < scene_x && scene_x < current_x + 40) && (current_y - 40 < scene_y && scene_y < current_y + 40) && button == 1) {
            if (number_of_points < 10) {
                number_of_points++;
            }
            star_pressed = glm::vec3(current_x, current_y, 0);
		}

    }
 
    //}
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    float scene_y = 720 - mouseY;
    int ok = 0;
    for (auto i : green_squares) {
        int x = i.x;
        int y = i.y;
        if ((x < mouseX && mouseX < x + 125) && (y < scene_y && scene_y < y + 125)) {
            save_green_square_drop = i;
            save_color = color;
            color = "";
            ok = 1;
        }
    }
    if (ok == 0) {
        if (color == "orange") {
            number_of_points += 1;
        }
        else if (color == "blue") {
			number_of_points += 2;
        }
        else if (color == "yellow") {
			number_of_points += 2;
        }
        else if (color == "purple") {
			number_of_points += 3;
		}
        color = "";
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
