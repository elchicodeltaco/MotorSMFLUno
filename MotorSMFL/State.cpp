#include "Include/State.hpp"
#include "Include/StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
	Player& player)
	:window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
{
}
State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)

{
}
State::~State()
{}
//Solicita agregar un estado a la pila
void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}
//El estado solicita eliminar un estado de la pila
void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}