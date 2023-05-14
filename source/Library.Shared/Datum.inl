#include "Datum.h"
#include <stdexcept>
#include <cassert>

#include "Scope.h"


namespace FieaGameEngine
{
	inline Datum::Datum(const Datum& other) :
		_type(other._type), _isExternal(other._isExternal)
	{
		if (_isExternal)
		{
			_size = other._size;
			_data._vp = other._data._vp;
			_capacity = other._capacity;
		}
		else
		{
			Resize(other._size);
			if (_type == Datum::DatumTypes::String)
			{
				for (size_t i = 0; i < _size; i++)
				{
					_data._stringData[i] = other._data._stringData[i];
				}
			}
			else
			{
				memcpy(_data._vp, other._data._vp, _size * DatumSizes[static_cast<int>(_type)]);
			}
		}
	}

	inline Datum::Datum(Datum&& other) noexcept :
		_type(other._type), _size(other._size), _capacity(other._capacity), _data(std::move(other._data)), _isExternal(other._isExternal)
	{
		other._isExternal = false;
		other._size = 0;
		other._capacity = 0;
		other._data = DatumValues();
	}

	inline Datum& Datum::operator=(const Datum& other)
	{
		Clear();

		_type = other._type;
		_isExternal = other._isExternal;
		if (_isExternal)
		{
			_size = other._size;
			_data._vp = other._data._vp;
			_capacity = other._capacity;
		}
		else
		{
			Resize(other._size);
			if (_type == Datum::DatumTypes::String)
			{
				for (size_t i = 0; i < _size; i++)
				{
					_data._stringData[i] = other._data._stringData[i];
				}
			}
			else
			{
				memcpy(_data._vp, other._data._vp, _size * DatumSizes[static_cast<int>(_type)]);
			}
		}

		return *this;
	}

	inline Datum& Datum::operator=(Datum&& other) noexcept
	{
		Clear();
		_type = other._type;
		_size = other._size;
		_capacity = other._capacity;
		_data = std::move(other._data);
		_isExternal = other._isExternal;

		other._isExternal = false;
		other._size = 0;
		other._capacity = 0;
		other._data = DatumValues();

		return *this;
	}

	inline Datum::~Datum()
	{
		if (_data._vp != nullptr)
		{
			if (_isExternal)
			{
				_data._vp = nullptr;
			}
			else
			{
				Resize(0);
			}
		}
	}
	inline Datum& Datum::operator=(const int& other)
	{
		Clear();

		_type = DatumTypes::Integer;
		PushBack(other);

		return *this;
	}
	inline Datum& Datum::operator=(const float& other)
	{
		Clear();

		_type = DatumTypes::Float;
		PushBack(other);

		return *this;
	}
	inline Datum& Datum::operator=(const std::string& other)
	{
		Clear();

		_type = DatumTypes::String;
		PushBack(other);

		return *this;
	}
	inline Datum& Datum::operator=(const glm::vec4& other)
	{
		Clear();

		_type = DatumTypes::Vector;
		PushBack(other);

		return *this;
	}
	inline Datum& Datum::operator=(const glm::mat4& other)
	{
		Clear();

		_type = DatumTypes::Matrix;
		PushBack(other);

		return *this;
	}
	inline Datum& Datum::operator=(RTTI* other)
	{
		Clear();

		_type = DatumTypes::Pointer;
		PushBack(other);

		return *this;
	}
	inline typename Datum::DatumTypes Datum::Type() const
	{
		return _type;
	}
	inline void Datum::SetType(DatumTypes type)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = type;
		}
	}
	inline size_t Datum::Size() const
	{
		return _size;
	}
	inline void Datum::Resize(size_t size)
	{
		AssertInternal();
		if (_type == DatumTypes::Unknown)
		{
			if (size == 0)
			{
				return;
			}
			else
			{
				throw std::runtime_error("Attempted Resize on Unset Type");
			}
		}
		while (_size > size)
		{
			PopBack();
		}
		if (size == 0)
		{
			free(_data._vp);
		}
		else
		{
			void* a = reinterpret_cast<void*>(realloc(_data._vp, size * DatumSizes[static_cast<int>(_type)]));
			assert(a != nullptr);
			_data._vp = a;
		}
		_capacity = size;
		if (_size < _capacity)
		{
			switch (_type)
			{
			case DatumTypes::String:
				while (_size < _capacity)
				{
					std::string* ptr = new(&_data._stringData[_size]) std::string("");
					ptr;
					++_size;
				}
				break;
			case DatumTypes::Pointer:
				while (_size < _capacity)
				{
					_data._RTTIData[_size] = nullptr;
					++_size;
				}
				break;
			case DatumTypes::Table:
				while (_size < _capacity)
				{
					_data._tableData[_size] = nullptr;
					++_size;
				}
				break;
			case DatumTypes::Integer:
				while (_size < _capacity)
				{
					PushBack(int(0));
				}
				break;
			case DatumTypes::Float:
				while (_size < _capacity)
				{
					PushBack(float(0.0f));
				}
				break;
			case DatumTypes::Vector:
				while (_size < _capacity)
				{
					PushBack(glm::vec4(0, 0, 0, 0));
				}
				break;
			case DatumTypes::Matrix:
				while (_size < _capacity)
				{
					PushBack(glm::mat4(0));
				}
				break;
			}
		}
		_size = _capacity;
	}
	inline void Datum::Clear()
	{
		if (_isExternal)
		{
			_isExternal = false;
			_data._vp = nullptr;
			_size = 0;
			_capacity = 0;
		}
		else
		{
			while (_size != 0)
			{
				PopBack();
			}
		}
	}
	inline void Datum::SetStorage(int* data, size_t size)
	{
		if (_type != DatumTypes::Unknown && !_isExternal)
		{
			throw std::runtime_error("Attempt to SetStorage with Type already set");
		}
		_data._vp = data;
		_size = size;
		_isExternal = true;
		_type = DatumTypes::Integer;

	}
	inline void Datum::SetStorage(float* data, size_t size)
	{
		if (_type != DatumTypes::Unknown && !_isExternal)
		{
			throw std::runtime_error("Attempt to SetStorage with Type already set");
		}
		_data._vp = data;
		_size = size;
		_isExternal = true;
		_type = DatumTypes::Float;
	}
	inline void Datum::SetStorage(std::string* data, size_t size)
	{
		if (_type != DatumTypes::Unknown && !_isExternal)
		{
			throw std::runtime_error("Attempt to SetStorage with Type already set");
		}
		_data._vp = data;
		_size = size;
		_isExternal = true;
		_type = DatumTypes::String;
	}
	inline void Datum::SetStorage(glm::vec4* data, size_t size)
	{
		if (_type != DatumTypes::Unknown && !_isExternal)
		{
			throw std::runtime_error("Attempt to SetStorage with Type already set");
		}
		_data._vp = data;
		_size = size;
		_isExternal = true;
		_type = DatumTypes::Vector;
	}
	inline void Datum::SetStorage(glm::mat4* data, size_t size)
	{
		if (_type != DatumTypes::Unknown && !_isExternal)
		{
			throw std::runtime_error("Attempt to SetStorage with Type already set");
		}
		_data._vp = data;
		_size = size;
		_isExternal = true;
		_type = DatumTypes::Matrix;
	}
	inline void Datum::SetStorage(RTTI** data, size_t size)
	{
		if (_type != DatumTypes::Unknown && !_isExternal)
		{
			throw std::runtime_error("Attempt to SetStorage with Type already set");
		}
		_data._vp = data;
		_size = size;
		_isExternal = true;
		_type = DatumTypes::Pointer;
	}
	inline bool Datum::operator==(const Datum& other) const
	{
		bool flag = false;
		if (_size == other._size && _type == other._type)
		{
			flag = true;
			switch (_type)
			{
			case DatumTypes::String:
				for (size_t i = 0; i < _size; i++)
				{
					if (_data._stringData[i] != other._data._stringData[i])
					{
						flag = false;
						break;
					}
				}
				break;
			case DatumTypes::Pointer:
				for (size_t i = 0; i < _size; i++)
				{
					if (_data._RTTIData[i] == nullptr || other._data._RTTIData[i] == nullptr)
					{
						if (_data._RTTIData[i] != other._data._RTTIData[i])
						{
							flag = false;
							break;
						}
					}
					else if (!_data._RTTIData[i]->Equals(other._data._RTTIData[i]))
					{
						flag = false;
						break;
					}
				}
				break;
			case DatumTypes::Table:
				for (size_t i = 0; i < _size; i++)
				{
					if (_data._tableData[i] == nullptr || other._data._tableData[i] == nullptr)
					{
						if (_data._tableData[i] != other._data._tableData[i])
						{
							flag = false;
							break;
						}
					}
					else if (!_data._RTTIData[i]->Equals(other._data._RTTIData[i]))
					{
						flag = false;
						break;
					}
				}
				break;
			default:
				flag = memcmp(_data._vp, other._data._vp, DatumSizes[static_cast<int>(_type)] * _size) == 0;
				break;
			}
		}
		return flag;
	}
	inline bool Datum::operator!=(const Datum& other) const
	{
		return !operator==(other);
	}
	inline bool Datum::operator==(const int& other) const
	{
		return _type == DatumTypes::Integer && _size > 0 && _data._intData[0] == other;
	}
	inline bool Datum::operator!=(const int& other) const
	{
		return !operator==(other);
	}
	inline bool Datum::operator==(const float& other) const
	{
		return _type == DatumTypes::Float && _size > 0 && _data._floatData[0] == other;
	}
	inline bool Datum::operator!=(const float& other) const
	{
		return !operator==(other);
	}
	inline bool Datum::operator==(const std::string& other) const
	{
		return _type == DatumTypes::String && _size > 0 && _data._stringData[0] == other;
	}
	inline bool Datum::operator!=(const std::string& other) const
	{
		return !operator==(other);
	}
	inline bool Datum::operator==(const glm::vec4& other) const
	{
		return _type == DatumTypes::Vector && _size > 0 && _data._vec4Data[0] == other;
	}
	inline bool Datum::operator!=(const glm::vec4& other) const
	{
		return !operator==(other);
	}
	inline bool Datum::operator==(const glm::mat4& other) const
	{
		return _type == DatumTypes::Matrix && _size > 0 && _data._mat4Data[0] == other;
	}
	inline bool Datum::operator!=(const glm::mat4& other) const
	{
		return !operator==(other);
	}
	inline bool Datum::operator==(const RTTI* other) const
	{
		if (other == nullptr)
		{
			return false;
		}
		return _type == DatumTypes::Pointer && _size > 0 && _data._RTTIData[0]->Equals(other);
	}
	inline bool Datum::operator!=(const RTTI* other) const
	{
		return !operator==(other);
	}

	inline void Datum::Set(int& value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::Integer);
		_data._intData[index] = value;
	}

	inline void Datum::Set(float& value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::Float);
		_data._floatData[index] = value;
	}

	inline void Datum::Set(std::string& value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::String);
		_data._stringData[index] = value;
	}

	inline void Datum::Set(glm::vec4& value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::Vector);
		_data._vec4Data[index] = value;
	}

	inline void Datum::Set(glm::mat4& value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::Matrix);
		_data._mat4Data[index] = value;
	}

	inline void Datum::Set(RTTI* value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::Pointer);
		_data._RTTIData[index] = value;
	}

	inline void Datum::Set(Scope* value, size_t index)
	{
		//AssertInternal();
		AssertSize(index);
		AssertType(DatumTypes::Table);
		_data._tableData[index] = value;
	}

	inline int& Datum::GetInt(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::Integer);
		return _data._intData[index];
	}

	inline float& Datum::GetFloat(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::Float);
		return _data._floatData[index];
	}

	inline std::string& Datum::GetString(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::String);
		return _data._stringData[index];
	}

	inline glm::vec4& Datum::GetVec(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::Vector);
		return _data._vec4Data[index];
	}

	inline glm::mat4& Datum::GetMat(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::Matrix);
		return _data._mat4Data[index];
	}

	inline RTTI* Datum::GetRTTI(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::Pointer);
		return _data._RTTIData[index];
	}

	inline Scope* Datum::GetScope(size_t index)
	{
		AssertSize(index);
		AssertType(DatumTypes::Table);
		return _data._tableData[index];
	}

	inline const int& Datum::GetInt(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::Integer);
		return _data._intData[index];
	}

	inline const float& Datum::GetFloat(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::Float);
		return _data._floatData[index];
	}

	inline const std::string& Datum::GetString(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::String);
		return _data._stringData[index];
	}

	inline const glm::vec4& Datum::GetVec(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::Vector);
		return _data._vec4Data[index];
	}

	inline const glm::mat4& Datum::GetMat(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::Matrix);
		return _data._mat4Data[index];
	}

	inline const RTTI* Datum::GetRTTI(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::Pointer);
		return _data._RTTIData[index];
	}

	inline const Scope* Datum::GetScope(size_t index) const
	{
		AssertSize(index);
		AssertType(DatumTypes::Table);
		return _data._tableData[index];
	}

	inline void Datum::PushBack(const int& target)
	{
		AssertInternal();
		AssertType(DatumTypes::Integer);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._intData[_size] = target;
		++_size;
	}

	inline void Datum::PushBack(const float& target)
	{
		AssertInternal();
		AssertType(DatumTypes::Float);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._floatData[_size] = target;
		++_size;
	}

	inline void Datum::PushBack(const std::string& target)
	{
		AssertInternal();
		AssertType(DatumTypes::String);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._stringData[_size] = target;
		++_size;
	}

	inline void Datum::PushBack(const glm::vec4& target)
	{
		AssertInternal();
		AssertType(DatumTypes::Vector);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._vec4Data[_size] = target;
		++_size;
	}

	inline void Datum::PushBack(const glm::mat4& target)
	{
		AssertInternal();
		AssertType(DatumTypes::Matrix);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._mat4Data[_size] = target;
		++_size;
	}

	inline void Datum::PushBack(RTTI* target)
	{
		AssertInternal();
		AssertType(DatumTypes::Pointer);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._RTTIData[_size] = target;
		++_size;
	}

	inline void Datum::PushBack(Scope* target)
	{
		AssertInternal();
		AssertType(DatumTypes::Table);
		if (_size == _capacity)
		{
			Resize(_size + 1);
			_size--;
		}
		_data._tableData[_size] = target;
		++_size;
	}



	inline void Datum::PopBack()
	{
		AssertInternal();
		if (_size > 0 && _type != DatumTypes::Unknown)
		{
			if (_type == DatumTypes::String)
			{
				_data._stringData[_size - 1].~basic_string();
			}
			--_size;
		}
	}

	inline int& Datum::FrontInt()
	{
		return GetInt();
	}

	inline const int& Datum::FrontInt() const
	{
		return GetInt();
	}

	inline float& Datum::FrontFloat()
	{
		return GetFloat();
	}

	inline const float& Datum::FrontFloat() const
	{
		return GetFloat();
	}

	inline std::string& Datum::FrontString()
	{
		return GetString();
	}

	inline const std::string& Datum::FrontString() const
	{
		return GetString();
	}

	inline glm::vec4& Datum::FrontVec()
	{
		return GetVec();
	}

	inline const glm::vec4& Datum::FrontVec() const
	{
		return GetVec();
	}

	inline glm::mat4& Datum::FrontMat()
	{
		return GetMat();
	}

	inline const glm::mat4& Datum::FrontMat() const
	{
		return GetMat();
	}

	inline RTTI* Datum::FrontRTTI()
	{
		return GetRTTI();
	}

	inline const RTTI* Datum::FrontRTTI() const
	{
		return GetRTTI();
	}

	inline Scope* Datum::FrontScope()
	{
		return GetScope();
	}

	inline const Scope* Datum::FrontScope() const
	{
		return GetScope();
	}

	inline int& Datum::BackInt()
	{
		return GetInt(Size() - 1);
	}

	inline const int& Datum::BackInt() const
	{
		return GetInt(Size() - 1);
	}

	inline float& Datum::BackFloat()
	{
		return GetFloat(Size() - 1);
	}

	inline const float& Datum::BackFloat() const
	{
		return GetFloat(Size() - 1);
	}

	inline std::string& Datum::BackString()
	{
		return GetString(Size() - 1);
	}

	inline const std::string& Datum::BackString() const
	{
		return GetString(Size() - 1);
	}

	inline glm::vec4& Datum::BackVec()
	{
		return GetVec(Size() - 1);
	}

	inline const glm::vec4& Datum::BackVec() const
	{
		return GetVec(Size() - 1);
	}

	inline glm::mat4& Datum::BackMat()
	{
		return GetMat(Size() - 1);
	}

	inline const glm::mat4& Datum::BackMat() const
	{
		return GetMat(Size() - 1);
	}

	inline RTTI* Datum::BackRTTI()
	{
		return GetRTTI(Size() - 1);
	}

	inline const RTTI* Datum::BackRTTI() const
	{
		return GetRTTI(Size() - 1);
	}

	inline Scope* Datum::BackScope()
	{
		return GetScope(Size() - 1);
	}

	inline const Scope* Datum::BackScope() const
	{
		return GetScope(Size() - 1);
	}

	inline bool Datum::Remove(int& target)
	{
		AssertInternal();
		if (_type == DatumTypes::Integer)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::Remove(float& target)
	{
		AssertInternal();
		if (_type == DatumTypes::Float)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::Remove(std::string& target)
	{
		AssertInternal();
		if (_type == DatumTypes::String)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::Remove(glm::vec4& target)
	{
		AssertInternal();
		if (_type == DatumTypes::Vector)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::Remove(glm::mat4& target)
	{
		AssertInternal();
		if (_type == DatumTypes::Matrix)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::Remove(RTTI* target)
	{
		AssertInternal();
		if (_type == DatumTypes::Pointer)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::Remove(Scope* target)
	{
		AssertInternal();
		if (_type == DatumTypes::Table)
		{
			auto a = Find(target);
			if (a < _size)
			{
				return RemoveAt(a);
			}
		}
		return false;
	}

	inline bool Datum::RemoveAt(size_t index)
	{
		AssertInternal();
		AssertSize(index);
		if (index < _size - 1)
		{
			switch (_type)
			{
			case DatumTypes::String:
				_data._stringData[index].~basic_string();
				memmove(_data._stringData + index, _data._stringData + index + 1, sizeof(std::string) * (_size - index - 1));
				break;

			case DatumTypes::Vector:
				memmove(_data._vec4Data + index, _data._vec4Data + index + 1, sizeof(glm::vec4) * (_size - index - 1));
				break;

			case DatumTypes::Matrix:
				memmove(_data._mat4Data + index, _data._mat4Data + index + 1, sizeof(glm::mat4) * (_size - index - 1));
				break;

			case DatumTypes::Pointer:
				memmove(_data._RTTIData + index, _data._RTTIData + index + 1, sizeof(void*) * (_size - index - 1));
				break;

			case DatumTypes::Table:
				memmove(_data._tableData + index, _data._tableData + index + 1, sizeof(void*) * (_size - index - 1));
				break;

			default:
				memmove(_data._intData + index, _data._intData + index + 1, sizeof(int) * (_size - index - 1));
			}

			--_size;
		}
		else
		{
			PopBack();
		}
		return true;
	}

	inline size_t Datum::Find(int& target)
	{
		size_t index = Size();
		if (_type == DatumTypes::Integer)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._intData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline size_t Datum::Find(float& target)
	{
		size_t index = Size();
		if (_type == DatumTypes::Float)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._floatData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline size_t Datum::Find(std::string& target)
	{
		size_t index = Size();
		if (_type == DatumTypes::String)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._stringData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline size_t Datum::Find(glm::vec4& target)
	{
		size_t index = Size();
		if (_type == DatumTypes::Vector)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._vec4Data[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline size_t Datum::Find(glm::mat4& target)
	{
		size_t index = Size();
		if (_type == DatumTypes::Matrix)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._mat4Data[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline size_t Datum::Find(RTTI* target)
	{
		size_t index = Size();
		if (_type == DatumTypes::Pointer)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._RTTIData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline size_t Datum::Find(Scope* target)
	{
		size_t index = Size();
		if (_type == DatumTypes::Table)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._tableData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(int& target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::Integer)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._intData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(float& target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::Float)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._floatData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(std::string& target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::String)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._stringData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(glm::vec4& target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::Vector)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._vec4Data[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(glm::mat4& target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::Matrix)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._mat4Data[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(RTTI* target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::Pointer)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._RTTIData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline const size_t Datum::Find(const Scope* target) const
	{
		size_t index = Size();
		if (_type == DatumTypes::Table)
		{
			for (index = 0; index < Size(); index++)
			{
				if (_data._tableData[index] == target)
				{
					break;
				}
			}
		}
		return index;
	}

	inline void Datum::AssertInternal() const
	{
		if (_isExternal)
		{
			throw std::runtime_error("Attempt to Mutate External data");
		}
	}

	inline void Datum::AssertType(Datum::DatumTypes t) const
	{
		if (Type() != t)
		{
			throw std::runtime_error("Incorrect Type");
		}
	}

	inline void Datum::AssertSize(size_t s) const
	{
		if (s >= Size())
		{
			throw std::runtime_error("Attempt to Access out of Range");
		}
	}


}