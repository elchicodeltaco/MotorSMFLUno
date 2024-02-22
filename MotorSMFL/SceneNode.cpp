#include "Include/SceneNode.h"
#include "Comando.h"

#include <cassert>

SceneNode::SceneNode()
	:mChildren()
	, mParent()
{
}

void SceneNode::attachChild(Ptr hijo)
{
	hijo->mParent = this;
	mChildren.push_back(std::move(hijo));
}

SceneNode:: Ptr SceneNode::detachChild(const SceneNode& nodo)
{
	auto found = std::find_if(
		mChildren.begin(), mChildren.end(),
		[&](Ptr& p) {return p.get() == &nodo; }
	);

	//Permite continuar con la función
	//Si se encuentra asignada la variable found
	assert(found != mChildren.end());

	//Guardar el nodo que encontramos

	Ptr resultado = std::move(*found);
	resultado->mParent = nullptr;
	mChildren.erase(found);
	return resultado;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);

}

void SceneNode::updateCurrent(sf::Time dt)
{
	for (Ptr& hijo : mChildren) {
		hijo->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target,
	sf::RenderStates states) const
{
	// Aplicar transformación del nodo actual
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target,
	sf::RenderStates states) const {
}

void SceneNode::drawChildren(sf::RenderTarget& target,
	sf::RenderStates states) const
{
	for (const Ptr& hijo : mChildren)
	{
		hijo->draw(target, states);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}
sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* nodo = this;
		nodo != nullptr;
		nodo = nodo->mParent)
	{
		transform = nodo->getWorldTransform() * transform;
	}
	return transform;
}

void SceneNode::onCommand(const Comando& comando, sf::Time dt)
{
	// Al llegar el comando al nodo, ejecutamos su acción si es que
	//encaja con la categoría
	if (comando.category & getCategory()) {
		comando.action(*this, dt);
	}

	for (Ptr& hijo : mChildren)
	{
		hijo->onCommand(comando, dt);
	}
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}