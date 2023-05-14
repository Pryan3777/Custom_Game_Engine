#pragma once

#include <functional>
#include <sstream>
#include <glm/glm.hpp>
#include "JsonParseCoordinator.h"
#include "JsonParseHelper.h"

namespace FieaGameEngine
{
	/// <summary>
	/// General Parser for Datum Types
	/// </summary>
	class JsonTableParseHelper : public JsonParseHelper
	{
	public:
		/// <summary>
		/// Wrapper Holding a Root Scope an Populating it
		/// </summary>
		class Wrapper : public JsonParseCoordinator::Wrapper
		{
			RTTI_DECLARATIONS(Wrapper, JsonParseCoordinator::Wrapper);

		public:
			/// <summary>
			/// Creates Wrapper for TableParser
			/// </summary>
			JsonTableParseHelper::Wrapper();


			/// <summary>
			/// Creates a Table Wrapper
			/// </summary>
			/// <returns>Shared Ptr to Table Wrapper</returns>
			std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> Create() const override;
			
			/// <summary>
			/// Stack for holding Scopes
			/// </summary>
			std::stack<Scope*, Vector<Scope*>> _stack;

			/// <summary>
			/// 
			/// </summary>
			std::shared_ptr<Scope> _root;

		
			/// <summary>
			/// Function Table for Dealing with a Data Type based on String
			/// </summary>
			const HashMap<const std::string, void(*)(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index)> _handleTable{ 1, {{"Integer", Integer}, {"Float", Float}, {"String", String}, {"Vector", Vector}, {"Matrix", Matrix}, {"Table", Table}}};
		private:
			/// <summary>
			/// Parses Int
			/// </summary>
			/// <param name="wrapper">Wrapper To Store to</param>
			/// <param name="string">Name of Item to Add</param>
			/// <param name="value">Item to Parse</param>
			/// <param name="isArray">True if array</param>
			/// <param name="index">Index if array</param>
			static void Integer(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index);
			
			/// <summary>
			/// Parses Float
			/// </summary>
			/// <param name="wrapper">Wrapper To Store to</param>
			/// <param name="string">Name of Item to Add</param>
			/// <param name="value">Item to Parse</param>
			/// <param name="isArray">True if array</param>
			/// <param name="index">Index if array</param>
			static void Float(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index);
			
			/// <summary>
			/// Parses String
			/// </summary>
			/// <param name="wrapper">Wrapper To Store to</param>
			/// <param name="string">Name of Item to Add</param>
			/// <param name="value">Item to Parse</param>
			/// <param name="isArray">True if array</param>
			/// <param name="index">Index if array</param>
			static void String(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index);
			
			/// <summary>
			/// Parses Vector
			/// </summary>
			/// <param name="wrapper">Wrapper To Store to</param>
			/// <param name="string">Name of Item to Add</param>
			/// <param name="value">Item to Parse</param>
			/// <param name="isArray">True if array</param>
			/// <param name="index">Index if array</param>
			static void Vector(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index);
			
			/// <summary>
			/// Parses Matrix
			/// </summary>
			/// <param name="wrapper">Wrapper To Store to</param>
			/// <param name="string">Name of Item to Add</param>
			/// <param name="value">Item to Parse</param>
			/// <param name="isArray">True if array</param>
			/// <param name="index">Index if array</param>
			static void Matrix(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index);
			
			/// <summary>
			/// Parses Table
			/// </summary>
			/// <param name="wrapper">Wrapper To Store to</param>
			/// <param name="string">Name of Item to Add</param>
			/// <param name="value">Item to Parse</param>
			/// <param name="isArray">True if array</param>
			/// <param name="index">Index if array</param>
			static void Table(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value value, bool isArray, int index);


			/// <summary>
			/// Parses a Float from the Front of a String
			/// </summary>
			/// <param name="string">String to Parse</param>
			/// <returns>Float Parsed</returns>
			static float FloatParse(std::string& string);

			/// <summary>
			/// Parses Vector from Front of String
			/// </summary>
			/// <param name="string">String to Parse</param>
			/// <returns>Vec4 Parsed</returns>
			static glm::vec4 VecParse(std::string& string);

			/// <summary>
			/// Parses Matrix from Front of String
			/// </summary>
			/// <param name="string">String to Parse</param>
			/// <returns>Mat4 Prased</returns>
			static glm::mat4 MatParse(std::string& string);
		};

		/// <summary>
		/// Parses a Given Object
		/// </summary>
		/// <param name="wrapper">Wrapper To Store to</param>
		/// <param name="key">Name of Item to Add</param>
		/// <param name="value">Item to Parse</param>
		/// <param name="isArray">True if array</param>
		/// <param name="index">Index if array</param>
		/// <returns>True if Parsed, False if Unable</returns>
		virtual bool StartHandler(std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper, const std::string& key, Json::Value& value, bool isArray = false, int index = 0) override;
		
		/// <summary>
		/// Finishes Parsing a Given Object
		/// </summary>
		/// <param name="wrapper">Wrapper Vlaue is stored in</param>
		/// <param name="isTable">True if type is Table</param>
		/// <returns>True always</returns>
		virtual bool EndHandler(std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper, bool isTable) override;
		
		/// <summary>
		/// Virtual Constructor
		/// </summary>
		/// <returns>Shared Ptr to New Table Parser</returns>
		virtual std::shared_ptr<JsonParseHelper> Create() const override;


		/// <summary>
		/// Constructor Defaulted
		/// </summary>
		JsonTableParseHelper() = default;

		/// <summary>
		/// Copy Cosntructor 
		/// </summary>
		/// <param name="other"></param>
		JsonTableParseHelper(std::shared_ptr<JsonTableParseHelper> other) {};

		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~JsonTableParseHelper() {};
	};
}