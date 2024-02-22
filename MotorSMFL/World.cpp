#include "Include//World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
	, mSpawnPosition(mWorldView.getSize().x / 2.f,
		mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(50.f)
	, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

}

void World::update(sf::Time dt)
{
	// Scroll del mundo
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);

	//Enviar los comandos al grafo de la escena
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
		adaptPlayerPosition();
	}

	//Paso de update regulta, adaptamos la posición (Corregir por si se sale)
	mSceneGraph.update(dt);
	adaptPlayerPosition();



}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures() {

	mTextures.load(Textures::Eagle, "Assets/Texturas/Avion.png");
	mTextures.load(Textures::Raptor, "Assets/Texturas/Dino.png");
	mTextures.load(Textures::Desert, "Assets/Texturas/Desierto.png");

}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; i++) {
		SceneNode::Ptr layer(new SceneNode());
		//guardo en arreglo de capas
		mSceneLayers[i] = layer.get();
		//Emparento al nodo raiz
		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& textura = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	textura.setRepeated(true);

	std::unique_ptr<SpriteNode> spriteFondo(new SpriteNode(textura, textureRect));
	spriteFondo->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(spriteFondo));

	//Agregamos el nodo del jugador 
	std::unique_ptr<Aircraft> avioncito(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = avioncito.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(50.f, 0.f);
	mSceneLayers[Air]->attachChild(std::move(avioncito));
}

commandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::adaptPlayerPosition()
{
	//Mantener la posicion del jugador dentro los limites de la pantalla
	//a distancia del borde
	sf::FloatRect limitesVista(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());

	const float borderDistance = 40.f;
	
	sf::Vector2f posicion = mPlayerAircraft->getPosition();
	posicion.x = std::max(posicion.x, limitesVista.left + borderDistance);
	posicion.x = std::min(posicion.x, limitesVista.left + limitesVista.width - borderDistance);

	posicion.y = std::max(posicion.y, limitesVista.top + borderDistance);
	posicion.y = std::min(posicion.y, limitesVista.top + limitesVista.height - borderDistance);

	mPlayerAircraft->setPosition(posicion);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocidad = mPlayerAircraft->getVelocity();

	//si se está moviendo en diagonal, reducimos su vel

	if (velocidad.x != 0.f && velocidad.y != 0)
	{
		mPlayerAircraft->setVelocity(velocidad / std::sqrt(2.f));
	}

	//sumamos la velocidad del escenario

	mPlayerAircraft->accelerate(0.f, mScrollSpeed); 
}