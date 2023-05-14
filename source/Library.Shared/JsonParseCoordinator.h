#pragma once

#include <memory>
#include "json/json.h"
#include "Vector.h"
#include "Scope.h"
#include <fstream>

namespace FieaGameEngine
{
	/// <summary>
	/// Forward Decleratoin of JsonParseHelper
	/// </summary>
	class JsonParseHelper;

	/// <summary>
	/// Coordinator for Json Parsing
	/// Calls Handlers to attempt to handle data
	/// </summary>
	class JsonParseCoordinator
	{
	public:
		/// <summary>
		/// Abstract Wrapper for storing parsed data
		/// </summary>
		class Wrapper : public FieaGameEngine::RTTI
		{
			RTTI_DECLARATIONS(Wrapper, RTTI);

			friend JsonParseCoordinator;

		public:
			/// <summary>
			/// Default Constructor
			/// </summary>
			Wrapper() = default;

			/// <summary>
			/// Virtual Destructor
			/// </summary>
			virtual ~Wrapper() = default;

			/// <summary>
			/// Virtual Constructor
			/// </summary>
			/// <returns>Creates new Copy of Wrapper</returns>
			virtual std::shared_ptr<Wrapper> Create() const = 0;

			/// <summary>
			/// Gets Pointer to stored JsonParseCoordinator
			/// </summary>
			/// <returns></returns>
			JsonParseCoordinator* GetJsonParseCoordinator();

			/// <summary>
			/// Increases Depth by 1
			/// </summary>
			void IncrementDepth();

			/// <summary>
			/// Decreases Depth by 1
			/// Removes Elements at Curretn Depth
			/// </summary>
			void DecrementDepth();			

			/// <summary>
			/// Coordinator this Wrapper belongs to
			/// </summary>
			JsonParseCoordinator *_coordinator = nullptr;

			/// <summary>
			/// Names of data members and their depth
			/// </summary>
			Vector<std::pair<size_t, std::string>> _names;
			
		private:
			/// <summary>
			/// Current Depth
			/// </summary>
			size_t _depth = 0;

			/// <summary>
			/// Sets ParseCoordinator of current Wrapper
			/// </summary>
			/// <param name="coordinator">Coordinator to Set</param>
			void SetJsonParseCoordinator(JsonParseCoordinator *coordinator);
		};

		/// <summary>
		/// Constructor for JsonParseCoordinator
		/// </summary>
		/// <param name="wrapper">Wrapper to fill</param>
		JsonParseCoordinator(std::shared_ptr<Wrapper> wrapper);

		~JsonParseCoordinator() = default;

		/// <summary>
		/// Clones current JsonParseCoordinator
		/// Recreates Helpers and Wrapper
		/// Owns Newly created Helpers and Wrapper
		/// </summary>
		/// <returns>Pointer to new JsonParseCoordinator</returns>
		JsonParseCoordinator* Clone() const;

		/// <summary>
		/// Adds helper to current ParseCoordinator
		/// </summary>
		/// <param name="helper">Helper to Add</param>
		void AddHelper(std::shared_ptr<JsonParseHelper> helper);

		/// <summary>
		/// Removes given Heleprs
		/// </summary>
		/// <param name="target">Helper to Remove</param>
		void Remove(std::shared_ptr<JsonParseHelper> target);

		/// <summary>
		/// Deserializes JSON String
		/// </summary>
		/// <param name="data">String to Deserialize</param>
		void DeserializeObject(const std::string &data);

		/// <summary>
		/// Deserializes from File
		/// </summary>
		/// <param name="file">File to Deserialize</param>
		void DeserializeObjectFromFile(const std::string &file);

		/// <summary>
		/// Deserializes from Istream
		/// </summary>
		/// <param name="stream">Istream to Deserialize from</param>
		void DeserializeObject(std::istream &stream);

		/// <summary>
		/// Sets Wrapper to given value
		/// </summary>
		/// <param name="wrapper">Wrapper to set to</param>
		void SetWrapper(std::shared_ptr<Wrapper> wrapper);

		/// <summary>
		/// Initializes all helpers
		/// </summary>
		void Initialize();

		/// <summary>
		/// Gets current Wrapper
		/// </summary>
		/// <returns>Wrapper for this Coordinator</returns>
		std::shared_ptr<Wrapper> GetWrapper() const;

	private:
		/// <summary>
		/// Parses current JSON Value
		/// </summary>
		/// <param name="value"></param>
		void ParseMembers(Json::Value value);

		/// <summary>
		/// Parses Json String Value Pair
		/// </summary>
		/// <param name="string">Name of Json Value</param>
		/// <param name="value">Json Value</param>
		/// <param name="isArray">True if Array</param>
		void Parse(const std::string& string, Json::Value value, bool isArray);


		/// <summary>
		/// Wrapper to Fill
		/// </summary>
		std::shared_ptr<Wrapper> _wrapper;

		/// <summary>
		/// Vector of Helpers
		/// </summary>
		Vector<std::shared_ptr<JsonParseHelper>> _helpers;

		/// <summary>
		/// Whether or not this is a Cloned or Original JSONParseCoordinator
		/// </summary>
		bool _cloned = false;
	};
}

