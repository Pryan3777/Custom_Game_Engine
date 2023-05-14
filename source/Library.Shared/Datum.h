#pragma once

#include <cstddef>
#include <string>
#include <glm/glm.hpp>
#include "RTTI.h"


namespace FieaGameEngine
{
	class Scope;

	/// <summary>
	/// Contains a Union of Common Types
	/// </summary>
	class Datum final
	{
		friend class Scope;
	public:
		/// <summary>
		/// Types Datum Supports
		/// </summary>
		enum class DatumTypes
		{
			Unknown,
			Integer,
			Float,
			String,
			Vector,
			Matrix,
			Pointer,
			Table
		};
	private:
		/// <summary>
		/// Types Datum Supports
		/// </summary>
		union DatumValues final
		{
			int* _intData;
			float* _floatData;
			std::string* _stringData;
			glm::vec4* _vec4Data;
			glm::mat4* _mat4Data;
			RTTI** _RTTIData;
			void* _vp;
			Scope** _tableData;
		};
		/// <summary>
		/// Sizes of Datum Types
		/// </summary>
		static constexpr size_t DatumSizes[8] =
			{0, 
			sizeof(int), 
			sizeof(float),
			sizeof(std::string),
			sizeof(glm::vec4),
			sizeof(glm::mat4),
			sizeof(RTTI*),
			sizeof(Scope*)};
	public:
		/// <summary>
		/// Defaut constructor for Datum
		/// </summary>
		Datum() = default;

		/// <summary>
		/// Copy Constructo for Datum
		/// </summary>
		/// <param name="other">Datum to Copy</param>
		Datum(const Datum& other);

		/// <summary>
		/// Move Constructor for Datum
		/// </summary>
		/// <param name="other">Datum to Take From</param>
		Datum(Datum&& other) noexcept;

		/// <summary>
		/// Assignment Operator for Datum
		/// </summary>
		/// <param name="other">Datum to Copy</param>
		/// <returns>Copied Datum</returns>
		Datum& operator=(const Datum& other);

		/// <summary>
		/// Move Assignment Operator for Datum
		/// </summary>
		/// <param name="other">Datum to Copy</param>
		/// <returns>Moved Datum</returns>
		Datum& operator=(Datum&& other) noexcept;
		
		~Datum();

		Datum& operator=(const int& other);
		Datum& operator=(const float& other);
		Datum& operator=(const std::string &other);
		Datum& operator=(const glm::vec4& other);
		Datum& operator=(const glm::mat4& other);
		Datum& operator=(RTTI* other);


		/// <summary>
		/// Gets Type of Datum
		/// </summary>
		/// <returns>Datum Type</returns>
		DatumTypes Type() const;

		/// <summary>
		/// Sets Datum Type
		/// </summary>
		/// <param name="index">Sets Datum Type</param>
		void SetType(DatumTypes type);

		/// <summary>
		/// Returns size of Datum
		/// </summary>
		size_t Size() const;

		/// <summary>
		/// Resizes Datum to given Size
		/// </summary>
		/// <param name="size">Size</param>
		void Resize(size_t size);

		/// <summary>
		/// Clears datum without Freeing
		/// </summary>
		void Clear();

		/// <summary>
		///  Sets to External storage
		/// </summary>
		/// <param name="data">Pointer to data</param>
		/// <param name="size">Size of data</param>
		void SetStorage(int* data, size_t size);

		/// <summary>
		///  Sets to External storage
		/// </summary>
		/// <param name="data">Pointer to data</param>
		/// <param name="size">Size of data</param>
		void SetStorage(float* data, size_t size);

		/// <summary>
		///  Sets to External storage
		/// </summary>
		/// <param name="data">Pointer to data</param>
		/// <param name="size">Size of data</param>
		void SetStorage(std::string* data, size_t size);

		/// <summary>
		///  Sets to External storage
		/// </summary>
		/// <param name="data">Pointer to data</param>
		/// <param name="size">Size of data</param>
		void SetStorage(glm::vec4* data, size_t size);

		/// <summary>
		///  Sets to External storage
		/// </summary>
		/// <param name="data">Pointer to data</param>
		/// <param name="size">Size of data</param>
		void SetStorage(glm::mat4* data, size_t size);

		/// <summary>
		///  Sets to External storage
		/// </summary>
		/// <param name="data">Pointer to data</param>
		/// <param name="size">Size of data</param>
		void SetStorage(RTTI** data, size_t size);

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const Datum& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const Datum& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const int& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const int& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const float& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const float& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const std::string& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const std::string& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const glm::vec4& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const glm::vec4& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const glm::mat4& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const glm::mat4& other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator==(const RTTI* other) const;

		/// <summary>
		/// checks if Datum is equal to other
		/// </summary>
		/// <param name="other">Value to compare to</param>
		/// <returns>If they are equal</returns>
		bool operator!=(const RTTI* other) const;

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(int& value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(float& value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(std::string& value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(glm::vec4& value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(glm::mat4& value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(RTTI* value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		void Set(Scope* value, size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		int& GetInt(size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		float& GetFloat(size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		std::string& GetString(size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		glm::vec4& GetVec(size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		glm::mat4& GetMat(size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		RTTI* GetRTTI(size_t index = 0);

		/// <summary>
		/// Sets value of Datum to index
		/// </summary>
		/// <param name="value">Value to set</param>
		/// <param name="index">Index to change</param>
		Scope* GetScope(size_t index = 0);

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const int& GetInt(size_t index = 0) const;

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const float& GetFloat(size_t index = 0) const;

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const std::string& GetString(size_t index = 0) const;

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const glm::vec4& GetVec(size_t index = 0) const;

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const glm::mat4& GetMat(size_t index = 0) const;

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const RTTI* GetRTTI(size_t index = 0) const;

		/// <summary>
		/// returns values at index
		/// </summary>
		/// <param name="index">Index to get Value from</param>
		/// <returns>Value found</returns>
		const Scope* GetScope(size_t index = 0) const;


		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(const int& target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(const float& target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(const std::string& target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(const glm::vec4& target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(const glm::mat4& target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(RTTI* target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PushBack(Scope* target);

		/// <summary>
		/// Adds Value to back of Datum
		/// </summary>
		/// <param name="target">value to push back</param>
		void PopBack();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		int& FrontInt();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const int& FrontInt() const;

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		float& FrontFloat();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const float& FrontFloat() const;

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		std::string& FrontString();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const std::string& FrontString() const;

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		glm::vec4& FrontVec();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const glm::vec4& FrontVec() const;

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		glm::mat4& FrontMat();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const glm::mat4& FrontMat() const;

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		RTTI* FrontRTTI();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const RTTI* FrontRTTI() const;

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		Scope* FrontScope();

		/// <summary>
		/// Gets value at Front
		/// </summary>
		/// <returns>Value found</returns>
		const Scope* FrontScope() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		int& BackInt();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const int& BackInt() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		float& BackFloat();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const float& BackFloat() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		std::string& BackString();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const std::string& BackString() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		glm::vec4& BackVec();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const glm::vec4& BackVec() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		glm::mat4& BackMat();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const glm::mat4& BackMat() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		RTTI* BackRTTI();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const RTTI* BackRTTI() const;

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		Scope* BackScope();

		/// <summary>
		/// Gets value at Back
		/// </summary>
		/// <returns>Value found</returns>
		const Scope* BackScope() const;
	
		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(int& target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(float& target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(std::string& target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(glm::vec4& target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(glm::mat4& target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(RTTI* target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool Remove(Scope* target);

		/// <summary>
		/// Finds and removes value
		/// </summary>
		/// <param name="target">Value to Find and Remove</param>
		/// <returns>Whether value was removed</returns>
		bool RemoveAt(size_t index);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(int& target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(float& target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(std::string& target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(glm::vec4& target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(glm::mat4& target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(RTTI* target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		size_t Find(Scope* target);

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(int& target) const;

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(float& target) const;

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(std::string& target) const;

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(glm::vec4& target) const;

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(glm::mat4& target) const;

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(RTTI* target) const;

		/// <summary>
		/// Finds and value
		/// </summary>
		/// <param name="target">Value to Find</param>
		/// <returns>Index of Value</returns>
		const size_t Find(const Scope* target) const;

		/// <summary>
		/// Paul's Code, hope it's good
		/// </summary>
		inline Scope& operator[](std::uint32_t index) { return *GetScope(index); }

		inline bool isExternal() const { return _isExternal; }

	private:
		void AssertInternal() const;

		void AssertType(Datum::DatumTypes t) const;

		void AssertSize(size_t s = 0) const;

		/// <summary>
		/// Data stored in Datum
		/// </summary>
		DatumValues _data {DatumValues()};

		/// <summary>
		/// Size of Datum
		/// </summary>
		std::size_t _size{ 0 };

		/// <summary>
		/// Capacity of Datum
		/// </summary>
		std::size_t _capacity{ 0 };

		/// <summary>
		/// Type of Datum
		/// </summary>
		DatumTypes _type{ DatumTypes::Unknown };

		/// <summary>
		/// Whether or not Data is stored externally
		/// </summary>
		bool _isExternal{ false };
	};
}
#include "Datum.inl"