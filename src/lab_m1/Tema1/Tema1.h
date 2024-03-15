#pragma once

#include "components/simple_scene.h"
#include "Star.h"
#include <vector>
#include "Gun.h"
#include "Enemy.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void DrawScene();
        bool hit_enemy(float, float, string, float radius);
        bool starInFront(Gun);
        bool enemy_hit_gun(float, float);
    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        std::vector<glm::vec3> above_squares;
        std::vector<glm::vec3> green_squares;
        std::vector<Gun> guns_in_use;
        std::vector<Enemy> all_enemies;
        std::vector<Enemy> enemy_slain;
        float squareSide;
        std::vector<string> all_colors;
        std::vector<float> three_lines;
        int mouse_y, mouse_x;
        std::string color;
        std::string save_color;
        glm::vec3 save_green_square_drop;
        glm::vec3 delete_gun;
        int starx, stary;
        float time_for_enemy_spawn;
        std::vector<Gun> gun_slain;
        int time_for_star_spawn;

        std::vector<Star> stars_points_on_screen;
        int lifes;
        int number_of_points;
        glm::vec3 star_pressed;
        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1

