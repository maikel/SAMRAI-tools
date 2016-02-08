#include "LogBuffer.h"
#include "Logging.h"
#include "SAMRAI/tbox/SAMRAI_MPI.h"

#include <string>
#include <iostream>

namespace stafseasq {
namespace log {

/*
 * Default constructor and destructors...
 */
LogBuffer::LogBuffer() :
		d_has_prefix(false),
		d_has_colors(false) {
}
LogBuffer::~LogBuffer() {
}

/*
 * Use the property structure as stream modifier. DANGER!
 * We do a static_cast which can fail if we dont use it on the right thing.
 */
std::ostream &operator<<(std::ostream &os, const LogBuffer::Properties &props) {
	LogBuffer *buffer = static_cast<LogBuffer *>(os.rdbuf());
	buffer->setProperties(props);
	return os;
}

/*
 * Set properties and do some logic. Check Settings and to print colors or
 * not.
 */
void LogBuffer::setProperties(const Properties &properties) {
	d_properties = properties;
	if (d_has_prefix) {
		std::stringstream prefix("");
		prefix << "[";
		switch (properties.level) {
		case error:
			if (d_has_colors) prefix << FG_RED;
			prefix << "ERROR";
			break;
		case warning:
			if (d_has_colors) prefix << FG_YELLOW;
			prefix << "WARNING";
			break;
		case info:
			if (d_has_colors) prefix << BOLD;
			prefix << "INFO";
			break;
		case debug:
			if (d_has_colors) prefix << FG_BLUE;
			prefix << "DEBUG";
			break;
		default:
			prefix << "UNKOWN";
		}
		if (d_has_colors) prefix << REGULAR << FG_DEFAULT;
		int rank = SAMRAI::tbox::SAMRAI_MPI::getSAMRAIWorld().getRank();
		prefix << "] [P=" << rank << "] [" << properties.file << "] " << "["
				<< properties.line << "] [" << properties.function << "] ";
		setPrefixString(prefix.str());
	}
}

/*
 * Just set prefix and color attributes and update your prefix, if needed.
 */
void LogBuffer::setPrefixOnOff(bool onoff) {
	d_has_prefix = onoff;
	if (!onoff) {
		setPrefixString(std::string(""));
	} else {
		setProperties(d_properties);
	}
}
/*
 * only the master process prints to a terminal. the rest goes into a file
 * TODO: the master actually gets mirrored in a file too. change the buffer
 * directly to remove the escape codes.
 */
void LogBuffer::setColorOnOff(bool onoff) {
	int rank = SAMRAI::tbox::SAMRAI_MPI::getSAMRAIWorld().getRank();
	d_has_colors = onoff && (rank == 0);
	if (d_has_prefix) {
		setProperties(d_properties);
	}
}

}
}
