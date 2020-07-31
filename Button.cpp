#include "Button.h"

Button::Button(uint8_t pin, uint16_t debounce_ms)
:  m_ignore_until(0)
,  m_delay(debounce_ms)
,  m_pin(pin)
,  m_state(State::eReleased)
,  m_has_changed(false)
{
	pinMode(m_pin, INPUT_PULLUP);
}

Button::State Button::read()
{
	m_has_changed = false;
	if (m_ignore_until > millis())
	{
		// ignore any changes during this period
	}
	
	// pin has changed 
	else if (digitalRead(m_pin) != m_state)
	{
		m_ignore_until = millis() + m_delay;
		m_state = !m_state;
		m_has_changed = true;
	}
	
	return static_cast<Button::State>(m_state);
}


bool Button::uniquePressed()
{
	return (pressed() && m_has_changed);
}

bool Button::uniqueReleased()
{
	return (released() && m_has_changed);
}

bool Button::pressed()
{
	return (read() == State::ePressed);
}

bool Button::released()
{
	return (read() == State::eReleased);
}
