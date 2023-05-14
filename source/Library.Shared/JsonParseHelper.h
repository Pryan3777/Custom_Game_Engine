#pragma once

#include <memory>
#include "RTTI.h"
#include "json/json.h"
#include "JsonParseCoordinator.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Abstract class for Helpers for Parsing JSON
	/// </summary>
	class JsonParseHelper
	{

	public:
		/// <summary>
		/// Initialize any Data members for the given helper
		/// </summary>
		virtual void Initialize();

		/// <summary>
		/// Attempt to Handle given Key and Data to fit in Wrapper
		/// </summary>
		/// <param name="wrapper">Place to store Data after Parsing</param>
		/// <param name="key">Name of Json Element</param>
		/// <param name="value">Value of Json Element</param>
		/// <param name="isArray">True if Array</param>
		/// <returns>True if was parsed</returns>
		virtual bool StartHandler(std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper, const std::string& key, Json::Value& value, bool isArray = false, int index = 0) = 0;
		
		/// <summary>
		/// Ends Handling after StartHandler call
		/// </summary>
		/// <param name="wrapper">Place Data was stored at</param>
		/// <param name="key">Name of JSON Element</param>
		/// <returns>true always</returns>
		virtual bool EndHandler(std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper, bool isTable) = 0;
		
		/// <summary>
		/// Virtual Constructor for JsonIntegerParseHelper
		/// </summary>
		/// <returns>New JsonIntegerParseHelper</returns>
		virtual std::shared_ptr<JsonParseHelper> Create() const = 0;
	
	protected:
		/// <summary>
		/// Constructor
		/// </summary>
		JsonParseHelper() {};

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other"></param>
		JsonParseHelper(std::shared_ptr<JsonParseHelper> other) {};

		/// <summary>
		/// Destructor, Marked Virtual
		/// </summary>
		virtual ~JsonParseHelper() {};
	};
}