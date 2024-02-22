#pragma once
#include "Include/StateStack.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{

}

void StateStack::update(sf::Time dt)
{

	for (auto iterador = mStack.rbegin(); iterador != mStack.rend(); ++iterador)
	{
		if (!(*iterador)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	//Dibujamos todo los estados activos de abajo hacia arriba
	for (State::Ptr& estado : mStack)
		estado->draw();
}

void StateStack::handleEvent(const sf::Event& evento)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(evento))
			break;

	}
	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}
void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto encontrado = mFactories.find(stateID);
	assert(encontrado != mFactories.end());

	return encontrado->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange cambio : mPendingList)
	{
		switch (cambio.action)
		{
		case Push:
			mStack.push_back(createState(cambio.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}
	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action accion, States::ID stateID)
	:action(accion)
	, stateID(stateID)
{

}