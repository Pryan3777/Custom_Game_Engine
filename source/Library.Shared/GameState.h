#pragma once
#include "GameTime.h"
#include "Scope.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Stores Game Time
	/// Singleton Instance
	/// </summary>
	class GameState
	{
	public:
		/// <summary>
		/// Get the Singleton Instance
		/// </summary>
		/// <returns>The Singleton Instance</returns>
		static GameState* Instance();

		/// <summary>
		/// Creates the Singleton Instance
		/// </summary>
		static void CreateInstance();

		/// <summary>
		/// Destroys the Singleton Instance
		/// </summary>
		static void DestroyInstance();


		/// <summary>
		/// Returns the game Time
		/// </summary>
		/// <returns>Time</returns>
		GameTime Time();


		/// <summary>
		/// Sets the Game time
		/// </summary>
		/// <param name="t">Time to Set To</param>
		void SetGameTime(GameTime t);

	private:
		/// <summary>
		/// Singleton Instance
		/// </summary>
		inline static GameState* _instance;

		/// <summary>
		/// Game Time
		/// </summary>
		GameTime _time;
	};
}