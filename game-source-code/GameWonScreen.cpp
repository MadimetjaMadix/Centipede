#include "GameWonScreen.h"
using namespace std::literals::string_literals;

GameWonScreen::GameWonScreen()
{
    //ctor
    //gameWonTexture_.loadFromFile("Assets/Winner Background.png"s);
}

void GameWonScreen::show(sf::RenderWindow& render_window,
          const int& player_score, const int& high_score)
{
    //Load background texture:
    //sf::Sprite background_sprite;
    //background_sprite.setTexture(gameWonTexture_);

    //Load font:
    font_.loadFromFile("Assets/Font.otf"s);

    auto game_won_title = "\t\t Awesome! \n You defeated us."s;
    sf::Text title(game_won_title, font_);
    title.setCharacterSize(48);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,
    titleRect.top  + titleRect.height/2.0f);
    //title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Green);
    title.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,render_window.getSize().y/2.0f - 150));

    auto game_won_controls = "Exit -> Press Enter"s;
    sf::Text controls(game_won_controls, font_);
    sf::FloatRect textRect = controls.getLocalBounds();
    controls.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top  + textRect.height/2.0f);
    controls.setFillColor(sf::Color::Red);
    controls.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,render_window.getSize().y/2.0f + 150));

    // Player score:
    auto score_text = "\t You scored: "s+std::to_string(player_score);
    sf::Text score(score_text, font_);
    score.setCharacterSize(30);
    sf::FloatRect scoreRect = score.getLocalBounds();
    score.setOrigin(scoreRect.left + scoreRect.width/2.0f,
    scoreRect.top  + scoreRect.height/2.0f);
    score.setFillColor(sf::Color::Red);
    score.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,render_window.getSize().y/2.0f));

    // Highscore:
    auto high_score_text = "\t Highscore: "s+std::to_string(high_score);
    sf::Text game_high_score(high_score_text, font_);
    sf::FloatRect highRect = game_high_score.getLocalBounds();
    game_high_score.setOrigin(highRect.left + highRect.width/2.0f,
    highRect.top  + highRect.height/2.0f);
    game_high_score.setFillColor(sf::Color::Red);
    game_high_score.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,render_window.getSize().y/2.0f +30));
    //game_high_score.setStyle(sf::Text::Bold);

    //Draw:
    //render_window.draw(background_sprite);
	render_window.clear(sf::Color(0,0,0));
    render_window.draw(title);
    render_window.draw(controls);
    render_window.draw(score);
    render_window.draw(game_high_score);
    render_window.display();

    // Poll for keyboard event:
    sf::Event event;
    while(true){
        while(render_window.pollEvent(event)){
            if(event.key.code == sf::Keyboard::Enter){
                render_window.close();
                return;
            }//if
        }//while
    }//while

}//show


GameWonScreen::~GameWonScreen()
{
    //dtor
}
