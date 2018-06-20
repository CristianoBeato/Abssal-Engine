
#ifndef _WIDGET_H_
#define _WIDGET_H_

typedef int (*btCallback)(void*);

class btEventHandler
{
public:
	btEventHandler(btCallback func);
	~btEventHandler(void);
	
	void	call(void* args);

private:
	btCallback m_callbackFunc;
};

class btWidget
{
public:

	//Widget options
	static const Uint32 GUI_DEFAULT = 0;
	static const Uint32 GUI_CENTERX = 1;
	static const Uint32 GUI_CENTERY = 2;
	static const Uint32 GUI_NO_NORMALIZE = 4;
	static const Uint32 GUI_NO_THEME = 8;
	static const Uint32 GUI_NO_FOCUS = 16;
	static const Uint32 GUI_CACHE = 32;
	static const Uint32 GUI_CENTERED = GUI_CENTERX | GUI_CENTERY;
	
	//Widget overflow
	static const Uint32 GUI_OVERFLOW_NONE = 0;
	static const Uint32 GUI_OVERFLOW_HIDDEN = 1;
	static const Uint32 GUI_OVERFLOW_REPLACE = 2;
	static const Uint32 GUI_OVERFLOW_CALLBACK = 3;

	//Mouse event states
	static const Uint32 GUI_MOUSE_NONE = 0;
	static const Uint32 GUI_MOUSE_CLICK = 1;
	static const Uint32 GUI_MOUSE_RELEASE = 2;
	static const Uint32 GUI_MOUSE_ACTIVE = 4;
	
	btWidget(void);
	btWidget(std::string name,
		btIntrusivePtr<btWidget> parent,
		glm::vec2 size = glm::vec2(1.0f, 1.0f),
		glm::vec2 pos = glm::vec2(0.0f, 0.0f),
		Uint32 options = GUI_DEFAULT);

	~btWidget(void);
	
	btIntrusivePtr<btWidget>	getWidget(const std::string name);
	void	attachWidget(btIntrusivePtr<btWidget> widget);
	void	removeWidget(btIntrusivePtr<btWidget> widget);

	virtual void	clear(void);

	//draw the frame;
	virtual void	draw(void);
	
	void	updatePosition(glm::vec2 pos);
	void	updateSize(glm::vec2 size);

	//handler callbacks
	void	onClick(btCallback callback);
	void	onRelease(btCallback callback);
	void	onHover(btCallback callback);
	void	onMouseEnter(btCallback callback);
	void	onMouseExit(btCallback callback);
	void	onActive(btCallback callback);
	
	void	parent(btIntrusivePtr<btWidget> setpat);
	const btIntrusivePtr<btWidget>	parent(void)const;
	btIntrusivePtr<btWidget>		parent(void);
	
	//animation
	void	move(glm::vec3 position, double time, btCallback callback);
	
protected:
	
	virtual void	handleClick(){};
	virtual void	handleRelease(){};
	virtual void	handleHover(){};
	virtual void	handleActive(){};
	virtual void	handleMouseEnter(){};
	virtual void	handleMouseExit(){};
	
private:
	void	handleMouse(glm::ivec2 pos, Uint32 event);
	void	onClick(void);
	void	onRelease(void);
	void	onHover(void);
	void	onMouseEnter(void);
	void	onMouseExit(void);
	void	onActive(void);

	bool				m_visible;
	bool				m_frozen;

	std::string							m_name;
	btIntrusivePtr<btWidget>			m_parent;
	std::map<std::string, btIntrusivePtr<btWidget>>	m_childrens;
	glm::vec2							m_position;
	glm::vec2							m_size;
	Uint32								m_widgetOps;
	
	btIntrusivePtr<btEventHandler>		m_onClick;
	btIntrusivePtr<btEventHandler>		m_onRelease;
	btIntrusivePtr<btEventHandler>		m_onHover;
	btIntrusivePtr<btEventHandler>		m_onActive;
	btIntrusivePtr<btEventHandler>		m_onMouseEnter;
	btIntrusivePtr<btEventHandler>		m_onMouseExit;
};

#endif //!_WIDGET_H_