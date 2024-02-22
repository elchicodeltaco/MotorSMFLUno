#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateStack.hpp"
#include "../Player.h"

#include <SFML/System/Time.hpp>
//#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application : private sf::NonCopyable
{
	public:
								Application();
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time elapsedTime);
		void					render();

		void					updateStatistics(sf::Time elapsedTime);	
		//void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		void					registerStates();

	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		//World					mWorld;
		Player					mPlayer;

		TextureHolder			mTextures;
		FontHolder				mFonts;

		StateStack				mStateStack;

	  	//sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};