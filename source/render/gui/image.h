
#ifndef _GUI_IMAGE_H_
#define _GUI_IMAGE_H_

class btTexture;

class btWidgetImage : public btWidget
{
public:
	btWidgetImage(void);
	btWidgetImage(std::string name, btWidget* parent,
				glm::vec2 size,
				glm::vec2 pos,
				glm::vec2 imageRect[4] ,
				Uint32 options = GUI_DEFAULT);
				
	~btWidgetImage(void);
	
	void	clear(void);
	void	draw(void);
	
	void	updateImage(glm::vec2 imageRect, std::string imagePath);
	
private:
	//the image
	btTexture*	m_image;

	//textures cordinates
	glm::vec2	m_imageRect[4];
};

#endif //!_GUI_IMAGE_H_