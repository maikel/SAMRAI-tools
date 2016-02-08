#ifndef SOURCE_LOGGING_H_
#define SOURCE_LOGGING_H_

#include "SAMRAI/tbox/InputDatabase.h"

#include <ostream>


namespace stafseasq {
namespace log {

namespace tbox = SAMRAI::tbox;

void initialize(tbox::Pointer<tbox::InputDatabase> db);

extern std::ostream out;

/*
 * Enable colored output for streams. Got the idea from
 * http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
 * and added some codes.
 */
enum Color {
	BOLD    = 1,
	REGULAR = 0,
	FG_RED = 31,
	FG_GREEN = 32,
	FG_YELLOW = 33,
	FG_BLUE = 34,
	FG_DEFAULT = 39,
	BG_RED = 41,
	BG_GREEN = 42,
	BG_BLUE = 44,
	BG_DEFAULT = 49
};

/*
 * Just print the escape codes for the terminal into the stream.
 * Looks ugly on non-terminals.
 * TODO: add a check where the stream points to (file or terminal)
 */
std::ostream &operator<<(std::ostream &os, const Color &color);

}
}

#endif /* SOURCE_LOGGING_H_ */
