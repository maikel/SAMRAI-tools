#include "Logging.h"
#include "LogBuffer.h"
#include "SAMRAI/tbox/SAMRAI_MPI.h"
#include "SAMRAI/tbox/InputDatabase.h"

namespace tbox = SAMRAI::tbox;

namespace stafseasq {
namespace log {

static LogBuffer log_buffer;
std::ostream out(&log_buffer);

void initialize(tbox::Pointer<tbox::InputDatabase> db) {
	int rank = SAMRAI::tbox::SAMRAI_MPI::getSAMRAIWorld().getRank();

	log_buffer.setActive(rank == 0);
	log_buffer.setOutputStream1(&std::cout);
	log_buffer.setOutputStream2(NULL);
	log_buffer.setProperties(
			{ info, rank, "main.C", "main(int, char**)" });
	log_buffer.setPrefixOnOff(db->getBoolWithDefault("has_prefix", false));
	log_buffer.setColorOnOff(db->getBoolWithDefault("has_color", false));

}

std::ostream &operator<<(std::ostream &os, const Color &color) {
	return os << "\033[" << static_cast<int>(color) << "m";
}

}
}
