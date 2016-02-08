#ifndef SOURCE_LOGBUFFER_H_
#define SOURCE_LOGBUFFER_H_

#include "SAMRAI/tbox/ParallelBuffer.h"
#include <ostream>
#include <cstring>

/*
 * Some ugly MACROS to have pretty output with line number and file and
 * function names.
 */
#define __FILENAME__ (strrchr(__FILE__, '/') ?\
		strrchr(__FILE__, '/') + 1 : __FILE__)
#ifdef DEBUG
#ifndef DBG
#define DBG stafseasq::log::LogBuffer::Properties({\
		stafseasq::log::debug, __LINE__, __FILENAME__, __FUNCTION__})
#endif
#else
#define DBG
#endif
#ifndef INFO
#define INFO stafseasq::log::LogBuffer::Properties({\
		stafseasq::log::info, __LINE__, __FILENAME__, __FUNCTION__})
#endif
#ifndef WARN
#define WARN stafseasq::log::LogBuffer::Properties({\
		stafseasq::log::warn, __LINE__, __FILENAME__, __FUNCTION__})
#endif
#ifndef ERROR
#define ERROR stafseasq::log::LogBuffer::Properties({\
	stafseasq::log::error, __LINE__, __FILENAME__, __FUNCTION__})
#endif

namespace stafseasq {
namespace log {

enum Level {
	error, warning, info, debug
};

/*
 * SAMRAI already has a nice parallelized Streambuffer. So we use what we
 * get! Look into ParallelBuffers Doc for details. We just add some filtering
 * and formatted output.
 */
class LogBuffer: public SAMRAI::tbox::ParallelBuffer {
public:

	struct Properties {
		Level level;
		int line;
		std::string file;
		std::string function;
	};

	LogBuffer();
	virtual ~LogBuffer();

	void setProperties(const Properties &properties);
	void setPrefixOnOff(bool onoff);
	void setColorOnOff(bool onoff);

private:
	Properties d_properties;
	bool d_has_prefix;
	bool d_has_colors;
};

/*
 * Set properties by streaming them into the stream!
 * DANGER: if the stream does not have a LogBuffer this might EXPLODE
 */
std::ostream &operator<<(std::ostream &os, const LogBuffer::Properties &props);

}
}
#endif /* SOURCE_LOGBUFFER_H_ */
