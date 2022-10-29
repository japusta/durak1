#include "Game.h"

Game* game = nullptr;

int main(int argc,char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int choice = 0,
        numTests = 0,
        answer = 0;
    
    Uint32 frameStart,frameTime;
    std::cout << "Choose the game mod:\n1) Player with Bot\n2) Bot with Bot\n" <<"Your answer:";
    std::cin >> choice;
    system("cls");
    if (choice == 1) {
        game = new Game("game_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false, choice, false);

        while (game->running()) {

            frameStart = SDL_GetTicks();//количество миллисекунд прошедших с момента инициализации SDL
            //здесь три основных функции 
            game->HandleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);//это задержка обновления окна, чтобы было 60 кадров
            }
        }
        game->~Game();
    }
    else if (choice == 2) {


        std::cout << "Enter the number of Bot fights:";
        std::cin >> numTests;
        std::cout << "May be you want to control bots fighting?\n(1-yes, 2-no) Your answer:";
        std::cin >> answer;
        system("cls");

        if (answer == 2) {
            int winFirstBot = 0,
                winSecondBot = 0,
                drawsCount = 0,
                whoWon = 0;
            
            for (int y = 0; y < numTests; y++) {
                game = new Game("game_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false, choice, false);

                while (game->running()) {

                    whoWon = game->HandleEvents();
                }
                game->~Game();
                system("cls");
                if (whoWon == 1) {
                    __asm {
                        inc winFirstBot
                    }
                    //winFirstBot++;
                }
                else if (whoWon == 2) {
                    __asm {
                        inc winSecondBot
                    }
                    //winSecondBot++;
                }
                else if (whoWon == 0) {
                    __asm {
                        inc drawsCount
                    }
                    //drawsCount++;
                }
            }
            std::cout << "Hard bot 1 wins: " << winFirstBot <<
                "\nHard bot 2 bot wins: " << winSecondBot <<
                "\nDraws: " << drawsCount;
        }
        else if (answer == 1) {
            for (int y = 0; y < numTests; y++) {
                game = new Game("game_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false, choice, true);

                while (game->running()) {

                    frameStart = SDL_GetTicks();

                    game->HandleEvents();
                    game->update();
                    game->render();

                    frameTime = SDL_GetTicks() - frameStart;
                    if (frameDelay > frameTime) {
                        SDL_Delay(frameDelay - frameTime);
                    }
                }
                game->~Game();
            }
        }

    }
    return 0;
}