#include "stm32f10x.h"
#include "driver.h"
#include "ssd1306.h"
#include "fonts.h"
#include <stdlib.h>

// =====================================================
// DINO RUN GAME
// STM32F103C8 + OLED SSD1306 + JOYSTICK
// =====================================================

// =====================================================
// GLOBAL VARIABLES
// =====================================================

// joystick ADC
int rawADC = 0;

// dinosaur position
int dinoX = 15;
int dinoY = 50;

// jump physics
int velocity = 0;

// cactus obstacle
int cactusX = 120;
int cactusH = 12;

// game variables
int score = 0;
int life = 3;

int speed = 45;

// level system
int level = 1;
int showLevelText = 0;

// prevents double score
int scoreGiven = 0;

// top scores
int top1 = 0;
int top2 = 0;
int top3 = 0;

// =====================================================
// FUNCTION PROTOTYPES
// =====================================================

void Intro();
void Game();
void DrawGame();
void ResetCactus();
void GameOver();
void UpdateTopScores();

// =====================================================
// MAIN
// =====================================================

int main() {

    // joystick analog input
    pinModeAnalogInA0();

    // OLED init
    SSD1306_Init();

    // intro screen
    Intro();

    // start game
    Game();

    while(1);
}

// =====================================================
// INTRO SCREEN
// =====================================================

void Intro() {

    SSD1306_Fill(SSD1306_COLOR_BLACK);

    SSD1306_GotoXY(22,10);

    SSD1306_Puts("DINO RUN",
                 &Font_11x18,
                 SSD1306_COLOR_WHITE);

    // intro animation
    for(int i=0;i<5;i++) {

        SSD1306_DrawFilledRectangle(
            30 + i*12,
            45,
            6,
            6,
            SSD1306_COLOR_WHITE
        );

        SSD1306_UpdateScreen();

        delay_ms(120);

        SSD1306_DrawFilledRectangle(
            30 + i*12,
            45,
            6,
            6,
            SSD1306_COLOR_BLACK
        );
    }

    SSD1306_UpdateScreen();

    delay_ms(1200);
}

// =====================================================
// GAME LOOP
// =====================================================

void Game() {

    while(life > 0) {

        // =========================================
        // READ ADC
        // =========================================

        if(ADC1->SR & ADC_SR_EOC) {

            rawADC = ADC1->DR;
        }

        // =========================================
        // JUMP
        // =========================================

        // joystick up
        if(rawADC > 2500 && dinoY >= 50) {

            velocity = -8;
        }

        // gravity
        velocity++;

        dinoY += velocity;

        // ground collision
        if(dinoY > 50) {

            dinoY = 50;
        }

        // =========================================
        // MOVE CACTUS
        // =========================================

        cactusX -= 3;

        // =========================================
        // SCORE SYSTEM
        // =========================================

        // obstacle passed dino
        if(cactusX + 6 < dinoX && scoreGiven == 0) {

            score++;

            scoreGiven = 1;

            // =====================================
            // LEVEL SYSTEM
            // =====================================

            // every 10 points = next level
            if(score % 5 == 0) {

                level++;

                showLevelText = 15;

                // stronger speed increase
                if(speed > 10)
                    speed -= 4;
            }

            else {

                // small speed increase
                if(speed > 18)
                    speed -= 1;
            }
        }

        // =========================================
        // RESET CACTUS
        // =========================================

        if(cactusX < -10) {

            ResetCactus();
        }

        // =========================================
        // COLLISION DETECTION
        // =========================================

        if(dinoX + 8 >= cactusX &&
           dinoX <= cactusX + 6) {

            if(dinoY + 8 >= 64 - cactusH) {

                life--;

                dinoY = 50;

                cactusX = 120;

                velocity = 0;

                scoreGiven = 0;
            }
        }

        // draw everything
        DrawGame();

        delay_ms(speed);
    }

    GameOver();
}

// =====================================================
// DRAW GAME
// =====================================================

void DrawGame() {

    SSD1306_Fill(SSD1306_COLOR_BLACK);

    // =========================================
    // GROUND
    // =========================================

    SSD1306_DrawLine(
        0,
        60,
        127,
        60,
        SSD1306_COLOR_WHITE
    );

    // =========================================
    // LIVES
    // =========================================

    SSD1306_GotoXY(0,0);

    SSD1306_Puts("L:",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    for(int i=0;i<life;i++) {

        SSD1306_Puts("*",
                     &Font_7x10,
                     SSD1306_COLOR_WHITE);
    }

    // =========================================
    // LEVEL
    // =========================================

    SSD1306_GotoXY(40,0);

    SSD1306_Puts("LV:",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    SSD1306_PutNum(level,
                   &Font_7x10,
                   SSD1306_COLOR_WHITE);

    // =========================================
    // SCORE
    // =========================================

    SSD1306_GotoXY(82,0);

    SSD1306_Puts("S:",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    SSD1306_PutNum(score,
                   &Font_7x10,
                   SSD1306_COLOR_WHITE);

    // =========================================
    // DINO
    // =========================================

    SSD1306_DrawFilledRectangle(
        dinoX,
        dinoY,
        8,
        8,
        SSD1306_COLOR_WHITE
    );

    // eye
    SSD1306_DrawPixel(
        dinoX + 5,
        dinoY + 2,
        SSD1306_COLOR_BLACK
    );

    // =========================================
    // CACTUS
    // =========================================

    SSD1306_DrawFilledRectangle(
        cactusX,
        64 - cactusH,
        6,
        cactusH,
        SSD1306_COLOR_WHITE
    );

    // =========================================
    // LEVEL TEXT
    // =========================================

    if(showLevelText > 0) {

        SSD1306_GotoXY(22,24);

        SSD1306_Puts("LEVEL",
                     &Font_11x18,
                     SSD1306_COLOR_WHITE);

        SSD1306_GotoXY(88,24);

        SSD1306_PutNum(level,
                       &Font_11x18,
                       SSD1306_COLOR_WHITE);

        showLevelText--;
    }

    SSD1306_UpdateScreen();
}

// =====================================================
// RESET CACTUS
// =====================================================

void ResetCactus() {

    cactusX = 128;

    cactusH = rand() % 18 + 8;

    scoreGiven = 0;
}

// =====================================================
// GAME OVER SCREEN
// =====================================================

void GameOver() {

    UpdateTopScores();

    SSD1306_Fill(SSD1306_COLOR_BLACK);

    SSD1306_GotoXY(18,10);

    SSD1306_Puts("GAME OVER",
                 &Font_11x18,
                 SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(28,38);

    SSD1306_Puts("SCORE:",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    SSD1306_PutNum(score,
                   &Font_7x10,
                   SSD1306_COLOR_WHITE);

    SSD1306_UpdateScreen();

    delay_ms(2500);

    // =========================================
    // TOP SCORES
    // =========================================

    SSD1306_Fill(SSD1306_COLOR_BLACK);

    SSD1306_GotoXY(20,0);

    SSD1306_Puts("TOP SCORES",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    // top 1
    SSD1306_GotoXY(10,18);

    SSD1306_Puts("1.",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    SSD1306_PutNum(top1,
                   &Font_7x10,
                   SSD1306_COLOR_WHITE);

    // top 2
    SSD1306_GotoXY(10,32);

    SSD1306_Puts("2.",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    SSD1306_PutNum(top2,
                   &Font_7x10,
                   SSD1306_COLOR_WHITE);

    // top 3
    SSD1306_GotoXY(10,46);

    SSD1306_Puts("3.",
                 &Font_7x10,
                 SSD1306_COLOR_WHITE);

    SSD1306_PutNum(top3,
                   &Font_7x10,
                   SSD1306_COLOR_WHITE);

    SSD1306_UpdateScreen();

    while(1);
}

// =====================================================
// UPDATE HIGH SCORES
// =====================================================

void UpdateTopScores() {

    if(score > top1) {

        top3 = top2;
        top2 = top1;
        top1 = score;
    }

    else if(score > top2) {

        top3 = top2;
        top2 = score;
    }

    else if(score > top3) {

        top3 = score;
    }
}