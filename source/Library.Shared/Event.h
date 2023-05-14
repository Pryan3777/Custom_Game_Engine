#pragma once
#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Event
	/// </summary>
	/// <typeparam name="T">Type of Payload</typeparam>
	template <typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<T>, EventPublisher);

	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="message">Message To Send</param>
		Event(T& message);

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Object to Copy</param>
		Event(const Event& other) = default;

		/// <summary>
		/// Move Operator
		/// </summary>
		/// <param name="other">Object to Move From</param>
		/// <returns></returns>
		Event(Event&& other) noexcept = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Object to Copy</param>
		/// <returns>Newly Created Object</returns>
		Event& operator=(const Event& other);

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other">Object to Move From</param>
		/// <returns>Newly Created Object</returns>
		Event& operator=(Event&& other) noexcept = default;

		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~Event() = default;

		/// <summary>
		/// Subscribes to this Event Type
		/// </summary>
		/// <param name="subscriber">Subscriber to Subscribe</param>
		static void Subscribe(EventSubscriber* subscriber);

		/// <summary>
		/// Unsubscribes Subscriber from this Event Type
		/// </summary>
		/// <param name="subscriber">Object to Unsubscribe</param>
		static void Unsubscribe(EventSubscriber* subscriber);

		/// <summary>
		/// Unsubscribes all Subscribers from this Event Type
		/// </summary>
		static void UnsubscribeAll();


		/// <summary>
		/// Checks if two Events are Equal
		/// </summary>
		/// <param name="other">Event to Check Against</param>
		/// <returns>True if Equal</returns>
		virtual bool Equals(const RTTI* other) const override;

		/// <summary>
		/// The message stored in this Object
		/// </summary>
		/// <returns>The message</returns>
		T Message();
	protected:
		/// <summary>
		/// List of Subscribers to Send Message to
		/// </summary>
		inline static SList<EventSubscriber*> _subscribers{};
	private:
		/// <summary>
		/// Message to send when Delivering
		/// </summary>
		T& _message;
	};
}
#include "Event.inl"
