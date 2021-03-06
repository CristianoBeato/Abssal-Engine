
#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <map>
#include "sys/memory/mem_pointers.h"
#include "sys/fileSystem/fs_stream.h"

class btDictKey :
	public btRefObj	//reference counter
{
public:
	friend class btDictionary;

	enum KeyType
	{
		KT_UNKNOW = 0,
		KT_BOOL,
		KT_FLOAT,
		KT_CHAR,	//8
		KT_UCHAR,	//8
		KT_SHORT,	//16
		KT_USHORT,	//16
		KT_INT,		//32
		KT_UINT,
		KT_STRING,
	};

	btDictKey(void);
	btDictKey(std::string name, void* value, const KeyType type, btDictKey* parent = NULL);
	~btDictKey(void);

	const std::string		getName(void);
	KeyType					getKeyType(void);
	const bool				getBool(void);
	const char				getChar(void);
	const unsigned char		getUChar(void);
	const short				getShort(void);
	const unsigned short	getUShort(void);
	const int				getInt(void);
	const unsigned int		getUInt(void);
	const float				getFloat(void);
	const char*				getString(void);

protected:

	//this is for save the dict
	//here we write in a json file;
	void	writeKey(btIntrusivePtr<char> key);

	//this is for save dict in 
	//internal binary mode
	void	writeKey(btIntrusivePtr<btStream> &outbuff);


private:

	//key name
	std::string	m_name;

	//key parent
	btDictKey	*m_parent;

	//type of the key
	KeyType		m_dataType;
	//the value of the key
	//btIntrusivePtr<char>	m_value;
	void *		m_value;

	void			writeBool(btIntrusivePtr<char> key);
	void			writeBinBool(btIntrusivePtr<btStream> &outbuff);
	void			writeChar(btIntrusivePtr<char> key);
	void			writeBinChar(btIntrusivePtr<btStream> &outbuff);
	void			writeShort(btIntrusivePtr<char> key);
	void			writeBinShort(btIntrusivePtr<btStream> &outbuff);
	void			writeInt(btIntrusivePtr<char> key);
	void			writeBinInt(btIntrusivePtr<btStream> &outbuff);
	void			writeFloat(btIntrusivePtr<char> key);
	void			writeBinFloat(btIntrusivePtr<btStream> &outbuff);
	void			writeString(btIntrusivePtr<char> key);
	void			writeBinString(btIntrusivePtr<btStream> &outbuff);
};

class btDictionary:
	public btRefObj
{
public:
	btDictionary(void);
	~btDictionary(void);

	void			addInt(const std::string keyName, const Sint32 keyVal, btDictKey* parent = NULL);
	const Sint32	getInt(const std::string keyName) const;
	void			addShort(const const std::string keyName, const Sint16 keyVal, btDictKey* parent = NULL);
	const Sint16	getShort(const std::string keyName) const;
	void			addChar(const std::string keyName, const Sint8 keyVal, btDictKey* parent = NULL);
	const Sint8		getChar(const std::string keyName) const;
	void			addFloat(const std::string keyName, const float keyVal, btDictKey* parent = NULL);
	const float		getFloat(const std::string keyName) const;
	void			addString(const std::string keyName, const std::string keyVal, btDictKey* parent = NULL);
	const char*		getString(const std::string keyName) const;

	//return the dict key
	const btIntrusivePtr<btDictKey> getKey(const std::string keyName) const;

	//this is for save the dict
	//here we write in a json file;
	void	writeKeys(btIntrusivePtr<char> key);

	//this is for save dict in 
	//internal binary mode
	void	writeKeys(btIntrusivePtr<btStream> &outbuff);

private:
	std::map<std::string, btIntrusivePtr<btDictKey>> m_DictionaryKeys;
};

#endif // !_DICTIONARY_H_
