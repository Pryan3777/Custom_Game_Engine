#include "pch.h"
#include "Signature.h"

namespace FieaGameEngine
{

	Signature::Signature(std::string name, Datum::DatumTypes type, size_t size, size_t offset) :
		_name(name), _type(type), _size(size), _offset(offset)
	{
	}

	void Signature::Populate(Scope * s)
	{
		char* b = reinterpret_cast<char*>(s);
		b += _offset;

		switch (_type)
		{
		case Datum::DatumTypes::Integer :
			(*s)[_name].SetStorage(reinterpret_cast<int*>(b), _size);
			break;

		case Datum::DatumTypes::Float:
			(*s)[_name].SetStorage(reinterpret_cast<float*>(b), _size);
			break;

		case Datum::DatumTypes::String:
			(*s)[_name].SetStorage(reinterpret_cast<std::string*>(b), _size);
			break;

		case Datum::DatumTypes::Vector:
			(*s)[_name].SetStorage(reinterpret_cast<glm::vec4*>(b), _size);
			break;

		case Datum::DatumTypes::Matrix:
			(*s)[_name].SetStorage(reinterpret_cast<glm::mat4*>(b), _size);
			break;

		case Datum::DatumTypes::Pointer:
			(*s)[_name].SetStorage(reinterpret_cast<RTTI**>(b), _size);
			break;

		case Datum::DatumTypes::Table:
			(*s)[_name].SetType(Datum::DatumTypes::Table);
			break;
		}
		
	}
}