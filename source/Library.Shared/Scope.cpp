#include "pch.h"
#include "Scope.h"
#include <stdexcept>
#include <cassert>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope);

	bool Scope::Equals(const RTTI* rhs) const
	{
		bool eq = false;
		if (rhs->As<Scope>() != nullptr && Size() == rhs->As<Scope>()->Size())
		{
			eq = true;
			HashMap<const std::string, Datum>::ConstIterator i = _data.begin();
			HashMap<const std::string, Datum>::ConstIterator j = rhs->As<Scope>()->_data.begin();
			while(i != _data.cend())
			{
				if (i->first != j->first || i->second != j->second)
				{
					eq = false;
					break;
				}
				++i;
				++j;
			}
		}

		return (eq);
	}

	Scope::Scope(size_t bins) :
		_index(Vector<std::pair<const std::string, Datum> *>::Vector()), _data(HashMap<const std::string, Datum>::HashMap(bins)), _bins(bins)
	{
	}
	Scope::Scope(const Scope& other) :
		_index(Vector<std::pair<const std::string, Datum>*>::Vector()), _data(HashMap<const std::string, Datum>::HashMap(other._bins)), _bins(other._bins)
	{
		_parent = nullptr;
		for (size_t i = 0; i < other._index.Size(); i++)
		{
			Datum& a = Append(other._index[i]->first);
			if (other._index[i]->second.Type() == Datum::DatumTypes::Table)
			{
				a = Datum();
				a.SetType(Datum::DatumTypes::Table);
				for (size_t j = 0; j < other._index[i]->second.Size(); ++j)
				{
					Scope* b = other._index[i]->second._data._tableData[j]->Clone();
					b->_parent = this;
					a.PushBack(b);
				}
			}
			else
			{
				a = other._index[i]->second;
			}
		}
	}
	Scope::Scope(Scope&& other) noexcept :
		_index(std::move(other._index)), _data(std::move(other._data)), _bins(other._bins)
	{
		for (size_t i = 0; i < Size(); i++)
		{
			if (_index[i]->second.Type() == Datum::DatumTypes::Table)
			{
				for (size_t j = 0; j < _index[i]->second.Size(); j++)
				{
					_index[i]->second.GetScope(j)->_parent = this;
				}
			}
		}
		other.Clear();
		if (other._parent != nullptr)
		{
			auto p = other.Orphan();
			delete(p);
		}
	}
	Scope& Scope::operator=(const Scope& other)
	{
		Clear();
		
		_parent = nullptr;
		for (size_t i = 0; i < other._index.Size(); i++)
		{
			Datum& a = Append(other._index[i]->first);
			if (other._index[i]->second.Type() == Datum::DatumTypes::Table)
			{
				a = Datum();
				a.SetType(Datum::DatumTypes::Table);
				for (size_t j = 0; j < other._index[i]->second.Size(); ++j)
				{
					Scope* b = other._index[i]->second._data._tableData[j]->Clone();
					b->_parent = this;
					a.PushBack(b);
				}
			}
			else
			{
				a = other._index[i]->second;
			}
		}

		return *this;
	}
	Scope& Scope::operator=(Scope&& other) noexcept
	{
		Clear();
		Orphan();

		_index = std::move(other._index);
		_data = std::move(other._data);
		_bins = other._bins;

		for (size_t i = 0; i < Size(); i++)
		{
			if (_index[i]->second.Type() == Datum::DatumTypes::Table)
			{
				for (size_t j = 0; j < _index[i]->second.Size(); j++)
				{
					_index[i]->second.GetScope(j)->_parent = this;
				}
			}
		}
		other.Clear();
		if (other._parent != nullptr)
		{
			auto p = other.Orphan();
			delete(p);
		}

		return *this;
	}
	Scope::~Scope()
	{
		Orphan();
		Clear();
	}
	size_t Scope::Size() const
	{
		return _index.Size();
	}
	bool Scope::IsEmpty()
	{
		return Size() == 0;
	}
	Datum* Scope::Find(const std::string target)
	{
		HashMap<const std::string, Datum>::Iterator i = _data.Find(target);
		return i == _data.end() ? nullptr : &i->second;
	}
	const Datum* Scope::Find(const std::string target) const
	{
		HashMap<const std::string, Datum>::ConstIterator i(_data.Find(target));
		return i == _data.end() ? nullptr : &i->second;
	}
	Datum* Scope::Search(const std::string target, Scope** scopeOut)
	{
		return SearchR(target, scopeOut, this);
	}
	Datum* Scope::SearchR(const std::string target, Scope** scopeOut, Scope* scope)
	{
		if (scope == nullptr)
		{
			return nullptr;
		}
		Datum * t = (scope)->Find(target);
		if (t != nullptr)
		{
			if (scopeOut != nullptr)
			{
				*scopeOut = scope;
			}
			return t;
		}
		return SearchR(target, scopeOut, ((scope)->_parent));
	}
	Datum& Scope::Append(const std::string target)
	{
		Datum* t = Find(target);
		if (t == nullptr)
		{
			std::pair<const std::string, Datum> p = std::pair<const std::string, Datum>(target, Datum());
			HashMap<const std::string, Datum>::Iterator i = _data.Insert(p);
			if (_data.Size() > _index.Size())
			{
				_index.PushBack(&*(i));
			}
			t = &(i->second);
		}
		return *t;
	}
	Scope& Scope::AppendScope(const std::string target)
	{
		Datum& d = Append(target);
		assert(d.Type() == Datum::DatumTypes::Unknown || d.Type() == Datum::DatumTypes::Table);
		d.SetType(Datum::DatumTypes::Table);
		Scope* s = new Scope;
		d.PushBack(s);
		s->_parent = this;
		return *s;
	}
	void Scope::Adopt(Scope& child, std::string name)
	{
		if (child._parent != nullptr)
		{
			child.Orphan();
		}

		Datum& d = Append(name);
		assert(d.Type() == Datum::DatumTypes::Unknown || d.Type() == Datum::DatumTypes::Table);
		d.SetType(Datum::DatumTypes::Table);
		d.PushBack(&child);
		child._parent = this;
	}
	Scope* Scope::GetParent()
	{
		return _parent;
	}
	Datum& Scope::operator[](const std::string target)
	{
		return Append(target);
	}
	Datum& Scope::operator[](const size_t target)
	{
		assert(target < _index.Size());
		return _index[target]->second;
	}
	bool Scope::operator==(const Scope& other) const
	{
		bool ret = false;
		if (_index.Size() == other._index.Size() && _parent == other._parent)
		{
			ret = true;
			for (size_t i = 0; i < _index.Size(); ++i)
			{
				auto a = _index[i]->first;
				auto b = other._index[i]->first;
				a;
				b;
				auto c = _index[i]->second;
				auto d = other._index[i]->second;
				c;
				d;
				if (_index[i]->first != other._index[i]->first || _index[i]->second != other._index[i]->second)
				{
					ret = false;
					break;
				}
			}
		}
		return ret;
	}
	bool Scope::operator!=(const Scope& other) const
	{
		return !operator==(other);
	}
	std::pair<Datum*, size_t> Scope::FindContainedScope(const Scope& target)
	{
		if (target._parent != this)
		{
			return std::pair<Datum*, size_t>(nullptr, 0);
		}
		while (true)
		{
			for (size_t i = 0; i < _index.Size(); i++)
			{
				if (_index[i]->second.Type() == Datum::DatumTypes::Table)
				{
					for (size_t j = 0; j < _index[i]->second.Size(); ++j)
					{
						if (_index[i]->second.GetScope(j) == &target)
						{
							return std::pair<Datum*, size_t>(&_index[i]->second, j);
						}
					}
				}
			}
		}
		return std::pair<Datum*, size_t>(nullptr, 0);
	}
	void Scope::Clear()
	{
		while (Size() > 0)
		{
			if (_index[0]->second.Type() == Datum::DatumTypes::Table)
			{
				while (_index[0]->second.Size() > 0)
				{
					Scope* child = _index[0]->second.GetScope(0);
					child->Orphan();
					delete(child);
				}
			}
			_index[0]->second.Clear();
			_data.Remove(_index[0]->first);
			_index.RemoveAt(0);
		}
		_data.Clear();
		_index.Clear();
	}
	Scope* Scope::Orphan()
	{
		if (_parent != nullptr)
		{
			auto[a, b] = _parent->FindContainedScope(*this);
			a->RemoveAt(b);
		}
		_parent = nullptr;
		return this;
	}
	Scope* Scope::Clone()
	{
		return new Scope(*this);
	}
}
