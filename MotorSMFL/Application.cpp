#include "Include/Application.h"
#include "Include/State.hpp"
#include "Include/StateIdentifiers.hpp"
#include "Include/StringHelpers.h"
#include <SFML/Window/Event.hpp>

#include "Include//Estados/GameState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application() :
	mWindow(sf::VideoMode(800, 600), "Juego", sf::Style::Close)
	, mPlayer()
	, mTextures()
	, mFonts()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
	, mStatisticsNumFrames(0)
	, mStatisticsText()
	, mStatisticsUpdateTime()
{
	mWindow.setKeyRepeatEnabled(false);

	//mFont.loadFromFile("Assets/Sansation.ttf");
	mFonts.load(Fonts::Main, "Assets/Sansation.ttf");

	mTextures.load(Textures::FondoPantallaTitulo, "Assets/Textures/MainTittle.jfif");
	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(15);

	//Agregar o registrar los estados que tendra el juego
	registerStates();
	//cual es el estado eb el que inicia el juego
	mStateStack.pushState(States::Game);
}

void Application::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
			//verificamos si hay estados en la pila
			// talvez este vacia antes de llamar a update
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Application::processInput()
{
	//obtenemos la cola de comandos del mundo
	//commandQueue& comandos = mWorld.getCommandQueue();
	//el jugador interactua con la ventana
	sf::Event evento;

	while (mWindow.pollEvent(evento))
	{
		//El evento que haya llegado, le decimos a player que lo atienda
		//mPlayer.handleEvent(evento, comandos);
		mStateStack.handleEvent(evento);

		//en el caso de que sea evento dee ventana
		if (evento.type == sf::Event::Closed)
			mWindow.close();
	}

	//mPlayer.handleRealTimeInput(comandos);

}

void Application::update(sf::Time elapsedTime)
{
	//Tenemos que comunicarle al world que le diga a los nodos de la escena que se actruaize
	//mWorld.update(elapsedTime);
	mStateStack.update(elapsedTime);

}

void Application::render()
{
	mWindow.clear();
	//mandamos la instruccion para que se dibuje el esado
	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.draw(mStatisticsText);

	mWindow.display();
}



void Application::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("Frames / segundo = " + toString(mStatisticsNumFrames) + "\n" + "Tiempo / update = "
			+ toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<GameState>(States::Game);
	//mStateStack.registerState<TitleState>(States::Title);
	//mStateStack.registerState<MenuState>(States::Menu);
}