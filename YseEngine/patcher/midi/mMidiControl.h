#if YSE_WINDOWS
#pragma once
#include "../pObject.h"

namespace YSE {
	namespace PATCHER {
		PATCHER_CLASS(mMidiControl, YSE::OBJ::M_CONTROL)
			_NO_MESSAGES
			_DO_CALCULATE

			_INT_IN(SetIntValue)

private:
	int cvalue;
	int controller;
	int channel;
	};
}
}

#endif