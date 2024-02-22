#include "Include/Label.hpp"

#include<SFML/Graphics/RenderStates.hpp>
#include<SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Label::Label(const std::string& texto, const FontHolder& fonts)
		: mText(texto, fonts.get(Fonts::Main), 20)
	{

	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::handleEvent(const sf::Event&)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	void Label::setText(const std::string& texto)
	{
		mText.setString(texto);
	}
}