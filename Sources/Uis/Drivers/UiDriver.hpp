#pragma once

#include "Maths/Time.hpp"

namespace acid {
/**
 * @brief Represents a driver that changes over time.
 * @tparam T The type to be driven.
 */
template<typename T>
class UiDriver {
public:
	/**
	 * Creates a new driver with a length.
	 * @param length The drivers length.
	 */
	explicit UiDriver(const Time &length) :
		m_length(length) {
	}

	virtual ~UiDriver() = default;

	/**
	 * Updates the driver with the passed time.
	 * @param delta The time between the last update.
	 * @return If the driver has not completed.
	 */
	bool Update(const Time &delta) {
		m_actualTime += delta;
		m_currentTime += delta;
		if (m_repeat)
			m_currentTime = Time::Seconds(std::fmod(m_currentTime.AsSeconds(), m_length.AsSeconds()));
		auto factor = static_cast<float>(m_currentTime / m_length);
		factor = std::clamp(factor, 0.0f, 1.0f);
		current = Calculate(factor);
		return factor != 1.0f && !m_repeat;
	}

	/**
	 * Gets the length.
	 * @return The length.
	 */
	const Time &GetLength() const { return m_length; }

	/**
	 * Sets the length.
	 * @param length The new length.
	 */
	void SetLength(const Time &length) { m_length = length; }

	/**
	 * Gets the current driver value.
	 * @return The current value.
	 */
	T Get() const { return current; }

protected:
	/**
	 * Calculates the new value.
	 * @param factor The time into the drivers life.
	 * @return The calculated value.
	 */
	virtual T Calculate(float factor) = 0;

	Time m_length;
	bool m_repeat = true;
	Time m_actualTime;
	Time m_currentTime;
	/// The most recent value calculation.
	T current{};
};
}
