Egg Incubator Controller Project using STM32

Overview

This project is an Egg Incubator Controller  powered by an STM32 microcontroller designed to manage the incubation process of eggs. 
The system regulates temperature, humidity, egg turning, and ventilation, and it allows for both automatic and manual modes of operation.

SYSTEM ARCHITECTURE

The incubator has several operational states and modes. 
Below is the proposed system design in a hierarchical structure:

/*******************************************************************/
Encubator_controller
├── START        // Entry to Incubating Process   
├── STOP         // Entry to Idle Mode  
├── modes/                          
│   ├── AUTO/          // Automatic Mode 
│   ├── MANUAL/        // Manual Mode  
│   ├── ADJUST_SETTINGS/  // Settings Adjustments 
├── IDLE/               
│   ├── MANUAL/   
│   │   ├── EGG_TURNING 
│   │   ├── VENTILATING 
│   │   ├── CALIBRATION    
│   │   ├── HEATING
│   │   └── COOLING       
│   ├── ADJUST_SETTINGS/
/*******************************************************************/


ENUMERATION of MODES and STATES 

The incubator can operate in different modes defined as follows:

Mode Idle: When the system is inactive.
Mode Auto: For the full incubating process (automatic).

Incubation Process States
The following states control the process flow:

STATE_INCUBATING................ Eggs are being incubated.
STATE_VENTILATING............... System is ventilating.
STATE_EGG_TURNING............... Eggs are turning automatically.
STATE_ALARM..................... Alarm state triggered (e.g., temperature deviation).
STATE_HATCH..................... The incubation process has reached the hatching stage.
STATE_CALIBRATION............... Calibration of temperature or humidity.
STATE_PREHEAT................... Preheating the incubator.
STATE_DOOR_OPEN................. Incubator door is open.
STATE_ERROR..................... Error state triggered (e.g., sensor failure).
STATE_COOLING................... Cooling down the system.


Primary functions responsible for handling the system's operations:

State Handlers:
	handleState()................ Manages state transitions.
	entryIdle().................. Entry function for Idle state.
	exitIdle()................... Exit function for Idle state.
	entryIncubating()............ Entry function for Incubating state.
	exitIncubating()............. Exit function for Incubating state.
	
	
Utility Functions:
	readTemperatureHumidity().... Reads temperature and humidity data.
	configureUART().............. Configures UART communication.
	configureGPIO().............. Configures GPIO pins for input/output.
	loadSettings()............... Loads saved settings.
	saveSettings()............... Saves current settings to memory.
	triggerAlarm()............... Activates an alarm if parameters are out of range.

Control Functions
	Heating & Ventilation:
		startHeating(), stopHeating().......... Control the heating system.
		startVentilation(), deactivateFans()... Control the ventilation fans.
	
	Egg Turning:
		startEggTurning(), stopEggTurning().... Control egg turning motor.
	
	Hatching Process:
		setHatchingConditions()................ Set conditions for hatching.
		hatchComplete()........................ Marks the end of the incubation process.

Last note:
 This project can be expanded further to include features such as Wi-Fi monitoring, advanced error detection, and more.