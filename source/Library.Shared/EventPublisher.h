#pragma once
#include "RTTI.h"
#include "SList.h"
#include "EventSubscriber.h"
#include "GameTime.h"
#include <memory>

namespace FieaGameEngine
{
	/// <summary>
	/// Publishes an Event
	/// </summary>
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);

	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="subscribers">List of Subscribers</param>
		EventPublisher(SList<EventSubscriber*>& subscribers);

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Object to Copy From</param>
		EventPublisher(const EventPublisher& other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other">Object to Move From</param>
		/// <returns>New Object</returns>
		EventPublisher(EventPublisher&& other) noexcept = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Object to Copy</param>
		/// <returns>Newly Copied Operator</returns>
		EventPublisher& operator=(const EventPublisher& other);

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other"></param>
		/// <returns>Transferred Object</returns>
		EventPublisher& operator=(EventPublisher&& other) noexcept = default;

		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~EventPublisher() = default;

		/// <summary>
		/// Notifies all Subscribers of this Event
		/// </summary>
		void Deliver();


		/// <summary>
		/// Returns this object as a String
		/// </summary>
		/// <returns>Stringified Obeject</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Determines if Polymorphic objects are Equal
		/// </summary>
		/// <param name="other">Object to Compare</param>
		/// <returns>true if equal</returns>
		virtual bool Equals(const RTTI* other) const override;


		/// <summary>
		/// Sets the time
		/// </summary>
		/// <param name="t">The time</param>
		void SetTime(std::chrono::high_resolution_clock::time_point t);

		/// <summary>
		/// Gets the time
		/// </summary>
		/// <returns>The time</returns>
		std::chrono::high_resolution_clock::time_point GetTime() const;
	protected:
		/// <summary>
		/// List of Subscribers
		/// </summary>
		SList<EventSubscriber*>& _subscribers;
		/// <summary>
		/// Expiration Time
		/// </summary>
		std::chrono::high_resolution_clock::time_point _expirationTime;
	};
}