#include <stdio.h>
#include "../../simdebug.h"

#include "../bildliste2d_besch.h"

#include "imagelist2d_reader.h"
#include "../obj_node_info.h"


obj_desc_t * imagelist2d_reader_t::read_node(FILE *fp, obj_node_info_t &node)
{
	ALLOCA(char, besch_buf, node.size);

	image_array_t *desc = new image_array_t();

	// Hajo: Read data
	fread(besch_buf, node.size, 1, fp);
	char * p = besch_buf;

	desc->count = decode_uint16(p);

//	DBG_DEBUG("imagelist2d_reader_t::read_node()", "count=%d data read (node.size=%i)",desc->count, node.size);

	return desc;
}
