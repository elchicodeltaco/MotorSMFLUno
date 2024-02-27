#include "TittleState.h"

#include "Include/ResourceHolder.h"
#include <SFML/Graphics/RenderWindow.hpp>

TittleState::TittleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::FondoPantallaTitulo));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("Presiona Cualquier Tecla para iniciar");

	mText.setPosition(sf::Vector2f(context).window->getSize() / 2u);
}

void TittleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText) //La intencion es un efecto de parpadeo en el texto
		window.draw(mText);
}

bool TittleState::update(sf::Time dt) {

	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f)) //Prender y apagar cada medio segundo la variable
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	return true;
}

bool TittleState::handleEvent(const sf::Event& evento)
{
	if (evento.type == sf::Event::KeyReleased)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}
	return true;
}