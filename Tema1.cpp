#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <queue>
#include<cstdlib>
#include <ctime>


#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    curentScene = Scene::Editor;

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 1;

    x_left = 0;
    y_left = 0;
    width_left = resolution.x / 6.0f;
    height_left = resolution.y / 4.0f;

    x_red = width_left;
    y_red = 0;
    width_red = resolution.x - width_left;
    height_red = resolution.y;
    Mesh* red_line = object2D::CreateSquare("red_line", corner, squareSide, glm::vec3(1, 0, 0));
    AddMeshToList(red_line);

    Mesh* line_left = object2D::CreateSquare("line_left", corner, squareSide, glm::vec3(1, 0, 0));
    AddMeshToList(line_left);

    x_blue = width_left + resolution.x / 20.0f;
    y_blue = resolution.y / 15.0f;
    width_blue = (resolution.x * 3.0f) / 4.0f;
    height_blue = (resolution.y * 2.0f) / 3.0f;
    Mesh* blue_square = object2D::CreateSquare("blue_square", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(blue_square);

    x_green = width_left + resolution.x / 50.f;
    y_green = y_blue + height_blue + height_left / 2 - 25;
    width_green = resolution.y / 10.f - 20;
    height_green = resolution.y / 10.f - 20;
    Mesh* green_square = object2D::CreateSquare("green_square", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(green_square);

    Mesh* new_form = object2D::CreateForm("new_form", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(new_form);

    Mesh* new_form_red = object2D::CreateForm("new_form_red", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(new_form_red);

    x_small_blue = width_left + width_blue / 10.0f;
    y_small_blue = height_blue / 4.0f;
    width_small_blue = width_blue / 19.0f;
    height_small_blue = width_small_blue;
    Mesh* blue_small = object2D::CreateSquare("blue_small", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(blue_small);

    x_grey = x_left + width_left / 2 - 35;
    y_grey = height_left / 2 - 35;
    width_grey = width_small_blue + width_small_blue / 2;
    height_grey = width_grey;

    Mesh* grey_square = object2D::CreateSquare("grey_square", corner, squareSide, glm::vec3(0.7, 0.7, 0.7), true);
    AddMeshToList(grey_square);

    x_grey_2 = x_left + width_left / 2 - 35;
    y_grey_2 = height_left + height_left / 2 - 35;
    width_grey_2 = width_small_blue + width_small_blue / 2;
    height_grey_2 = width_grey_2;

    Mesh* yellow_square = object2D::CreateSquare("yellow_square", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellow_square);

    x_grey_3 = x_left + width_left / 2 - 35;
    y_grey_3 = 2 * height_left + height_left / 2 - 35;
    width_grey_3 = width_small_blue + width_small_blue / 2;
    height_grey_3 = width_grey_3;

    Mesh* orange_square = object2D::CreateSquare("orange_square", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(orange_square);

    x_grey_4 = x_left + width_left / 2 - 35;
    y_grey_4 = 3 * height_left + height_left / 2 - 35;
    width_grey_4 = width_small_blue + width_small_blue / 2;
    height_grey_4 = width_grey_4;

    Mesh* purple_square = object2D::CreateSquare("purple_square", corner, squareSide, glm::vec3(0.5, 0, 0.5), true);
    AddMeshToList(purple_square);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            matrix[i][j] = 0;
            matrix_copy[i][j] = 0;
        }
    }

    for (int i = 0; i < 11; i++) {
        green_squares[i] = 1;
    }
    green_count = 11;

    count = 0;
    isolated = false;

    is_drag = 0;
    drag_square_x = 0;
    drag_square_y = 0;
    drag_offset_x = 0;
    drag_offset_y = 0;

    grosime_board_game = 5;
    x_board_game = resolution.x / 5 - 50;
    y_board_game = 30;
    width_board_game = resolution.x - 2 * x_board_game;
    height_board_game = resolution.y - y_board_game * 2;
    Mesh* white_line = object2D::CreateSquare("white_line", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(white_line);

    x_left_score = 10;
    y_left_score = resolution.y - 50;
    y_form_left = resolution.y / 9;
    y_form_right = resolution.y / 9;
    speed_paddle = 850.0f;

    Mesh* ball = object2D::CreateCircle("ball", corner, squareSide, glm::vec3(0.7, 0.9, 0.9), true);
    AddMeshToList(ball);

    ball_radius = 14;
    ball_x = resolution.x / 2;
    ball_y = resolution.y / 2;
    viteza_bila = 200.0f;
    v_x_bila = 0.0f;
    v_y_bila = 0.0f;
    ball_move = false;
    unghi = 0.0f;
    scor_left = 0;
    scor_right = 0;
    scor_left_ant = 0;
    scor_right_ant = 0;

    ball_radius_2 = 14;
    ball_x_2 = resolution.x / 2;
    ball_y_2 = resolution.y / 2;
    viteza_bila_2 = 200.0f;
    v_x_bila_2 = 0.0f;
    v_y_bila_2 = 0.0f;
    ball_move_2 = false;
    unghi_2 = 0.0f;
    count_bile = 0;
    delay_minge_2 = 0.0f;
    runda_activa = false;

    Mesh* green_line = object2D::CreateSquare("green_line", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(green_line);

    anim_left = 0;
    anim_right = 0;
}


void Tema1::FrameStart()
{

    glClearColor(0, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (curentScene == Scene::Editor) {
        UpdateEditor();
    }
    else if (curentScene == Scene::Game) {
        UpdateGame(deltaTimeSeconds);
    }
}


void Tema1::FrameEnd()
{
}


void Tema1::UpdateGame(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    glClearColor(0.08, 0.12, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, resolution.x, resolution.y);

    if (anim_left > 0) {
        anim_left -= deltaTimeSeconds;
    }
    if (anim_right > 0) {
        anim_right -= deltaTimeSeconds;
    }
    Draw_ball(ball_x, ball_y, ball_radius);
    if (count_bile == 1) {
        Draw_ball(ball_x, ball_y, ball_radius);
    }
    else if (count_bile == 2) {
        Draw_ball(ball_x, ball_y, ball_radius);
        if (ball_move_2) {
            Draw_ball(ball_x_2, ball_y_2, ball_radius_2);
        }
    }

    float dimens = 40;
    float form_left_x = resolution.x / 5;
    float form_right_x = resolution.x - (resolution.x / 4);

    float scale_left;
    float scale_right;
    if (anim_left > 0) {
        scale_left = 1 + anim_left * 0.5;
    }
    else scale_left = 1;

    if (anim_right > 0) {
        scale_right = 1 + anim_right * 0.5;
    }
    else scale_right = 1;

    RenderForm(form_left_x, y_form_left, matrix_copy, dimens, scale_left);

    RenderForm(form_right_x, y_form_right, matrix_copy, dimens, scale_right);

    Draw_white_line(x_board_game, y_board_game, grosime_board_game, height_board_game);
    Draw_white_line(x_board_game + width_board_game - grosime_board_game, y_board_game, grosime_board_game, height_board_game);
    Draw_white_line(x_board_game, y_board_game + height_board_game - grosime_board_game, width_board_game, grosime_board_game);
    Draw_white_line(x_board_game, y_board_game, width_board_game, grosime_board_game);
    Draw_squares_game();
    Draw_text_LEFT(x_left_score, y_left_score);
    Draw_score_number((int)scor_left, x_left_score + 35, y_left_score - 80, 35);
    Draw_text_RIGHT(resolution.x - 200, y_left_score);
    Draw_score_number((int)scor_right, resolution.x - 135, y_left_score - 80, 35);

    if (scor_left == 5) {
        glClearColor(0.35, 0.06, 0.06, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, resolution.x, resolution.y);

        float text_x = resolution.x / 2 - 400;
        float text_y = resolution.y / 2 - 50;
        Draw_text_LEFT_WIN(text_x, text_y);
        return;
    }
    else if (scor_right == 5) {
        glClearColor(0.35, 0.06, 0.06, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, resolution.x, resolution.y);

        float text_x = resolution.x / 2 - 450;
        float text_y = resolution.y / 2 - 50;
        Draw_text_RIGHT_WIN(text_x, text_y);
        return;
    }

}


void Tema1::Draw_ball(float x, float y, float radius)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(radius, radius);
    RenderMesh2D(meshes["ball"], shaders["VertexColor"], m);
}


void Tema1::RenderForm(float x, float y, int matrix[5][13], int dimens, float scale)
{
    int count = 0;

    int linie_ant = -1;
    int count_i = 0;
    int max_i = 0;
    int max_j = 0;
    int ok = 1;

    for (int i = 0; i < 5 && (ok == 1); i++) {
        for (int j = 0; j < 13; j++) {
            if (matrix[i][j] != 0) {
                max_j++;
                ok = 0;
            }
        }
    }

    ok = 1;

    for (int j = 0; j < 13 && (ok == 1); j++) {
        for (int i = 0; i < 5; i++) {
            if (matrix[i][j] != 0) {
                max_i++;
                ok = 0;
            }
        }
    }

    if (max_j >= max_i) {
        for (int i = 0; i < 5; i++) {
            count = 0;
            for (int j = 0; j < 13; j++) {

                if (matrix[i][j] != 0) {
                    if (linie_ant == -1) {
                        linie_ant = i;
                    }
                    else if (linie_ant != i) {
                        count_i++;
                        linie_ant = i;
                    }
                    float form_x = x + count_i * dimens;
                    float form_y = y + count * dimens;
                    count++;
                    if (max_i == 3 && max_j == 3) {
                        form_x -= 30;
                    }
                    glm::mat3 m = transform2D::Translate(form_x, form_y);
                    m *= transform2D::Scale(dimens * scale, dimens * scale);

                    if (matrix[i][j] == 1) {
                        RenderMesh2D(meshes["grey_square"], shaders["VertexColor"], m);
                    }
                    else if (matrix[i][j] == 2) {
                        RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], m);
                    }
                    else if (matrix[i][j] == 3) {
                        RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], m);
                    }
                    else if (matrix[i][j] == 4) {
                        RenderMesh2D(meshes["purple_square"], shaders["VertexColor"], m);
                    }
                }
            }
        }
    }
    else {
        int count_j = 0;
        int coloana_ant = -1;

        for (int j = 0; j < 13; j++) {
            int count = 0;
            for (int i = 0; i < 5; i++) {
                if (matrix[i][j] != 0) {
                    if (coloana_ant == -1) {
                        coloana_ant = j;
                    }
                    else if (coloana_ant != j) {
                        count_j++;
                        coloana_ant = j;
                    }

                    float form_x = x + count_j * dimens;
                    float form_y = y + count * dimens;
                    count++;

                    glm::mat3 m = transform2D::Translate(form_x, form_y);
                    m *= transform2D::Scale(dimens * scale, dimens * scale);

                    if (matrix[i][j] == 1) {
                        RenderMesh2D(meshes["grey_square"], shaders["VertexColor"], m);
                    }
                    else if (matrix[i][j] == 2) {
                        RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], m);
                    }
                    else if (matrix[i][j] == 3) {
                        RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], m);
                    }
                    else if (matrix[i][j] == 4) {
                        RenderMesh2D(meshes["purple_square"], shaders["VertexColor"], m);
                    }
                }
            }
        }
    }
}


void Tema1::Draw_white_line(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["white_line"], shaders["VertexColor"], m);
}


void Tema1::Draw_white_line_rotate(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Rotate(M_PI / 4);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["white_line"], shaders["VertexColor"], m);
}


void Tema1::Draw_squares_game()
{
    glm::ivec2 resolution = window->GetResolution();
    float middle_x = x_board_game + width_board_game / 2 - grosime_board_game - 3.5;
    float square_size = 40;
    float jump = 21.5;

    for (float y = y_board_game; y < y_board_game + height_board_game; y += square_size + jump) {
        Draw_white_line(middle_x, y, square_size / 2, square_size);
    }
}


void Tema1::Draw_green_line(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["green_line"], shaders["VertexColor"], m);
}


void Tema1::Draw_letter_L(float x, float y, float size)
{
    Draw_white_line(x, y, 5, size);
    Draw_white_line(x, y, size, 5);
}


void Tema1::Draw_letter_E(float x, float y, float size)
{
    Draw_white_line(x, y, 5, size);
    Draw_white_line(x, y, size, 5);
    Draw_white_line(x, y + size / 2, size * 0.7f, 5);
    Draw_white_line(x, y + size - 5, size, 5);
}


void Tema1::Draw_letter_F(float x, float y, float size)
{
    Draw_white_line(x, y, 5, size);
    Draw_white_line(x, y + size / 2, size * 0.7f, 5);
    Draw_white_line(x, y + size - 5, size, 5);
}


void Tema1::Draw_letter_T(float x, float y, float size)
{
    Draw_white_line(x, y + size - 5, size, 5);
    Draw_white_line(x + size / 2 - 2.5f, y, 5, size);
}


void Tema1::Draw_letter_R(float x, float y, float size)
{
    Draw_white_line(x + 5, y, 5, size);
    Draw_white_line(x + 5, y + size - 5, size * 0.7f, 5);
    Draw_white_line(x + 5 + size * 0.7f - 5, y + size / 2, 5, size / 2);
    Draw_white_line(x + 5, y + size / 2, size * 0.7f, 5);
    Draw_white_line_rotate(x + 10 + size * 0.5f, y, 5, size / 2 + 6);
}


void Tema1::Draw_letter_I(float x, float y, float size)
{
    Draw_white_line(x, y, size, 5);
    Draw_white_line(x + size / 2 - 2.5f, y, 5, size);
    Draw_white_line(x, y + size - 5, size, 5);
}


void Tema1::Draw_letter_G(float x, float y, float size)
{
    Draw_white_line(x, y, 5, size);
    Draw_white_line(x, y, size, 5);
    Draw_white_line(x, y + size - 5, size, 5);
    Draw_white_line(x + size - 5, y, 5, size / 2);
    Draw_white_line(x + size / 2, y, size / 2, 5);
}


void Tema1::Draw_letter_H(float x, float y, float size)
{
    Draw_white_line(x, y, 5, size);
    Draw_white_line(x + size - 5, y, 5, size);
    Draw_white_line(x, y + size / 2, size, 5);
}


void Tema1::Draw_text_LEFT(float x, float y)
{
    float letter_size = 30;
    float spacing = letter_size + 5;

    Draw_letter_L(x, y, letter_size);
    Draw_letter_E(x + spacing, y, letter_size);
    Draw_letter_F(x + spacing * 2, y, letter_size);
    Draw_letter_T(x + spacing * 3, y, letter_size);
}


void Tema1::Draw_text_RIGHT(float x, float y)
{
    float letter_size = 30;
    float spacing = letter_size + 5;

    Draw_letter_R(x, y, letter_size);
    Draw_letter_I(x + spacing, y, letter_size);
    Draw_letter_G(x + spacing * 2, y, letter_size);
    Draw_letter_H(x + spacing * 3, y, letter_size);
    Draw_letter_T(x + spacing * 4, y, letter_size);
}


void Tema1::Draw_digit_0(float x, float y, float size)
{
    Draw_white_line(x, y, 5, size);
    Draw_white_line(x + size - 5, y, 5, size);
    Draw_white_line(x, y, size, 5);
    Draw_white_line(x, y + size - 5, size, 5);
}


void Tema1::Draw_digit_1(float x, float y, float size)
{
    Draw_white_line(x + size / 2 - 2.5f, y, 5, size);
}


void Tema1::Draw_digit_2(float x, float y, float size)
{
    Draw_white_line(x, y + size - 5, size, 5);
    Draw_white_line(x + size - 5, y + size / 2, 5, size / 2);
    Draw_white_line(x, y + size / 2, size, 5);
    Draw_white_line(x, y, 5, size / 2);
    Draw_white_line(x, y, size, 5);
}


void Tema1::Draw_digit_3(float x, float y, float size)
{
    Draw_white_line(x, y + size - 5, size, 5);
    Draw_white_line(x, y + size / 2, size, 5);
    Draw_white_line(x, y, size, 5);
    Draw_white_line(x + size - 5, y, 5, size);
}


void Tema1::Draw_digit_4(float x, float y, float size)
{
    Draw_white_line(x, y + size / 2, 5, size / 2);
    Draw_white_line(x, y + size / 2, size, 5);
    Draw_white_line(x + size - 5, y, 5, size);
}


void Tema1::Draw_digit_5(float x, float y, float size)
{
    Draw_white_line(x, y + size - 5, size, 5);
    Draw_white_line(x, y + size / 2, 5, size / 2);
    Draw_white_line(x, y + size / 2, size, 5);
    Draw_white_line(x + size - 5, y, 5, size / 2);
    Draw_white_line(x, y, size, 5);
}

void Tema1::Draw_score_number(int number, float x, float y, float size)
{
    if (number < 0 || number > 9) {
        return;
    }

    switch (number) {
    case 0: Draw_digit_0(x, y, size); break;
    case 1: Draw_digit_1(x, y, size); break;
    case 2: Draw_digit_2(x, y, size); break;
    case 3: Draw_digit_3(x, y, size); break;
    case 4: Draw_digit_4(x, y, size); break;
    case 5: Draw_digit_5(x, y, size); break;
    }
}


void Tema1::Draw_letter_L_green(float x, float y, float size)
{
    Draw_green_line(x, y, 10, size);
    Draw_green_line(x, y, size, 10);
}

void Tema1::Draw_letter_E_green(float x, float y, float size)
{
    Draw_green_line(x, y, 10, size);
    Draw_green_line(x, y, size, 10);
    Draw_green_line(x, y + size / 2, size * 0.7f, 10);
    Draw_green_line(x, y + size - 10, size, 10);
}

void Tema1::Draw_letter_F_green(float x, float y, float size)
{
    Draw_green_line(x, y, 10, size);
    Draw_green_line(x, y + size / 2, size * 0.7f, 10);
    Draw_green_line(x, y + size - 10, size, 10);
}

void Tema1::Draw_letter_T_green(float x, float y, float size)
{
    Draw_green_line(x, y + size - 10, size, 10);
    Draw_green_line(x + size / 2 - 5.0f, y, 10, size);
}

void Tema1::Draw_letter_R_green(float x, float y, float size)
{
    Draw_green_line(x + 35, y, 10, size);
    Draw_green_line(x + 35, y + size - 10, size * 0.7f, 10);
    Draw_green_line(x + 35 + size * 0.7f - 10, y + size / 2, 10, size / 2);
    Draw_green_line(x + 35, y + size / 2, size * 0.7f, 10);
    glm::mat3 m;
    m = transform2D::Translate(x + 45 + size * 0.5f - 10, y);
    m *= transform2D::Rotate(M_PI / 4);
    m *= transform2D::Scale(10, size / 2 + 20);
    RenderMesh2D(meshes["green_line"], shaders["VertexColor"], m);
}

void Tema1::Draw_letter_I_green(float x, float y, float size)
{
    Draw_green_line(x, y, size, 10);
    Draw_green_line(x + size / 2 - 5.0f, y, 10, size);
    Draw_green_line(x, y + size - 10, size, 10);
}

void Tema1::Draw_letter_G_green(float x, float y, float size)
{
    Draw_green_line(x, y, 10, size);
    Draw_green_line(x, y, size, 10);
    Draw_green_line(x, y + size - 10, size, 10);
    Draw_green_line(x + size - 10, y, 10, size / 2);
    Draw_green_line(x + size / 2, y, size / 2, 10);
}

void Tema1::Draw_letter_H_green(float x, float y, float size)
{
    Draw_green_line(x, y, 10, size);
    Draw_green_line(x + size - 10, y, 10, size);
    Draw_green_line(x, y + size / 2, size, 10);
}

void Tema1::Draw_letter_W(float x, float y, float size)
{
    Draw_green_line(x - 50, y, 10, size);
    Draw_green_line(x, y, 10, size);
    Draw_green_line(x + 50, y, 10, size);
    glm::mat3 m1;
    m1 = transform2D::Translate(x + 50, y);
    m1 *= transform2D::Rotate(M_PI / 2);
    m1 *= transform2D::Scale(10, size * 0.6f + 40);
    RenderMesh2D(meshes["green_line"], shaders["VertexColor"], m1);
}

void Tema1::Draw_letter_I_WIN(float x, float y, float size)
{
    Draw_green_line(x - 50, y, size, 10);
    Draw_green_line(x + size / 2 - 5.0f - 50, y, 10, size);
    Draw_green_line(x - 50, y + size - 10, size, 10);
}

void Tema1::Draw_letter_N(float x, float y, float size)
{
    Draw_green_line(x - 50, y, 10, size);
    glm::mat3 m1;
    m1 = transform2D::Translate(x + 45, y);
    m1 *= transform2D::Rotate(M_PI / 3.9f);
    m1 *= transform2D::Scale(10, size * 0.6f + 74);
    RenderMesh2D(meshes["green_line"], shaders["VertexColor"], m1);
    Draw_green_line(x + size - 55, y, 10, size);
}

void Tema1::Draw_text_LEFT_WIN(float x, float y)
{
    float letter_size = 100;
    float spacing = letter_size + 18;
    Draw_letter_L_green(x, y, letter_size);
    Draw_letter_E_green(x + spacing, y, letter_size);
    Draw_letter_F_green(x + spacing * 2, y, letter_size);
    Draw_letter_T_green(x + spacing * 3, y, letter_size);
    Draw_letter_W(x + spacing * 5 + 3, y, letter_size);
    Draw_letter_I_WIN(x + spacing * 6 + 3, y, letter_size);
    Draw_letter_N(x + spacing * 7 + 3, y, letter_size);
}

void Tema1::Draw_text_RIGHT_WIN(float x, float y)
{
    float letter_size = 100;
    float spacing = letter_size + 18;
    Draw_letter_R_green(x, y, letter_size);
    Draw_letter_I_green(x + spacing, y, letter_size);
    Draw_letter_G_green(x + spacing * 2, y, letter_size);
    Draw_letter_H_green(x + spacing * 3, y, letter_size);
    Draw_letter_T_green(x + spacing * 4, y, letter_size);
    Draw_letter_W(x + spacing * 6 + 3, y, letter_size);
    Draw_letter_I_WIN(x + spacing * 7 + 3, y, letter_size);
    Draw_letter_N(x + spacing * 8 + 3, y, letter_size);
}

void Tema1::UpdateEditor()
{
    for (int i = 0; i < 4; i++) {
        Draw_left(x_left, y_left + (i * height_left), width_left, height_left);
    }
    Draw_blue(x_blue, y_blue, width_blue, height_blue);
    isolated = BFS();
    for (int i = 0; i < 11; i++) {
        int space = 97;
        if (green_squares[i] == 1) {
            if (i == 10) {
                if (count > 10 || count == 0 || isolated || (!Valid_Form())) {
                    Draw_red_form(x_green + space * i, y_green, width_green, height_green);
                }
                else {
                    Draw_form(x_green + space * i, y_green, width_green, height_green);
                }
            }
            else {
                Draw_green(x_green + space * i, y_green, width_green, height_green);
            }
        }
    }
    Draw_red(x_red, y_red, width_red, height_red);
    for (int i = 0; i < 5; i++) {
        int space = 70;
        for (int j = 0; j < 13; j++) {
            if (matrix[i][j] == 0) {
                Draw_small_blue(x_small_blue + space * j, y_small_blue + space * i, width_small_blue, height_small_blue);
            }
        }
    }
    Draw_squares_table();

    if (is_drag != 1) {
        Draw_grey(x_grey, y_grey, width_grey, height_grey);
    }

    if (is_drag != 2) {
        glm::mat3 m2 = transform2D::Translate(x_grey_2, y_grey_2);
        m2 *= transform2D::Scale(width_grey_2, height_grey_2);
        RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], m2);
    }

    if (is_drag != 3) {
        glm::mat3 m3 = transform2D::Translate(x_grey_3, y_grey_3);
        m3 *= transform2D::Scale(width_grey_3, height_grey_3);
        RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], m3);
    }

    if (is_drag != 4) {
        glm::mat3 m4 = transform2D::Translate(x_grey_4, y_grey_4);
        m4 *= transform2D::Scale(width_grey_4, height_grey_4);
        RenderMesh2D(meshes["purple_square"], shaders["VertexColor"], m4);
    }

    if (is_drag) {
        Draw_drag(drag_square_x, drag_square_y);
    }

    if (is_drag) {
        Draw_drag(drag_square_x, drag_square_y);
    }


}


bool Tema1::StartGame()
{
    if (count == 0 || count > 10 || isolated || !(Valid_Form())) {
        return false;
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            matrix_copy[i][j] = matrix[i][j];
        }
    }

    return true;
}


bool Tema1::Valid_Form()
{
    int cnt_ant = 0;
    int cnt;
    int ok = 1;
    for (int i = 0; i < 5; i++) {
        cnt = 0;
        for (int j = 0; j < 13; j++) {
            if (matrix[i][j] != 0) {
                cnt++;
            }
        }
        if (cnt_ant == 0) {
            if (cnt != 0) {
                cnt_ant = cnt;
            }
        }
        else if (cnt_ant != cnt && (cnt != 0)) {
            ok = 0;
        }
    }

    cnt_ant = 0;
    for (int i = 0; i < 13; i++) {
        cnt = 0;
        for (int j = 0; j < 5; j++) {
            if (matrix[j][i] != 0) {
                cnt++;
            }
        }
        if (cnt_ant == 0) {
            if (cnt != 0) {
                cnt_ant = cnt;
            }
        }
        else if (cnt_ant != cnt && (cnt != 0)) {
            ok = 0;
        }
    }
    if (ok == 1) return true;
    return false;
}


bool Tema1::BFS()
{
    if (count == 0) return false;
    if (count == 1) return false;

    int visited[5 * 13] = { 0 };
    int adjList[65][4];
    int adjCount[65] = { 0 };
    int node;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            if (matrix[i][j] != 0) {
                node = i * 13 + j;
                int vecini = 0;

                if (i > 0 && matrix[i - 1][j] != 0) {
                    adjList[node][vecini] = (i - 1) * 13 + j;
                    vecini++;
                }
                if (i < 4 && matrix[i + 1][j] != 0) {
                    adjList[node][vecini] = (i + 1) * 13 + j;
                    vecini++;
                }
                if (j > 0 && matrix[i][j - 1] != 0) {
                    adjList[node][vecini] = i * 13 + (j - 1);
                    vecini++;
                }
                if (j < 12 && matrix[i][j + 1] != 0) {
                    adjList[node][vecini] = i * 13 + (j + 1);
                    vecini++;
                }

                adjCount[node] = vecini;
            }
        }
    }

    queue<int> q;
    int start;
    int ok_1 = 1;
    for (int i = 0; i < 5 && (ok_1 == 1); i++) {
        for (int j = 0; j < 13 && (ok_1 == 1); j++) {
            if (matrix[i][j] != 0) {
                start = i * 13 + j;
                ok_1 = 0;
            }
        }
    }

    q.push(start);
    visited[start] = 1;
    int count_bfs = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < adjCount[current]; i++) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = 1;
                count_bfs++;
            }
        }
    }

    if (count_bfs == count) {
        return false;
    }
    else {
        return true;
    }
}

void Tema1::Draw_red_form(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["new_form_red"], shaders["VertexColor"], m);
}


void Tema1::Draw_squares_table()
{
    float x, y, space = 70;
    float offset = (width_small_blue - space) / 2;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            if (matrix[i][j] != 0) {
                x = x_small_blue + j * space + offset;
                y = y_small_blue + i * space + offset;
                glm::mat3 m = transform2D::Translate(x, y);
                m *= transform2D::Scale(70, 70);

                if (matrix[i][j] == 1) {
                    RenderMesh2D(meshes["grey_square"], shaders["VertexColor"], m);
                }
                else if (matrix[i][j] == 2) {
                    RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], m);
                }
                else if (matrix[i][j] == 3) {
                    RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], m);
                }
                else if (matrix[i][j] == 4) {
                    RenderMesh2D(meshes["purple_square"], shaders["VertexColor"], m);
                }
            }
        }
    }
}


void Tema1::Draw_drag(float x, float y)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width_grey, height_grey);

    glDisable(GL_DEPTH_TEST);

    if (is_drag == 1) {
        RenderMesh2D(meshes["grey_square"], shaders["VertexColor"], m);
    }
    else if (is_drag == 2) {
        RenderMesh2D(meshes["yellow_square"], shaders["VertexColor"], m);
    }
    else if (is_drag == 3) {
        RenderMesh2D(meshes["orange_square"], shaders["VertexColor"], m);
    }
    else if (is_drag == 4) {
        RenderMesh2D(meshes["purple_square"], shaders["VertexColor"], m);
    }

    glEnable(GL_DEPTH_TEST);
}


void Tema1::Draw_grey(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["grey_square"], shaders["VertexColor"], m);
}


void Tema1::Draw_red(float x, float y, float width, float height)
{
    glm::mat3 m;

    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, 1);
    RenderMesh2D(meshes["red_line"], shaders["VertexColor"], m);

    m = transform2D::Translate(x, y + height - 1);
    m *= transform2D::Scale(width, 1);
    RenderMesh2D(meshes["red_line"], shaders["VertexColor"], m);

    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(1, height);
    RenderMesh2D(meshes["red_line"], shaders["VertexColor"], m);

    m = transform2D::Translate(x + width - 1, y);
    m *= transform2D::Scale(1, height);
    RenderMesh2D(meshes["red_line"], shaders["VertexColor"], m);
}


void Tema1::Draw_left(float x, float y, float width, float height)
{
    glm::mat3 m;

    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, 1);
    RenderMesh2D(meshes["line_left"], shaders["VertexColor"], m);

    m = transform2D::Translate(x, y + height - 1);
    m *= transform2D::Scale(width, 1);
    RenderMesh2D(meshes["line_left"], shaders["VertexColor"], m);

    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(1, height);
    RenderMesh2D(meshes["line_left"], shaders["VertexColor"], m);

    m = transform2D::Translate(x + width - 1, y);
    m *= transform2D::Scale(1, height);
    RenderMesh2D(meshes["line_left"], shaders["VertexColor"], m);
}


void Tema1::Draw_blue(float x, float y, float width, float height)
{
    glm::mat3 m;

    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, 1);
    RenderMesh2D(meshes["blue_square"], shaders["VertexColor"], m);

    m = transform2D::Translate(x, y + height - 1);
    m *= transform2D::Scale(width, 1);
    RenderMesh2D(meshes["blue_square"], shaders["VertexColor"], m);

    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(1, height);
    RenderMesh2D(meshes["blue_square"], shaders["VertexColor"], m);

    m = transform2D::Translate(x + width - 1, y);
    m *= transform2D::Scale(1, height);
    RenderMesh2D(meshes["blue_square"], shaders["VertexColor"], m);
}


void Tema1::Draw_green(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["green_square"], shaders["VertexColor"], m);
}


void Tema1::Draw_form(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["new_form"], shaders["VertexColor"], m);
}


void Tema1::Draw_small_blue(float x, float y, float width, float height)
{
    glm::mat3 m;
    m = transform2D::Translate(x, y);
    m *= transform2D::Scale(width, height);
    RenderMesh2D(meshes["blue_small"], shaders["VertexColor"], m);
}


bool Tema1::Delete_square(float click_x, float click_y)
{
    int space = 70;
    int ok = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            if (matrix[i][j] != 0) {
                float square_x = x_small_blue + j * space;
                float square_y = y_small_blue + i * space;
                if (click_x >= square_x - 10 && click_x <= square_x + 80 &&
                    click_y >= square_y - 10 && click_y <= square_y + 80) {
                    matrix[i][j] = 0;
                    count--;
                    if (green_count <= 10) {
                        for (int k = 0; k <= 9 && ok == 1; k++) {
                            if (count < 10) {
                                if (green_squares[k] == 0) {
                                    green_squares[k] = 1;
                                    green_count++;
                                    ok = 0;
                                }
                            }
                        }
                    }

                    return true;
                }
            }
        }
    }
    return false;
}


void Tema1::Delete_green_square()
{
    int ok = 1;
    for (int i = 9; i >= 0 && ok == 1; i--) {
        if (green_squares[i] == 1) {
            green_squares[i] = 0;
            green_count--;
            ok = 0;
        }
    }
}


void Tema1::Put_square(float x, float y)
{
    int space = 70;

    int i = (int)((y - y_small_blue) / space);
    int j = (int)((x - x_small_blue) / space);

    if (i < 0 || i >= 5 || j < 0 || j >= 13) {
        return;
    }
    float square_x = x_small_blue + j * space;
    float square_y = y_small_blue + i * space;

    if (x < square_x - 10 || x > square_x + width_small_blue + 10 ||
        y < square_y - 10 || y > square_y + height_small_blue + 10) {
        return;
    }

    if (matrix[i][j] == 0) {
        matrix[i][j] = is_drag;
        count++;
        Delete_green_square();
    }
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (curentScene == Scene::Game) {
        if (scor_left >= 5 || scor_right >= 5) {
            return;
        }
        glm::ivec2 resolution = window->GetResolution();

        int max_i = 0;
        int max_j = 0;
        int ok = 1;

        for (int i = 0; i < 5 && (ok == 1); i++) {
            for (int j = 0; j < 13; j++) {
                if (matrix_copy[i][j] != 0) {
                    max_j++;
                    ok = 0;
                }
            }
        }
        ok = 1;
        for (int j = 0; j < 13 && (ok == 1); j++) {
            for (int i = 0; i < 5; i++) {
                if (matrix_copy[i][j] != 0) {
                    max_i++;
                    ok = 0;
                }
            }
        }

        float dimens = 40;
        float paddle_height;

        if (max_j >= max_i) {
            paddle_height = max_j * dimens;
        }
        else {
            paddle_height = max_i * dimens;
        }

        if (window->KeyHold(GLFW_KEY_W)) {
            y_form_left += speed_paddle * deltaTime;
            if (y_form_left + paddle_height > y_board_game + height_board_game) {
                y_form_left = y_board_game + height_board_game - paddle_height;
            }
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            y_form_left -= speed_paddle * deltaTime;
            if (y_form_left < y_board_game) {
                y_form_left = y_board_game;
            }
        }

        if (window->KeyHold(GLFW_KEY_UP)) {
            y_form_right += speed_paddle * deltaTime;
            if (y_form_right + paddle_height > y_board_game + height_board_game) {
                y_form_right = y_board_game + height_board_game - paddle_height;
            }
        }
        if (window->KeyHold(GLFW_KEY_DOWN)) {
            y_form_right -= speed_paddle * deltaTime;
            if (y_form_right < y_board_game) {
                y_form_right = y_board_game;
            }
        }

        if (count_bile == 0) {
            if (window->KeyHold(GLFW_KEY_1)) {
                count_bile = 1;
                srand(time(NULL));
                int rand_1 = rand() % 100;
                int rand_2 = rand() % 100;

                ball_move = true;
                if (rand_1 <= rand_2) {
                    v_x_bila = -viteza_bila;
                }
                else {
                    v_x_bila = viteza_bila;
                }
                v_y_bila = 0;
            }
            else if (window->KeyHold(GLFW_KEY_2)) {
                count_bile = 2;
                runda_activa = true;
                ball_move = true;
                ball_move_2 = true;
                v_x_bila = -viteza_bila;
                v_y_bila = 0;
                v_x_bila_2 = viteza_bila_2;
                v_y_bila_2 = 0;
                scor_left_ant = 0;
                scor_right_ant = 0;
            }
        }

        if (count_bile == 1) {
            if (!ball_move && (scor_left > 0 || scor_right > 0) && scor_left < 5 && scor_right < 5) {
                ball_move = true;

                if (scor_left_ant != scor_left) {
                    v_x_bila = -viteza_bila;
                    v_y_bila = 0;
                    scor_left_ant = scor_left;
                }
                else if (scor_right_ant != scor_right) {
                    v_x_bila = viteza_bila;
                    v_y_bila = 0;
                    scor_right_ant = scor_right;
                }
            }

            if (ball_move) {
                ball_x += v_x_bila * deltaTime;
                ball_y += v_y_bila * deltaTime;

                if (ball_y - ball_radius <= y_board_game) {
                    ball_y = y_board_game + ball_radius;
                    v_y_bila = -v_y_bila;
                }
                if (ball_y + ball_radius >= y_board_game + height_board_game) {
                    ball_y = y_board_game + height_board_game - ball_radius;
                    v_y_bila = -v_y_bila;
                }

                float form_left_x = resolution.x / 5;
                float paddle_width;
                if (max_j >= max_i) {
                    paddle_width = max_i * dimens;
                }
                else {
                    paddle_width = max_j * dimens;
                }

                if (ball_x - ball_radius <= form_left_x + paddle_width &&
                    ball_x > form_left_x &&
                    ball_y >= y_form_left &&
                    ball_y <= y_form_left + paddle_height) {

                    anim_left = 1;
                    viteza_bila += 100.f;
                    float centru_paleta = y_form_left + paddle_height / 2;
                    unghi = (ball_y - centru_paleta) / (paddle_height / 2);
                    v_x_bila = viteza_bila * cos(unghi);
                    v_y_bila = viteza_bila * sin(unghi);
                    if (v_x_bila < 0) v_x_bila = -v_x_bila;
                    ball_x = form_left_x + paddle_width + ball_radius;
                }

                if (ball_y + ball_radius >= y_form_left &&
                    ball_y + ball_radius <= y_form_left + paddle_height &&
                    ball_x >= form_left_x &&
                    ball_x <= form_left_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_left - ball_radius;
                }

                if (ball_y - ball_radius <= y_form_left + paddle_height &&
                    ball_y - ball_radius >= y_form_left &&
                    ball_x >= form_left_x &&
                    ball_x <= form_left_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_left + paddle_height + ball_radius;
                }

                float form_right_x = resolution.x - (resolution.x / 4);

                if (ball_x + ball_radius >= form_right_x &&
                    ball_x < form_right_x + paddle_width &&
                    ball_y >= y_form_right &&
                    ball_y <= y_form_right + paddle_height) {

                    anim_right = 1;
                    viteza_bila += 100.f;
                    float centru_paleta = y_form_right + paddle_height / 2;
                    unghi = (ball_y - centru_paleta) / (paddle_height / 2);
                    v_x_bila = viteza_bila * cos(unghi);
                    v_y_bila = viteza_bila * sin(unghi);
                    if (v_x_bila > 0) v_x_bila = -v_x_bila;
                    ball_x = form_right_x - ball_radius;
                }

                if (ball_y + ball_radius >= y_form_right &&
                    ball_y + ball_radius <= y_form_right + paddle_height &&
                    ball_x >= form_right_x &&
                    ball_x <= form_right_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_right - ball_radius;
                    viteza_bila += 100.f;
                }

                if (ball_y - ball_radius <= y_form_right + paddle_height &&
                    ball_y - ball_radius >= y_form_right &&
                    ball_x >= form_right_x &&
                    ball_x <= form_right_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_right + paddle_height + ball_radius;
                    viteza_bila += 100.f;
                }

                if (ball_x - ball_radius <= x_board_game) {
                    scor_right_ant = scor_right;
                    scor_right++;
                    ball_x = resolution.x / 2;
                    ball_y = resolution.y / 2;
                    ball_move = false;
                    v_x_bila = 0;
                    v_y_bila = 0;
                    viteza_bila = 200.f;
                }

                if (ball_x + ball_radius >= x_board_game + width_board_game) {
                    scor_left_ant = scor_left;
                    scor_left++;
                    ball_x = resolution.x / 2;
                    ball_y = resolution.y / 2;
                    ball_move = false;
                    v_x_bila = 0;
                    v_y_bila = 0;
                    viteza_bila = 200.f;
                }
            }
        }

        else if (count_bile == 2) {
            if (!runda_activa && !ball_move && !ball_move_2 && (scor_left > 0 || scor_right > 0)) {
                runda_activa = true;
                int goluri_left = scor_left - scor_left_ant;
                int goluri_right = scor_right - scor_right_ant;

                if (goluri_left == 2) {
                    ball_move = true;
                    v_x_bila = -viteza_bila;
                    v_y_bila = 0;
                    delay_minge_2 = 1.5f;
                }
                else if (goluri_right == 2) {
                    ball_move = true;
                    v_x_bila = viteza_bila;
                    v_y_bila = 0;
                    delay_minge_2 = 1.5f;
                }
                else if (goluri_left == 1 && goluri_right == 1) {
                    ball_move = true;
                    ball_move_2 = true;
                    v_x_bila = -viteza_bila;
                    v_y_bila = 0;
                    v_x_bila_2 = viteza_bila_2;
                    v_y_bila_2 = 0;
                }
                else if (goluri_left == 1) {
                    ball_move = true;
                    ball_move_2 = true;
                    v_x_bila = -viteza_bila;
                    v_y_bila = 0;
                    v_x_bila_2 = -viteza_bila_2;
                    v_y_bila_2 = 0;
                }
                else if (goluri_right == 1) {
                    ball_move = true;
                    ball_move_2 = true;
                    v_x_bila = viteza_bila;
                    v_y_bila = 0;
                    v_x_bila_2 = viteza_bila_2;
                    v_y_bila_2 = 0;
                }

                scor_left_ant = scor_left;
                scor_right_ant = scor_right;
            }

            if (delay_minge_2 > 0) {
                delay_minge_2 -= deltaTime;
                if (delay_minge_2 <= 0 && ball_move) {
                    ball_move_2 = true;
                    if (v_x_bila < 0) {
                        v_x_bila_2 = -viteza_bila_2;
                    }
                    else {
                        v_x_bila_2 = viteza_bila_2;
                    }
                    v_y_bila_2 = 0;
                    ball_x_2 = resolution.x / 2;
                    ball_y_2 = resolution.y / 2;
                    delay_minge_2 = 0;
                }
            }

            if (ball_move) {
                ball_x += v_x_bila * deltaTime;
                ball_y += v_y_bila * deltaTime;

                if (ball_y - ball_radius <= y_board_game) {
                    ball_y = y_board_game + ball_radius;
                    v_y_bila = -v_y_bila;
                }
                if (ball_y + ball_radius >= y_board_game + height_board_game) {
                    ball_y = y_board_game + height_board_game - ball_radius;
                    v_y_bila = -v_y_bila;
                }

                float form_left_x = resolution.x / 5;
                float paddle_width;
                if (max_j >= max_i) {
                    paddle_width = max_i * dimens;
                }
                else {
                    paddle_width = max_j * dimens;
                }

                if (ball_x - ball_radius <= form_left_x + paddle_width &&
                    ball_x > form_left_x &&
                    ball_y >= y_form_left &&
                    ball_y <= y_form_left + paddle_height) {

                    anim_left = 1;
                    viteza_bila += 100.f;
                    float centru_paleta = y_form_left + paddle_height / 2;
                    unghi = (ball_y - centru_paleta) / (paddle_height / 2);
                    v_x_bila = viteza_bila * cos(unghi);
                    v_y_bila = viteza_bila * sin(unghi);
                    if (v_x_bila < 0) v_x_bila = -v_x_bila;
                    ball_x = form_left_x + paddle_width + ball_radius;
                }

                if (ball_y + ball_radius >= y_form_left &&
                    ball_y + ball_radius <= y_form_left + paddle_height &&
                    ball_x >= form_left_x &&
                    ball_x <= form_left_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_left - ball_radius;
                }

                if (ball_y - ball_radius <= y_form_left + paddle_height &&
                    ball_y - ball_radius >= y_form_left &&
                    ball_x >= form_left_x &&
                    ball_x <= form_left_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_left + paddle_height + ball_radius;
                }

                float form_right_x = resolution.x - (resolution.x / 4);

                if (ball_x + ball_radius >= form_right_x &&
                    ball_x < form_right_x + paddle_width &&
                    ball_y >= y_form_right &&
                    ball_y <= y_form_right + paddle_height) {

                    anim_right = 1;
                    viteza_bila += 100.f;
                    float centru_paleta = y_form_right + paddle_height / 2;
                    unghi = (ball_y - centru_paleta) / (paddle_height / 2);
                    v_x_bila = viteza_bila * cos(unghi);
                    v_y_bila = viteza_bila * sin(unghi);
                    if (v_x_bila > 0) v_x_bila = -v_x_bila;
                    ball_x = form_right_x - ball_radius;
                }

                if (ball_y + ball_radius >= y_form_right &&
                    ball_y + ball_radius <= y_form_right + paddle_height &&
                    ball_x >= form_right_x &&
                    ball_x <= form_right_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_right - ball_radius;
                    viteza_bila += 100.f;
                }

                if (ball_y - ball_radius <= y_form_right + paddle_height &&
                    ball_y - ball_radius >= y_form_right &&
                    ball_x >= form_right_x &&
                    ball_x <= form_right_x + paddle_width) {
                    v_y_bila = -v_y_bila;
                    ball_y = y_form_right + paddle_height + ball_radius;
                    viteza_bila += 100.f;
                }

                if (ball_x - ball_radius <= x_board_game) {
                    scor_right++;
                    ball_x = resolution.x / 2;
                    ball_y = resolution.y / 2;
                    ball_move = false;
                    v_x_bila = 0;
                    v_y_bila = 0;
                    viteza_bila = 200.f;

                    if (!ball_move_2) {
                        runda_activa = false;
                    }
                }

                if (ball_x + ball_radius >= x_board_game + width_board_game) {
                    scor_left++;
                    ball_x = resolution.x / 2;
                    ball_y = resolution.y / 2;
                    ball_move = false;
                    v_x_bila = 0;
                    v_y_bila = 0;
                    viteza_bila = 200.f;

                    if (!ball_move_2) {
                        runda_activa = false;
                    }
                }
            }

            if (ball_move_2) {
                ball_x_2 += v_x_bila_2 * deltaTime;
                ball_y_2 += v_y_bila_2 * deltaTime;

                if (ball_y_2 - ball_radius_2 <= y_board_game) {
                    ball_y_2 = y_board_game + ball_radius_2;
                    v_y_bila_2 = -v_y_bila_2;
                }
                if (ball_y_2 + ball_radius_2 >= y_board_game + height_board_game) {
                    ball_y_2 = y_board_game + height_board_game - ball_radius_2;
                    v_y_bila_2 = -v_y_bila_2;
                }

                float form_left_x = resolution.x / 5;
                float paddle_width;
                if (max_j >= max_i) {
                    paddle_width = max_i * dimens;
                }
                else {
                    paddle_width = max_j * dimens;
                }

                if (ball_x_2 - ball_radius_2 <= form_left_x + paddle_width &&
                    ball_x_2 > form_left_x &&
                    ball_y_2 >= y_form_left &&
                    ball_y_2 <= y_form_left + paddle_height) {

                    anim_left = 1;
                    viteza_bila_2 += 100.f;
                    float centru_paleta = y_form_left + paddle_height / 2;
                    unghi_2 = (ball_y_2 - centru_paleta) / (paddle_height / 2);
                    v_x_bila_2 = viteza_bila_2 * cos(unghi_2);
                    v_y_bila_2 = viteza_bila_2 * sin(unghi_2);
                    if (v_x_bila_2 < 0) v_x_bila_2 = -v_x_bila_2;
                    ball_x_2 = form_left_x + paddle_width + ball_radius_2;
                }

                if (ball_y_2 + ball_radius_2 >= y_form_left &&
                    ball_y_2 + ball_radius_2 <= y_form_left + paddle_height &&
                    ball_x_2 >= form_left_x &&
                    ball_x_2 <= form_left_x + paddle_width) {
                    v_y_bila_2 = -v_y_bila_2;
                    ball_y_2 = y_form_left - ball_radius_2;
                }

                if (ball_y_2 - ball_radius_2 <= y_form_left + paddle_height &&
                    ball_y_2 - ball_radius_2 >= y_form_left &&
                    ball_x_2 >= form_left_x &&
                    ball_x_2 <= form_left_x + paddle_width) {
                    v_y_bila_2 = -v_y_bila_2;
                    ball_y_2 = y_form_left + paddle_height + ball_radius_2;
                }

                float form_right_x = resolution.x - (resolution.x / 4);

                if (ball_x_2 + ball_radius_2 >= form_right_x &&
                    ball_x_2 < form_right_x + paddle_width &&
                    ball_y_2 >= y_form_right &&
                    ball_y_2 <= y_form_right + paddle_height) {

                    anim_right = 1;
                    viteza_bila_2 += 100.f;
                    float centru_paleta = y_form_right + paddle_height / 2;
                    unghi_2 = (ball_y_2 - centru_paleta) / (paddle_height / 2);
                    v_x_bila_2 = viteza_bila_2 * cos(unghi_2);
                    v_y_bila_2 = viteza_bila_2 * sin(unghi_2);
                    if (v_x_bila_2 > 0) v_x_bila_2 = -v_x_bila_2;
                    ball_x_2 = form_right_x - ball_radius_2;
                }

                if (ball_y_2 + ball_radius_2 >= y_form_right &&
                    ball_y_2 + ball_radius_2 <= y_form_right + paddle_height &&
                    ball_x_2 >= form_right_x &&
                    ball_x_2 <= form_right_x + paddle_width) {
                    v_y_bila_2 = -v_y_bila_2;
                    ball_y_2 = y_form_right - ball_radius_2;
                    viteza_bila_2 += 100.f;
                }

                if (ball_y_2 - ball_radius_2 <= y_form_right + paddle_height &&
                    ball_y_2 - ball_radius_2 >= y_form_right &&
                    ball_x_2 >= form_right_x &&
                    ball_x_2 <= form_right_x + paddle_width) {
                    v_y_bila_2 = -v_y_bila_2;
                    ball_y_2 = y_form_right + paddle_height + ball_radius_2;
                    viteza_bila_2 += 100.f;
                }

                if (ball_x_2 - ball_radius_2 <= x_board_game) {
                    scor_right++;
                    ball_x_2 = resolution.x / 2;
                    ball_y_2 = resolution.y / 2;
                    ball_move_2 = false;
                    v_x_bila_2 = 0;
                    v_y_bila_2 = 0;
                    viteza_bila_2 = 200.f;

                    if (!ball_move) {
                        runda_activa = false;
                    }
                }

                if (ball_x_2 + ball_radius_2 >= x_board_game + width_board_game) {
                    scor_left++;
                    ball_x_2 = resolution.x / 2;
                    ball_y_2 = resolution.y / 2;
                    ball_move_2 = false;
                    v_x_bila_2 = 0;
                    v_y_bila_2 = 0;
                    viteza_bila_2 = 200.f;

                    if (!ball_move) {
                        runda_activa = false;
                    }
                }
            }
        }

        return;
    }

    static bool pressed_left = false;
    static bool pressed_right = false;

    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        auto resolution = window->GetResolution();
        float click_x = window->GetCursorPosition().x;
        float click_y = resolution.y - window->GetCursorPosition().y;

        if (!pressed_left) {
            if (click_x >= x_grey && click_x <= x_grey + width_grey &&
                click_y >= y_grey && click_y <= y_grey + height_grey) {
                is_drag = 1;
                drag_offset_x = click_x - x_grey;
                drag_offset_y = click_y - y_grey;
                drag_square_x = x_grey;
                drag_square_y = y_grey;
            }
            else if (click_x >= x_grey_2 && click_x <= x_grey_2 + width_grey_2 &&
                click_y >= y_grey_2 && click_y <= y_grey_2 + height_grey_2) {
                is_drag = 2;
                drag_offset_x = click_x - x_grey_2;
                drag_offset_y = click_y - y_grey_2;
                drag_square_x = x_grey_2;
                drag_square_y = y_grey_2;
            }
            else if (click_x >= x_grey_3 && click_x <= x_grey_3 + width_grey_3 &&
                click_y >= y_grey_3 && click_y <= y_grey_3 + height_grey_3) {
                is_drag = 3;
                drag_offset_x = click_x - x_grey_3;
                drag_offset_y = click_y - y_grey_3;
                drag_square_x = x_grey_3;
                drag_square_y = y_grey_3;
            }
            else if (click_x >= x_grey_4 && click_x <= x_grey_4 + width_grey_4 &&
                click_y >= y_grey_4 && click_y <= y_grey_4 + height_grey_4) {
                is_drag = 4;
                drag_offset_x = click_x - x_grey_4;
                drag_offset_y = click_y - y_grey_4;
                drag_square_x = x_grey_4;
                drag_square_y = y_grey_4;
            }
        }
        pressed_left = true;
    }
    else {
        if (pressed_left && is_drag) {
            auto resolution = window->GetResolution();
            float x = window->GetCursorPosition().x;
            float y = resolution.y - window->GetCursorPosition().y;
            Put_square(x, y);
            is_drag = 0;
        }
        pressed_left = false;
    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        if (!pressed_right) {
            auto resolution = window->GetResolution();
            float click_x = window->GetCursorPosition().x;
            float click_y = resolution.y - window->GetCursorPosition().y;
            Delete_square(click_x, click_y);
        }
        pressed_right = true;
    }
    else {
        pressed_right = false;
    }

    if (is_drag) {
        auto resolution = window->GetResolution();
        float mouse_x = window->GetCursorPosition().x;
        float mouse_y = resolution.y - window->GetCursorPosition().y;
        drag_square_x = mouse_x - drag_offset_x;
        drag_square_y = mouse_y - drag_offset_y;
    }
}

void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (curentScene == Scene::Game) {
        return;
    }

    if (is_drag) {
        float current_y = window->GetResolution().y - mouseY;
        float current_x = mouseX;
        drag_square_x = current_x - drag_offset_x;
        drag_square_y = current_y - drag_offset_y;
    }

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (curentScene == Scene::Game) {
        return;
    }

    float click_y = window->GetResolution().y - mouseY;
    float click_x = mouseX;

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        int space = 97;
        float start_button_x = x_green + space * 10;
        float start_button_y = y_green;

        if (click_x >= start_button_x && click_x <= start_button_x + width_green &&
            click_y >= start_button_y && click_y <= start_button_y + height_green) {

            if (StartGame()) {
                curentScene = Scene::Game;
            }
            return;
        }
    }

    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    if (click_x >= x_grey && click_x <= x_grey + width_grey &&
        click_y >= y_grey && click_y <= y_grey + height_grey) {
        is_drag = 1;
        drag_square_x = x_grey;
        drag_square_y = y_grey;
        drag_offset_x = click_x - x_grey;
        drag_offset_y = click_y - y_grey;
        return;
    }
    else if (click_x >= x_grey_2 && click_x <= x_grey_2 + width_grey_2 &&
        click_y >= y_grey_2 && click_y <= y_grey_2 + height_grey_2) {
        is_drag = 2;
        drag_square_x = x_grey_2;
        drag_square_y = y_grey_2;
        drag_offset_x = click_x - x_grey_2;
        drag_offset_y = click_y - y_grey_2;
        return;
    }
    else if (click_x >= x_grey_3 && click_x <= x_grey_3 + width_grey_3 &&
        click_y >= y_grey_3 && click_y <= y_grey_3 + height_grey_3) {
        is_drag = 3;
        drag_square_x = x_grey_3;
        drag_square_y = y_grey_3;
        drag_offset_x = click_x - x_grey_3;
        drag_offset_y = click_y - y_grey_3;
        return;
    }
    else if (click_x >= x_grey_4 && click_x <= x_grey_4 + width_grey_4 &&
        click_y >= y_grey_4 && click_y <= y_grey_4 + height_grey_4) {
        is_drag = 4;
        drag_square_x = x_grey_4;
        drag_square_y = y_grey_4;
        drag_offset_x = click_x - x_grey_4;
        drag_offset_y = click_y - y_grey_4;
        return;
    }


    for (int i = 0; i < 11; i++) {
        if (green_squares[i]) {
            int space = 97;
            float green_x = x_green + space * i;

            if (click_x >= green_x && click_x <= green_x + width_green &&
                click_y >= y_green && click_y <= y_green + height_green) {
                green_squares[i] = 0;
                green_count--;
                return;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (curentScene == Scene::Game) {
        return;
    }

    if (button != GLFW_MOUSE_BUTTON_LEFT || !is_drag) return;

    float x = mouseX;
    float y = window->GetResolution().y - mouseY;
    int space = 70;
    int square_x;
    int square_y;

    bool square_placed = false;
    int ok = 1;
    for (int i = 0; i < 5 && (ok == 1); i++) {
        for (int j = 0; j < 13 && (ok == 1); j++) {
            square_x = x_small_blue + j * space;
            square_y = y_small_blue + i * space;

            if ((x >= square_x - 10 && x <= square_x + width_small_blue + 10) &&
                (y >= square_y - 10 && y <= square_y + height_small_blue + 10)) {

                if (matrix[i][j] == 0) {
                    matrix[i][j] = is_drag;
                    count++;
                    square_placed = true;
                }

                ok = 0;
            }
        }
    }

    if (square_placed) {
        Delete_green_square();
    }

    is_drag = 0;
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}