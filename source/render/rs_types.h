
#ifndef _RENDER_TYPES_H_
#define _RENDER_TYPES_H_

//GL matematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//need to be included before SDL
//#define GLEW_STATIC
#include <GL/glew.h>

typedef glm::tvec3<GLubyte>		btColor;
typedef glm::tvec4<GLubyte>		btColorApha;
typedef glm::vec3				btColorF;
typedef glm::vec4				btColorAphaF;


#endif // !_RENDER_TYPES_H_
