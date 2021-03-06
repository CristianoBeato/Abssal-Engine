
#include "precompiled.h"
#pragma hdrstop

#include "gameLogic/lgc_object.h"

btGameObject::btGameObject()
{
}

btGameObject::btGameObject(btGameObject * parent, const std::string name) : m_parent(parent), m_name(name)
{
	//append children 
	if (parent != NULL)
		parent->m_childrens.push_back(this);
}

btGameObject::~btGameObject()
{
}

glm::vec3 btGameObject::getLocalPosition(void) const
{
	return m_position;
}

glm::vec3 btGameObject::getWorldPosition(void) const
{
	return glm::vec3();
}
