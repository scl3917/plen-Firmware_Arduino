// Arduinoライブラリ関連
#include "Arduino.h"

// 独自ライブラリ関連
#include "System.h"
#include "MotionController.h"


namespace {
	PLEN2::System system;
}


void PLEN2::MotionController::dump(unsigned char slot)
{
	#if _DEBUG
		system.outputSerial().println(F("in fuction : MotionController::dump()"));
	#endif

	if (slot >= SLOT_MAX())
	{
		return;
	}

	Header header;
	header.slot = slot;
	getHeader(&header);

	system.outputSerial().println(F("{"));

		system.outputSerial().print(F("\t\"slot\": "));
		system.outputSerial().print(header.slot, HEX);
		system.outputSerial().println(F(","));

		system.outputSerial().print(F("\t\"name\": "));
		system.outputSerial().print(header.name);
		system.outputSerial().println(F(","));

		system.outputSerial().println(F("\t\"codes\": ["));
	
			system.outputSerial().print(F("\t\t\"function\": "));
			system.outputSerial().print(header.codes[0], HEX);
			system.outputSerial().println(F(","));

			system.outputSerial().print(F("\t\t\"arguments\": ["));
	
				system.outputSerial().print(header.codes[1], HEX);
				system.outputSerial().println(F(","));

				system.outputSerial().print(header.codes[2], HEX);
	
			system.outputSerial().println(F("\t\t]"));
	
		system.outputSerial().println(F("\t],"));

		system.outputSerial().println(F("\t\"frames\": ["));

		for (int index = 0; index < header.frame_num; index++)
		{
			Frame frame;
			frame.number = index;
			getFrame(header.slot, &frame);

			system.outputSerial().println(F("\t\t{"));

			system.outputSerial().print(F("\t\t\t\"transition_time_ms\": "));
			system.outputSerial().print(frame.transition_time_ms);
			system.outputSerial().println(F(","));

			system.outputSerial().println(F("\t\t\t\"outputs\": ["));



			system.outputSerial().println(F("\t\t\t]"));

			system.outputSerial().print();

			if ((index + 1) == header.frame_num)
			{
				system.outputSerial().println(F("\t\t}"));
			}
			else
			{
				system.outputSerial().println(F("\t\t},"));
			}
		}

		system.outputSerial().println(F("\t]"));
	
	system.outputSerial().println(F("}"));

	Frame frame;
	frame.number = 0;
}