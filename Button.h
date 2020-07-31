#pragma once
#include "Arduino.h"

class Button
{
	public:
	    enum State : uint8_t
		{
			ePressed = LOW,
			eReleased = HIGH
		};
		explicit Button(uint8_t pin, uint16_t debounce_ms = 10);

		bool pressed();
		bool released();
		bool uniquePressed();
		bool uniqueReleased();
	private:
		State read();
		uint32_t m_ignore_until;//4 bytes
		const uint16_t m_delay;//2 bytes
		const uint8_t  m_pin;//1 byte
		uint8_t m_state : 1; 
		uint8_t m_has_changed : 1; 
};
