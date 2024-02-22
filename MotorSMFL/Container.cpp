#include "Include/Container.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Container::Container()
		: mChildren()
		, mSelectedChild(-1)
	{
	}

	void Container::pack(Component::Ptr componente)
	{
		//Agregamos el nuevo elemento al vector de componentes
		mChildren.push_back(componente);
		//si no hay elemento seleccionado, seleccionamos este
		if (!hasSelection() && componente->isSelectable())
			select(mChildren.size() - 1);
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	void Container::handleEvent(const sf::Event& evento)
	{
		//Si tenemos seleccionado algún algún objeto 
		if (hasSelection() && mChildren[mSelectedChild]->isActive())
		{
			mChildren[mSelectedChild]->handleEvent(evento);
		}
		else if (evento.type == sf::Event::KeyReleased)
		{
			if (evento.key.code == sf::Keyboard::W ||
				evento.key.code == sf::Keyboard::Up)
			{
				selectPrevious();//seleccionar elemento de ui anterior
			}
			else if (evento.key.code == sf::Keyboard::S ||
				evento.key.code == sf::Keyboard::Down)
			{
				selectNext(); //seleccionamos el siguiente de la ui
			}
		}
		else if (evento.key.code == sf::Keyboard::Return ||
			evento.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				mChildren[mSelectedChild]->activate();
		}
	}
	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//aplicamos transformacion al elemento
		states.transform *= getTransform();
		// mandamos a dibujar a cada elemento en el contenedor
		for (const Component::Ptr& hijo : mChildren)
			target.draw(*hijo, states);
	}
	bool Container::hasSelection() const
	{
		return mSelectedChild >= 0;

	}
	void Container::select(std::size_t index)
	{
		// verificamos que el elemento se pueda seleccionar
		if (mChildren[index]->isSelectable())
		{
			// en caso de que ya haya un elemento seleccionado lo deseleccionamos
			if (hasSelection())
				mChildren[mSelectedChild]->deselect();

			// selecciono el nuevo elemento
			mChildren[index]->select();
			mSelectedChild = index;
		}
	}
	//Hola
	void Container::selectNext()
	{
		if (!hasSelection()) return;

		//Buscamos el siguiente elemento que sea seleccionable
		int siguiente = mSelectedChild;
		do
			siguiente = (siguiente + 1) % mChildren.size();
		while (!mChildren[siguiente]->isSelectable());

		// seleccionamos el elemento
		select(siguiente);
	}

	void Container::selectPrevious()
	{
		if (!hasSelection()) return;

		int anterior = mSelectedChild;
		do
			anterior = (anterior + mChildren.size() - 1) % mChildren.size();
		while (!mChildren[anterior]->isSelectable());

		select(anterior);
	}

	
}