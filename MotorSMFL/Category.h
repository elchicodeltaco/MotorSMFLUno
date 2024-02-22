#pragma once


//Asignar posibles categoría a los nodos de la escena

namespace Category 
{
	enum Type
	{
		None			= 0,
		Scene			= 1 << 0,
		PlayerAircraft  = 1 << 1,
		AlliedCraft		= 1 << 2,
		EnemyCraft		= 1 << 3,

	};
}