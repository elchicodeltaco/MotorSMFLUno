#pragma once
#include "Include/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TittleState :
    public State
{

public:
	TittleState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	sf::Sprite				mBackgroundSprite;
	sf::Text				mText;

	bool::					mShowText;
	sf::Time				mTextEffectTime;
};

