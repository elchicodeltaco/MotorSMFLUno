#include "commandQueue.h"
#include "Include//SceneNode.h"

void commandQueue::push(const Comando& comando) 
{
	mQueue.push(comando);
}

Comando commandQueue::pop() {
	Comando comandoTemporal = mQueue.front();
	mQueue.pop();
	return comandoTemporal;
}

bool commandQueue::isEmpty() const
{
	return mQueue.empty();
}