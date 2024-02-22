#include "Include/Estados/GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window)
	, mPlayer(*context.player)
{

}

void GameState::draw()
{
	mWorld.draw(); // aqui ya dibujamos el nivel/escenario

}

bool  GameState::update(sf::Time dt)
{
	mWorld.update(dt); // aqui se actualiza el nivel
	commandQueue& comandos = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInput(comandos);
	return true;
}

bool GameState::handleEvent(const sf::Event& evento)
{
	//Manejo de entradas de juego
	commandQueue& comandos = mWorld.getCommandQueue();
	mPlayer.handleEvent(evento, comandos);

	// podriamos detectar si se aprieta la tecla de pause para ir a ese estado (pauseState)
	return true;
}