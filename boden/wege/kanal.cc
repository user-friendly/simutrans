/*
 * Eine Sorte Wasser die zu einer Haltestelle geh�rt
 *
 * �berarbeitet Januar 2001
 * von Hj. Malthaner
 */

#include <stdio.h>

#include "../../simworld.h"
#include "../../display/simimg.h"

#include "../../besch/grund_besch.h"
#include "../../besch/weg_besch.h"

#include "../../bauer/wegbauer.h"
#include "../../dataobj/translator.h"
#include "kanal.h"

const weg_besch_t *kanal_t::default_kanal=NULL;



kanal_t::kanal_t(loadsave_t *file) :  weg_t()
{
	rdwr(file);
}



kanal_t::kanal_t() : weg_t()
{
	set_desc(default_kanal);
}



void kanal_t::rdwr(loadsave_t *file)
{
	weg_t::rdwr(file);

	if(file->get_version() <= 87000) {
		set_desc(default_kanal);
		return;
	}

	if(file->is_saving()) {
		const char *s = get_desc()->get_name();
		file->rdwr_str(s);
	}
	else {
		char bname[128];
		file->rdwr_str(bname, lengthof(bname));

		const weg_besch_t *desc = wegbauer_t::get_desc(bname);
		int old_max_speed = get_max_speed();
		if(desc==NULL) {
			desc = wegbauer_t::get_desc(translator::compatibility_name(bname));
			if(desc==NULL) {
				desc = default_kanal;
				welt->add_missing_paks( bname, karte_t::MISSING_WAY );
			}
			dbg->warning("kanal_t::rdwr()", "Unknown channel %s replaced by %s (old_max_speed %i)", bname, desc->get_name(), old_max_speed );
		}
		set_desc(desc);
		if(old_max_speed>0) {
			set_max_speed(old_max_speed);
		}
	}
}
