//#pragma once
//
//#include "Factory.h"
//#include "Scope.h"
//
//#include "AttributedFoo.h"
//
//using namespace FieaGameEngine;
//
//namespace UnitTests
//{
//	class AttributedFooFactory : public FieaGameEngine::Factory<FieaGameEngine::Scope>
//	{
//		virtual FieaGameEngine::Scope* CreateProduct() override { return new AttributedFoo; };
//		virtual const std::string ClassName() const override { return "AttributedFoo"; };
//	};
//}