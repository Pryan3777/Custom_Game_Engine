#include "pch.h"
#include "Attributed.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed);


	Attributed::Attributed(size_t type)
	{
		Populate(type);
	}

	Attributed::Attributed(const Attributed& other) :
		Scope(other)
	{
		Populate(other.TypeIdInstance());
	}

	Attributed::Attributed(Attributed&& other) noexcept :
		Scope(std::move(other))
	{
		Populate(other.TypeIdInstance());
	}

	Attributed& Attributed::operator=(const Attributed& other)
	{
		Scope::operator=(other);
		Populate(other.TypeIdClass());
		return *this;
	}

	Attributed& Attributed::operator=(Attributed&& other) noexcept
	{
		Scope::operator=(std::move(other));
		Populate(other.TypeIdClass());
		return *this;
	}

	bool Attributed::IsAttribute(std::string target)
	{
		return Find(target) != nullptr;
	}

	bool Attributed::IsPrescribedAttribute(std::string target)
	{
		return IsAttribute(target) && FindIndex(target) < _lastPrescribed;
	}

	bool Attributed::IsAuxiliaryAttribute(std::string target)
	{
		return IsAttribute(target) && FindIndex(target) >= _lastPrescribed;
	}

	std::pair<size_t, size_t> Attributed::Attributes()
	{
		return std::pair<size_t, size_t>(0, _index.Size());
	}

	std::pair<size_t, size_t> Attributed::PrescribedAttributes()
	{
		return std::pair<size_t, size_t>(0, _lastPrescribed);
	}

	std::pair<size_t, size_t> Attributed::AuxiliaryAttributes()
	{
		return std::pair<size_t, size_t>(_lastPrescribed, _index.Size());
	}

	void Attributed::Populate(size_t type)
	{
		operator[]("this") = this;
		TypeManager* t = TypeManager::Instance();
		auto s = t->GetSignaturesForTypeId(type);
		auto si = s.begin();
		auto se = s.end();
		for (si; si != se; ++si)
		{
			si->Populate(this);
			++_lastPrescribed;
		}
	}

	FieaGameEngine::Vector<FieaGameEngine::Signature> Attributed::Signatures()
	{
		FieaGameEngine::Vector<FieaGameEngine::Signature> v;
		return v;
	}
}
