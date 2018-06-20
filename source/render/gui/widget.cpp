
#include "precompiled.h"
#pragma hdrstop

#include "widget.h"

btEventHandler::btEventHandler(btCallback func) : m_callbackFunc(func)
{
}

btEventHandler::~btEventHandler(void)
{
}

void btEventHandler::call(void* args)
{
	m_callbackFunc(args);
}

btWidget::btWidget(void) : 
	m_parent(NULL), 
	m_name("\0"),
	m_position(glm::vec2(0.0f, 0.0f)),
	m_size(glm::vec2(1.0f, 1.0f)),
	m_widgetOps(GUI_DEFAULT)
{
	m_onClick = NULL;
	m_onRelease = NULL;
	m_onHover = NULL;
	m_onActive = NULL;
	m_onMouseEnter = NULL;
	m_onMouseExit  = NULL;
}

btWidget::btWidget(std::string name, 
	btIntrusivePtr<btWidget> parent, 
	glm::vec2 size, 
	glm::vec2 pos,
	Uint32 options):
	m_parent(parent),
	m_name(name),
	m_size(size),
	m_position(pos),
	m_widgetOps(options)
{
	m_onClick = NULL;
	m_onRelease = NULL;
	m_onHover = NULL;
	m_onActive = NULL;
	m_onMouseEnter = NULL;
	m_onMouseExit = NULL;
}

btWidget::~btWidget(void)
{
}

btIntrusivePtr<btWidget> btWidget::getWidget(const std::string name)
{
	return btIntrusivePtr<btWidget>();
}

void btWidget::attachWidget(btIntrusivePtr<btWidget> widget)
{
	//sanity check
	if (!widget.validade())
		return;

	//TODO: check if already in the cildrens 

	//append in the list
	m_childrens[widget->m_name] = widget;

	//set parent
	widget->parent(this);
}

void btWidget::removeWidget(btIntrusivePtr<btWidget> widget)
{
	m_childrens.erase(widget->m_name);
}

void btWidget::clear(void)
{
	for (auto child : m_childrens)
	{
		if (child.second.validade())
			child.second->clear();
	}

	m_childrens.clear();
}

void btWidget::draw(void)
{
	for (auto child : m_childrens)
	{
		if (child.second.validade())
			child.second->draw();
	}
}

void btWidget::updatePosition(glm::vec2 pos)
{
	m_position = pos;
}

void btWidget::updateSize(glm::vec2 size)
{
	m_size = size;
}

void btWidget::onClick(btCallback callback)
{
	m_onClick = new btEventHandler(callback);
}

void btWidget::onRelease(btCallback callback)
{
	m_onRelease = new btEventHandler(callback);
}

void btWidget::onHover(btCallback callback)
{
	m_onHover = new btEventHandler(callback);
}

void btWidget::onMouseEnter(btCallback callback)
{
	m_onMouseEnter = new btEventHandler(callback);
}

void btWidget::onMouseExit(btCallback callback)
{
	m_onMouseExit = new btEventHandler(callback);
}

void btWidget::onActive(btCallback callback)
{
	m_onActive = new  btEventHandler(callback);
}

void btWidget::move(glm::vec3 position, double time, btCallback callback)
{
}

void btWidget::parent(btIntrusivePtr<btWidget>	setpat)
{
	m_parent = setpat;
}

const btIntrusivePtr<btWidget> btWidget::parent(void) const
{
	return m_parent;
}

btIntrusivePtr<btWidget> btWidget::parent(void)
{
	return m_parent;
}
