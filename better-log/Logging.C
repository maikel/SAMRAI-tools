#include "Logging.h"
#include "LogBuffer.h"
#include "SAMRAI/tbox/SAMRAI_MPI.h"
#include "SAMRAI/tbox/InputDatabase.h"
#include "SAMRAI/tbox/PIO.h"

namespace tbox = SAMRAI::tbox;

namespace stafseasq {
namespace log {

static LogBuffer log_buffer;
std::ostream out(&log_buffer);

/*
 * set default values for the buffer and point the SAMRAIs paralleled
 * log stream pout. Thats handling the file-per-processor thing and
 * we do the rest.
 */
void initialize(tbox::Pointer<tbox::InputDatabase> db) {
	int rank = SAMRAI::tbox::SAMRAI_MPI::getSAMRAIWorld().getRank();

	log_buffer.setActive(true);
	log_buffer.setOutputStream1(&tbox::pout);
	log_buffer.setOutputStream2(NULL);
	log_buffer.setPrefixOnOff(db->getBoolWithDefault("has_prefix", false));
	log_buffer.setColorOnOff(db->getBoolWithDefault("has_color", false));
	log_buffer.setProperties({ info, __LINE__, __FILE__, __FUNCTION__ });

}

std::ostream &operator<<(std::ostream &os, const Color &color) {
	return os << "\033[" << static_cast<int>(color) << "m";
}

}
}
