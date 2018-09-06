#include "Logic.h"

Logic::Logic():screen_state_{ScreenState::SPLASHSCREEN}
{
    player_ = std::make_shared<Player>(grid_);
    game_objects_.push_back(player_);
    moving_game_objects.push_back(player_);
    //ctor
}

void Logic::getInputCommands()
{
    presentation_.processInputEvents();
}


void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();


}
void Logic::loadAssets()
{

}

void Logic::renderSplashScreen()
{
    presentation_.drawSplashScreen();
    screen_state_ = ScreenState::GAME_ACTIVE;
}

void Logic::renderGameObjects()
{

}

void Logic::renderGameOverScreen()
{

}

void Logic::renderGameWonScreen()
{

}


Logic::~Logic()
{
    //dtor
}