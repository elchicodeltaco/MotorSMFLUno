#include "Include/Estados/MenuState.hpp"
#include "Include/Button.hpp"
#include "Include/ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

MenuState::MenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mGUIContainer()
{
	sf::Texture& textura = context.textures->get(Textures::FondoPantallaTitulo);
	mBackgroundSprite.setTexture(textura);

	auto botonJugar = std::make_shared<GUI::Button>(*context.fonts, context.textures);
	botonJugar->setPosition(200, 300);
	botonJugar->setText("Jugar");
	botonJugar->setCallback([this]()
		{
			requestStackPop();
			requestStackPush(States::Game);
		});

	auto botonSalir = std::make_shared<GUI::Button>(*context.fonts, context.textures);
	botonJugar->setPosition(200, 600);
	botonJugar->setText("Salir");
	botonJugar->setCallback([this]()
		{
			requestStackPop();
			
		});

	mGUIContainer.pack(botonJugar);
	mGUIContainer.pack(botonSalir);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
	
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& evento)
{
	mGUIContainer.handleEvent(evento);
	return false;
}