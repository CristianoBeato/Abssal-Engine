
#ifndef _PNG_LOADER_H_
#define _PNG_LOADER_H_

class btPNGLoader : public btImageLoader
{
public:
	btPNGLoader(void);
	~btPNGLoader(void);

	//Load Image
	virtual bool	loadFromFile(const std::string file);
	//save image
	virtual bool	saveToFile(const std::string file);

private:

};

#endif // !_PNG_LOADER_H_
