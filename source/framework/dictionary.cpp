
#include "precompiled.h"
#pragma hdrstop

#include "dictionary.h"

btDictKey::btDictKey(void) : m_value(nullptr), m_dataType(KT_UNKNOW), m_parent(NULL)
{
}

btDictKey::btDictKey(std::string name, void* value, const KeyType type, btDictKey* parent) :
	m_name(name),
	m_value(value), 
	m_dataType(type),
	m_parent(parent)
{
}

btDictKey::~btDictKey(void)
{
	m_name.clear();
	m_dataType = KT_UNKNOW;
}

const std::string btDictKey::getName(void)
{
	return m_name;
}

btDictKey::KeyType btDictKey::getKeyType(void)
{
	return m_dataType;
}

const bool btDictKey::getBool(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_BOOL);
	//return (char)(*m_value.getInternalPtr()) != 0;
	return m_value != NULL;
}

const char btDictKey::getChar(void)
{
	//check if are a correct data type, and consistent pointer
	SDL_assert(m_dataType != KT_CHAR && m_value != NULL);
	//return *m_value.getInternalPtr();
	return *static_cast<Sint8*>(m_value);
}

const unsigned char btDictKey::getUChar(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_UCHAR && m_value != NULL);
	//return *(unsigned char*)m_value.getInternalPtr();
	return *static_cast<Uint8*>(m_value);
}

const short btDictKey::getShort(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_SHORT && m_value != NULL);

	//btIntrusivePtr<short> valref = m_value.dynamicCast<short>();
	//return *valref.getInternalPtr();
	return *static_cast<short*>(m_value);
}

const unsigned short btDictKey::getUShort(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_USHORT && m_value != NULL);

	//btIntrusivePtr<unsigned short> valref = m_value.dynamicCast<unsigned short>();
	//return *valref.getInternalPtr();
	return *static_cast<Uint16*>(m_value);
}

const int btDictKey::getInt(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_INT && m_value != NULL);

	//btIntrusivePtr<int> valref = m_value.staticCast<int>();
	//return *valref.getInternalPtr();
	return *static_cast<Sint32*>(m_value);
}

const unsigned int btDictKey::getUInt(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_UINT && m_value != NULL);

	//btIntrusivePtr<unsigned int> valref = m_value.staticCast<unsigned int>();
	//return *valref.getInternalPtr();
	return *static_cast<Uint32*>(m_value);
}

const float btDictKey::getFloat(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_FLOAT && m_value != NULL);
	//btIntrusivePtr<float> valref = m_value.staticCast<float>();
	//return *valref.getInternalPtr();
	return *static_cast<float*>(m_value);
}

const char * btDictKey::getString(void)
{
	//check if are a correct data type
	SDL_assert(m_dataType != KT_STRING);
	//btIntrusivePtr<char> valref = m_value.staticCast<char>();
	//return valref.getInternalPtr();
	return static_cast<const char*>(m_value);
}

void btDictKey::writeKey(btIntrusivePtr<char> key)
{
	switch (m_dataType)
	{
	case btDictKey::KT_BOOL:
		writeBool(key);
		break;
	case btDictKey::KT_FLOAT:
		writeFloat(key);
		break;
	case btDictKey::KT_CHAR:
		writeChar(key);
		break;
	case btDictKey::KT_SHORT:
		writeShort(key);
		break;
	case btDictKey::KT_INT:
		writeInt(key);
		break;
	case btDictKey::KT_STRING:
		writeString(key);
		break;
	default:
		gConsole.error("Ivalid Dict Key");
		break;
	}
}

void btDictKey::writeKey(btIntrusivePtr<btStream>& outbuff)
{
	switch (m_dataType)
	{
	case btDictKey::KT_BOOL:
		writeBinBool(outbuff);
		break;
	case btDictKey::KT_FLOAT:
		writeBinFloat(outbuff);
		break;
	case btDictKey::KT_CHAR:
		writeBinChar(outbuff);
		break;
	case btDictKey::KT_SHORT:
		writeBinFloat(outbuff);
		break;
	case btDictKey::KT_INT:
		writeBinInt(outbuff);
		break;
	case btDictKey::KT_STRING:
		writeBinString(outbuff);
		break;
	default:
		gConsole.error("Ivalid Dict Key");
		break;
	}
}



void btDictKey::writeBool(btIntrusivePtr<char> key)
{
}

void btDictKey::writeBinBool(btIntrusivePtr<btStream>& outbuff)
{
}

void btDictKey::writeChar(btIntrusivePtr<char> key)
{
	key = (char*)std::to_string(getChar()).c_str();
}

void btDictKey::writeBinChar(btIntrusivePtr<btStream>& outbuff)
{
}

void btDictKey::writeShort(btIntrusivePtr<char> key)
{
	key = (char*)std::to_string(getShort()).c_str();
}

void btDictKey::writeBinShort(btIntrusivePtr<btStream>& outbuff)
{
}

void btDictKey::writeInt(btIntrusivePtr<char> key)
{
	key = (char*)std::to_string(getInt()).c_str();
}

void btDictKey::writeBinInt(btIntrusivePtr<btStream>& outbuff)
{

}

void btDictKey::writeFloat(btIntrusivePtr<char> key)
{
	key = (char*)std::to_string(getFloat()).c_str();
}

void btDictKey::writeBinFloat(btIntrusivePtr<btStream>& outbuff)
{
}

void btDictKey::writeString(btIntrusivePtr<char> key)
{
	key = (char*)m_value;
}

void btDictKey::writeBinString(btIntrusivePtr<btStream>& outbuff)
{
}

/*
====================================================================================================

====================================================================================================
*/
btDictionary::btDictionary(void)
{
}

btDictionary::~btDictionary(void)
{
}

void btDictionary::addInt(const std::string keyName, const Sint32 keyVal, btDictKey * parent)
{
	m_DictionaryKeys[keyName] = new btDictKey(keyName, (void*)(&keyVal), btDictKey::KT_INT, parent);;
}

const Sint32 btDictionary::getInt(const std::string keyName) const
{
	btIntrusivePtr<btDictKey> key = getKey(keyName);
	//check if key are a right type
	SDL_assert(key->getKeyType() != btDictKey::KT_INT);

	//check key consistency
	if (!key.validate() || key->getKeyType() != btDictKey::KT_INT)
		return 0;

	return key->getInt();
}

void btDictionary::addShort(const const std::string keyName, const Sint16 keyVal, btDictKey * parent)
{
	m_DictionaryKeys[keyName] = new btDictKey(keyName, (void*)(&keyVal), btDictKey::KT_SHORT, parent);;
}

const Sint16 btDictionary::getShort(const std::string keyName) const
{
	btIntrusivePtr<btDictKey> key = getKey(keyName);
	//check if key are a right type
	SDL_assert(key->getKeyType() != btDictKey::KT_SHORT);

	//check key consistency
	if (!key.validate() || key->getKeyType() != btDictKey::KT_SHORT)
		return 0;

	return key->getShort();
}

void btDictionary::addChar(const std::string keyName, const Sint8 keyVal, btDictKey * parent)
{
	m_DictionaryKeys[keyName] = new btDictKey(keyName, (void*)(&keyVal), btDictKey::KT_CHAR, parent);;
}

const Sint8 btDictionary::getChar(const std::string keyName) const
{
	btIntrusivePtr<btDictKey> key = getKey(keyName);
	//check if key are a right type
	SDL_assert(key->getKeyType() != btDictKey::KT_CHAR);

	//check key consistency
	if (!key.validate() || key->getKeyType() != btDictKey::KT_CHAR)
		return 0;

	return key->getChar();
}

void btDictionary::addFloat(const std::string keyName, const float keyVal, btDictKey * parent)
{
	m_DictionaryKeys[keyName] = new btDictKey(keyName, (void*)(&keyVal), btDictKey::KT_FLOAT, parent);;
}

const float btDictionary::getFloat(const std::string keyName) const
{
	btIntrusivePtr<btDictKey> key = getKey(keyName);
	//check if key are a right type
	SDL_assert(key->getKeyType() != btDictKey::KT_FLOAT);

	//check key consistency
	if (!key.validate() || key->getKeyType() != btDictKey::KT_FLOAT)
		return 0.0f;

	return key->getFloat();
}

void btDictionary::addString(const std::string keyName, const std::string keyVal, btDictKey * parent)
{
	m_DictionaryKeys[keyName] = new btDictKey(keyName, (void*)keyVal.data(), btDictKey::KT_SHORT, parent);
}

const char * btDictionary::getString(const std::string keyName) const
{
	btIntrusivePtr<btDictKey> key = getKey(keyName);
	//check if key are a right type
	SDL_assert(key->getKeyType() != btDictKey::KT_STRING);

	//check key consistency
	if (!key.validate() || key->getKeyType() != btDictKey::KT_STRING)
		return "";

	return key->getString();
}

const btIntrusivePtr<btDictKey> btDictionary::getKey(const std::string keyName) const
{
	std::map<std::string, btIntrusivePtr<btDictKey>>::const_iterator it;
	it = m_DictionaryKeys.find(keyName);

	if (it != m_DictionaryKeys.end())
		return it->second;
	
	return btIntrusivePtr<btDictKey>(NULL);
}

void btDictionary::writeKeys(btIntrusivePtr<char> key)
{
//	for (auto key : m_DictionaryKeys)
//		key.second->writeKey(key);
}

void btDictionary::writeKeys(btIntrusivePtr<btStream>& outbuff)
{
	for (auto key : m_DictionaryKeys)
		key.second->writeKey(outbuff);
}
