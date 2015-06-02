#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

/*
	File:		ResourceManager.hpp
	Date:		31-01-2015
	Author:		Johnathon Forster

	Class:		ResourceManager
	Requires:	None
	Inherits:	None

	Description:
				Contains a list of pointers to objects coupled with an identifying string
*/

#include <vector>

template <typename Type> class ResourceManager
{
protected:
	struct KeyReferencePair
	{
		std::string key;
		Type *reference;
	};

	std::vector<KeyReferencePair> _resourceList;

public:
	enum Error { None, KeyTaken, KeyMissing };

protected:
	Error _error;

public:
	ResourceManager()
	{

	}

	~ResourceManager()
	{
		for (unsigned i = 0; i < _resourceList.size(); i++)
		{
			delete _resourceList[i].reference;
		}

		_resourceList.clear();
	}

	inline bool addReference(const std::string key, Type *reference)
	{
		//	Check it's not currently in use
		for (auto iter = _resourceList.begin(); iter != _resourceList.end(); iter++)
		{
			if (iter->key.compare(key) == 0)
			{
				_error = Error::KeyTaken;
				return false;
			}
		}

		KeyReferencePair krp;
		krp.key = key;
		krp.reference = reference;

		_resourceList.push_back(krp);
		return true;
	}
	
	inline bool removeReference(const std::string key)
	{
		for (auto iter = _resourceList.begin(); iter != resourceList.end(); iter++)
		{
			if (iter->key.compare(key) == 0)
			{
				_resourceList.erase(iter);
				return true;
			}
		}

		_error = Error::KeyMissing;
		return false;
	}

	inline void removeAllReferences()
	{
		for (unsigned i = 0; i < _resourceList.size(); i++)
		{
			delete _resourceList[i].reference;
		}

		_resourceList.clear();
	}
	
	inline bool changeReference(const std::string key, const Type *newReference)
	{
		for (auto iter = _resourceManager.begin(); iter != _resourceManager.end(); inter++)
		{
			if (iter->key.compare(key) == 0)
			{
				delete iter->reference;
				iter->reference = reference;
				return true;
			}
		}

		_error = Error::KeyMissing;
		return false;
	}

	inline Type *getResource(const std::string key)
	{
		//	Search through _resourceList to see if there's a matching key
		for (unsigned i = 0; i < _resourceList.size(); i++)
		{
			if (_resourceList[i].key.compare(key) == 0) return _resourceList[i].reference;
		}

		_error = Error::KeyMissing;
		return 0;
	}

	inline Error lastError() { return _error; }
};

#endif