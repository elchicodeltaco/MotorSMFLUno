#pragma once
#include "Comando.h"

#include <queue>

class commandQueue
{
public:
	void	push(const Comando& comando);
	Comando pop();
	bool	isEmpty() const;

private:
	std::queue<Comando> mQueue;
};

