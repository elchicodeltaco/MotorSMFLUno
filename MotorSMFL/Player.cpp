#include "Player.h"
#include "commandQueue.h"
#include "Include/Aircraft.h"

#include <map>
#include <string>
#include <algorithm>

struct AircraftMover
{
	AircraftMover(float vx, float vy) : velocity(vx,vy)
	{}

	void operator() (Aircraft& avioncito, sf::Time) const
	{
		avioncito.accelerate(velocity);
	}
	sf::Vector2f velocity;
};

Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	
	initializeActions();

	// Asignar las categorías al avión del jugador

	for (auto& par : mActionBinding)
	{
		par.second.category = Category::PlayerAircraft;
	}
}

void Player::initializeActions()
{
	//vinculo la accion a la funcion ejecutada
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0, -playerSpeed));
	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(0, playerSpeed));

}

void Player::handleEvent(const sf::Event evento, commandQueue& comandos)
{
	// nos interesan los eventos de apretar tecla
	if (evento.type == sf::Event::KeyPressed)
	{
		//Verificar si la tecla apretada aparece en el binding de teclas
		// Y si así, activamos el evento
		auto encontrado = mKeyBinding.find(evento.key.code);
		if (encontrado != mKeyBinding.end() && !isRealtimeAction(encontrado->second))
		{
			comandos.push(mActionBinding[encontrado->second]);
		}
	}
}
bool Player::isRealtimeAction(Action accion)
{
	switch (accion)
	{
	case MoveLeft:
	case MoveRight:
	case MoveUp:
	case MoveDown:
		return true;
	default:
		return false;
	}
}

void Player::handleRealTimeInput(commandQueue& comandos)
{
	//checando las teclas asignadas para ver si están apretadas
	for (auto par : mKeyBinding)
	{
		// si las teclas están apretadas, buscamos la accion y activamos comandos
		if (sf::Keyboard::isKeyPressed(par.first) && isRealtimeAction(par.second))
		{
			comandos.push(mActionBinding[par.second]);
		}
	}
}

void Player::assignKey(Action accion, sf::Keyboard::Key tecla)
{
	//limpiar teclas que tengan mapeadas acciones
	for (auto iterador = mKeyBinding.begin(); iterador != mKeyBinding.end();)
	{
		if (iterador->second == accion)
			mKeyBinding.erase(iterador++);
		else
			++iterador;
	}
}

sf::Keyboard::Key Player::getAssignedKey(Action accion) const
{
	for (auto par : mKeyBinding)
	{
		if (par.second == accion)
			return par.first;
	}
	return sf::Keyboard::Unknown;

}