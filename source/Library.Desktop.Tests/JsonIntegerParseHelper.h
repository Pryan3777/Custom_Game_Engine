//#pragma once
//
//#include "JsonParseCoordinator.h"
//#include "JsonParseHelper.h"
//
//
//namespace UnitTests
//{
//	/// <summary>
//	/// Implementation of JsonParseHelper
//	/// Handles Integer Data Types
//	/// Ignores Structure
//	/// </summary>
//	class JsonIntegerParseHelper : public FieaGameEngine::JsonParseHelper
//	{
//	public:
//		/// <summary>
//		/// Implementatoin of JsonParseCoordinator::Wrapper
//		/// Holds a Vector of Ints
//		/// </summary>
//		class Wrapper : public FieaGameEngine::JsonParseCoordinator::Wrapper
//		{
//			RTTI_DECLARATIONS(Wrapper, FieaGameEngine::JsonParseCoordinator::Wrapper);
//
//		public:
//			/// <summary>
//			/// Virtual Constructor
//			/// </summary>
//			/// <returns>Shared Pointer to new Wrapper</returns>
//			std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> Create() const override;
//
//			/// <summary>
//			/// Integer Vector
//			/// </summary>
//			FieaGameEngine::Vector<int> _data;
//		};
//
//		/// <summary>
//		/// Attempt to Handle given Key and Data to fit in Wrapper
//		/// </summary>
//		/// <param name="wrapper">Place to store Data after Parsing</param>
//		/// <param name="key">Name of Json Element</param>
//		/// <param name="value">Value of Json Element</param>
//		/// <param name="isArray">True if Array</param>
//		/// <returns>True if was parsed</returns>
//		virtual bool StartHandler(std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> wrapper, const std::string& key, Json::Value& value, bool isArray) override;
//		
//		/// <summary>
//		/// Ends Handling after StartHandler call
//		/// </summary>
//		/// <param name="wrapper">Place Data was stored at</param>
//		/// <param name="key">Name of JSON Element</param>
//		/// <returns>true always</returns>
//		virtual bool EndHandler(std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> wrapper, const std::string& key) override;
//		
//		/// <summary>
//		/// Virtual Constructor for JsonIntegerParseHelper
//		/// </summary>
//		/// <returns>New JsonIntegerParseHelper</returns>
//		virtual std::shared_ptr<FieaGameEngine::JsonParseHelper> Create() const override;
//	};
//}