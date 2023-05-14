#include "pch.h"
#include "ActionEvent.h"

namespace FieaGameEngine
{
	void ActionEvent::Update(GameTime g)
	{
		g;
		for (size_t i = AuxiliaryAttributes().first; i < AuxiliaryAttributes().second; ++i)
		{
			_message.Append(FindName(i)) = _index[i]->second;
		}
		_message["Subtype"] = _data["Subtype"];

		EventQueue::Enqueue(std::make_shared<Event<EventMessageAttributed>>(_message), std::chrono::duration<int, std::ratio<1, 1000>>(_data["Delay"].FrontInt()));
	}
	Vector<Signature> ActionEvent::Signatures()
	{
		return {
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(ActionEvent, _subtype)},
			{"Delay", Datum::DatumTypes::Integer, 1, offsetof(ActionEvent, _delay)}
		};
	}
}