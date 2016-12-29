#include "Irrigation.h"
#include "Sensor.h"
#include "Component.h"


Irrigation::Irrigation() {}
Irrigation::Irrigation(Conf* conf, Sensor* moistureSensor, TimedComponent* reseviorPump,
	TimedComponent* waterPump, TimedComponent* PP_1, TimedComponent* PP_2,
	TimedComponent* PP_3, TimedComponent* PP_4, TimedComponent* mixer) :
	Action(conf) {

	m_pauseDuration = 3000;
	m_pauseUntil = 0;

	m_moistureSensor = moistureSensor;
	m_reseviorPump = reseviorPump;
	m_waterPump = waterPump;
	m_PP_1 = PP_1;
	m_PP_2 = PP_2;
	m_PP_3 = PP_3;
	m_PP_4 = PP_4;
	m_mixer = mixer;
}

void Irrigation::execute(unsigned long now) {
	TimedComponent* components[] = { m_reseviorPump, m_waterPump, m_PP_1, 
		m_PP_2, m_PP_3, m_PP_4, m_mixer };

	// If there is no data in the moisture sensor or the action is already
	// running, or paused, then do nothing
	if (!m_moistureSensor->hasAverage() ||
		running(components, sizeof(components)) ||
		m_pauseUntil > now) {
		return;
	}

	// Check the moisture sensor
	float average = m_moistureSensor->getAverage();

	// If below the threshold, then irrigate
	if (average < m_conf->minWater) {
		unsigned long elapsed = 0;

		// Resevior pump
		m_reseviorPump->turnOn(now, m_conf->reseviorPumpOpen, elapsed);
		elapsed += m_conf->reseviorPumpOpen;

		// Peripump 1
		m_PP_1->turnOn(now, m_conf->PP1Open, elapsed);
		elapsed += m_conf->PP1Open;

		// Peripump 2
		m_PP_2->turnOn(now, m_conf->PP2Open, elapsed);
		elapsed += m_conf->PP2Open;

		// Peripump 3
		m_PP_3->turnOn(now, m_conf->PP3Open, elapsed);
		elapsed += m_conf->PP3Open;

		// Peripump 4
		m_PP_4->turnOn(now, m_conf->PP4Open, elapsed);
		elapsed += m_conf->PP4Open;

		// Mixer
		m_mixer->turnOn(now, m_conf->mixerOn, elapsed);
		elapsed += m_conf->mixerOn;

		// Water pump
		m_waterPump->turnOn(now, m_conf->waterPumpOpen, elapsed);
		elapsed += m_conf->waterPumpOpen;

		// Pause for a bit
		m_pauseUntil = now + elapsed + m_pauseDuration;
	}
}

bool Irrigation::running(TimedComponent* components[], int size) {
	bool running = false;
	for (int i = 0; i < size; i++) {
		running = running || components[i]->isOn();
	}
	return running;
}