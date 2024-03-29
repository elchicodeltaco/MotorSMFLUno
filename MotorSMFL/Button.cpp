#include "Include/Button.hpp"

#include <SFML/Window/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Button::Button(const FontHolder& fonts, const TextureHolder& textures)
		: mCallback()
		, mNormalTexture(textures.get(Textures::ButtonNormal))
		, mSelectedTexture(textures.get(Textures::ButtonSelected))
		, mPressedTexture(textures.get(Textures::ButtonPressed))
		, mSprite()
		, mText("", fonts.get(Fonts::Main), 20)
		, mIsToggle(false)
	{
		mSprite.setTexture(mNormalTexture);//asignamos imagen al bot�n

		sf::FloatRect bounds = mSprite.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	void Button::setText(const std::string& texto)
	{
		mText.setString(texto);
	}
	
	void Button::setToggle(bool flag)
	{
		mIsToggle = flag;
	}

	bool Button::isSelectable() const
	{
		return true;
	}
	void Button::select()
	{
		Component::select();
		mSprite.setTexture(mNormalTexture);
		
	}

	void Button::deselect()
	{
		Component::deselect();
		mSprite.setTexture(mNormalTexture);
	}

	void Button::activate()
	{
		Component::activate();
		//si estamos en toggle, entonces mostamos que el bot�n est� apretado
		if (mIsToggle)
			mSprite.setTexture(mPressedTexture);
		//Si  tiene una funcion, hacemos callback
		if (mCallback)
			mCallback();
		//Si no estamos en toggle, desactivamos el bot�n.
		if (!mIsToggle)
			deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();
			if (mIsToggle) {
				if (isSelected())
					mSprite.setTexture(mSelectedTexture);
				else
					mSprite.setTexture(mNormalTexture);			
				
			}
	}
	void Button::handleEvent(const sf::Event&)
	{

	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states); //primero dibujamos el bot�n
		target.draw(mText, states); //encima el texto
	}
}
