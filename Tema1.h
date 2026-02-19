#pragma once
#include <vector>
#include "components/simple_scene.h"

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
    protected:
       
        enum class Scene {Editor, Game};
        Scene curentScene;
        int matrix_copy[5][13];

        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        float sign = 1;
        float x_left;
        float y_left;
        float width_left;
        float height_left;
        float x_red;
        float y_red;
        float width_red;
        float height_red;
        float x_blue;
        float y_blue;
        float width_blue;
        float height_blue;
        float x_green;
        float y_green;
        float width_green;
        float height_green;
        float x_small_blue;
        float y_small_blue;
        float width_small_blue;
        float height_small_blue;
        float x_grey;
        float y_grey;
        float width_grey;
        float height_grey;

        float x_grey_2;
        float y_grey_2;
        float width_grey_2;
        float height_grey_2;

        float x_grey_3;
        float y_grey_3;
        float width_grey_3;
        float height_grey_3;

        float x_grey_4;
        float y_grey_4;
        float width_grey_4;
        float height_grey_4;

        bool isolated;
        int count;

        void Draw_left(float x_left, float y_left, float width_left, float height_left);
        void Draw_red(float x_red, float y_red, float width_red, float height_red);
        void Draw_blue(float x_blue, float y_blue, float width_blue, float height_blue);
        void Draw_green(float x_green, float y_green, float width_green, float height_green);
        void Draw_form(float x, float y, float width, float height);
        void Draw_small_blue(float x_small_blue, float y_small_blue, float width_small_blue, float height_small_blue);
        void Draw_grey(float x_grey, float y_grey, float width_grey, float height_grey);
        void Draw_drag(float x, float y);
        void Draw_squares_table();
        bool Delete_square(float click_x, float click_y);
        void Put_square(float release_x, float release_y);
        void Delete_green_square();
        void Draw_red_form(float x, float y, float width, float height);
        void UpdateGame(float deltaTimeSeconds);
        void UpdateEditor();
        void RenderForm(float x, float y, int matrix[5][13], int dimens, float scale);
        bool StartGame();
        bool BFS();
        void Draw_white_line(float x, float y, float width, float height);
        void Draw_squares_game();
        void Draw_letter_L(float x, float y, float size);
        void Draw_letter_E(float x, float y, float size);
        void Draw_letter_F(float x, float y, float size);
        void Draw_letter_T(float x, float y, float size);
        void Draw_letter_R(float x, float y, float size);
        void Draw_white_line_rotate(float x, float y, float width, float height);
        void Draw_letter_I(float x, float y, float size);
        void Draw_letter_G(float x, float y, float size);
        void Draw_letter_H(float x, float y, float size);
        void Draw_text_LEFT(float x, float y);
        void Draw_text_RIGHT(float x, float y);
        bool Line_Form();
        void Draw_ball(float x, float y, float radius);
        bool Valid_Form();
        void Draw_digit_0(float x, float y, float size);
        void Draw_digit_1(float x, float y, float size);
        void Draw_digit_2(float x, float y, float size);
        void Draw_digit_3(float x, float y, float size);
        void Draw_digit_4(float x, float y, float size);
        void Draw_digit_5(float x, float y, float size);
     
        void Draw_score_number(int number, float x, float y, float size);
        void Draw_green_line(float x, float y, float width, float height);
        void Draw_letter_L_green(float x, float y, float size);
        void Draw_letter_E_green(float x, float y, float size);
        void Draw_letter_F_green(float x, float y, float size);
        void Draw_letter_T_green(float x, float y, float size);
        void Draw_letter_R_green(float x, float y, float size);
        void Draw_letter_I_green(float x, float y, float size);
        void Draw_letter_G_green(float x, float y, float size);
        void Draw_letter_H_green(float x, float y, float size);
        void Draw_letter_W(float x, float y, float size);
        void Draw_letter_I_WIN(float x, float y, float size);
        void Draw_letter_N(float x, float y, float size);
        void Draw_text_LEFT_WIN(float x, float y);
        void Draw_text_RIGHT_WIN(float x, float y);

        float x_board_game;
        float y_board_game;
        float width_board_game;
        float height_board_game;
        float grosime_board_game;
        float y_form_left;
        float y_form_right;
        float speed_paddle;
        float scor_left;
        float scor_right;
        float scor_left_ant;
        float scor_right_ant;

        float ball_x;
        float ball_y;
        float ball_radius;
        float unghi;
        float y_paleta;
        float h_paleta;
        float v_x_bila;
        float v_y_bila;
        float viteza_bila;
        float segment_bila;
        bool ball_move;

        //minge 2
        float ball_radius_2;
        float ball_x_2;
        float ball_y_2;
        float viteza_bila_2;
        float v_x_bila_2;
        float v_y_bila_2;
        bool ball_move_2;
        float unghi_2;
        float delay_minge_2;
        bool runda_activa;
        float count_bile;

        float x_left_score;
        float y_left_score;
        float width_left_score;
        float height_left_score;
        float grosime_left_score;

        int matrix[5][13];
        int green_squares[11];
        int green_count;
        int is_drag;
        float drag_offset_x;
        float drag_offset_y;
        float drag_square_x;
        float drag_square_y;

        float anim_left;
        float anim_right;

    };
}