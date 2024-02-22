#include "Include/Aircraft.h"
#include "Include/ResourceHolder.h"

#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(Aircraft::Type tipo)
{

	switch (tipo)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;

	case Aircraft::Raptor:
		return Textures::Raptor;
	}
	
	return Textures::Eagle;

}

Aircraft::Aircraft(Type tipo, const TextureHolder& textures)
	:mType(tipo)
	, mSprite(textures.get(toTextureID(tipo)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite, setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target,
	sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Aircraft::Eagle:
		return Category::PlayerAircraft;

	case Aircraft::Raptor:

	default:
		return Category::EnemyCraft;
	}
}