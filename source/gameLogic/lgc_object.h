
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_
 
class btGameObject
{
public:
	btGameObject(void);
	btGameObject(btGameObject * parent, const std::string name);
	~btGameObject(void);

	//get the object position in local space;
	glm::vec3	getLocalPosition(void)const;
	
	//return the object in the final world position
	glm::vec3	getWorldPosition(void)const;

private:
	btGameObject*					m_parent;
	std::vector<btGameObject*>		m_childrens;
	std::string						m_name;

	//local space postion
	glm::vec3						m_position;

	//the local space object size
	glm::vec3						m_scale;

	//the object orientation
	glm::quat						m_orientation;
};

#endif // !_GAME_OBJECT_H_
