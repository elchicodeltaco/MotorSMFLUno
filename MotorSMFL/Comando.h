#pragma once

#include "Category.h"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>
class SceneNode; // forward declaration, aviso que existe

struct Comando
{
	Comando();

	std::function<void(SceneNode&, sf::Time) > action;

	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return[=](SceneNode& node, sf::Time dt)
	{
		// Verificar si puedo hacer un cast
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		//hago el downcast del nodo e invoco la función en ese nodo
		fn(static_cast<GameObject&>(node), dt);
	};
}


