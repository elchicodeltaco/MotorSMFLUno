#pragma once

#include "Comando.h"

#include <SFML/Window/Event.hpp>

#include <map>

class commandQueue;

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount,
	};

public:
	Player();
	void handleEvent(const sf::Event event, commandQueue& comandos);
	void handleRealTimeInput(commandQueue& comandos);

	void assignKey(Action accion, sf::Keyboard::Key tecla);
	sf::Keyboard::Key getAssignedKey(Action accion) const;

	bool isRealtimeAction(Action accion);

private:
	void initializeActions();
private:
	std::map<sf::Keyboard::Key, Action>mKeyBinding;
	std::map<Action, Comando>		   mActionBinding;

	float playerSpeed = 200.f;
};


