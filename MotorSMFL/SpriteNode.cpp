#include "Include/SpriteNode.h"
#include <SFML/Graphics/RenderTarget.hpp>

SpriteNode::SpriteNode(const sf::Texture& textura)
	: mSprite(textura)
{

}

SpriteNode::SpriteNode(const sf::Texture& textura, const sf::IntRect& textureRect)
	: mSprite(textura, textureRect)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}