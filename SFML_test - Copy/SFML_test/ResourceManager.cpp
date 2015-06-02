#include "ResourceManager.hpp"

template <typename Type>
ResourceManager<Type>::ResourceManager<Type>()
{
	
}

template <typename Type> ResourceManager<Type>::~ResourceManager()
{
	
}

//template <class Type> ResourceManager<Type>::ResourceManager()
//{
//	_error = Error::None;
//
//	_resourceList = new std::vector<Type>();
//}

template <typename Type> bool ResourceManager<Type>::addReference(const std::string key, const Type *reference)
{
	return true;
}

template <typename Type> void ResourceManager<Type>::removeAllReferences()
{
	_resourceList.clear();
}

template <typename Type> bool ResourceManager<Type>::changeReference(const std::string key, const Type *newReference)
{

}

template <typename Type> const Type *ResourceManager<Type>::getResource(const std::string key)
{
	//	Search through _resourceList to see if there's a matching key
	for (unsigned i = 0; i < _resourceList.size(); i++)
	{
		if (_resourceList[i].key.compare(_key) == 0) return _resourceList[i].reference;
	}

	_error = Error::KeyMissing;
	return 0;
}