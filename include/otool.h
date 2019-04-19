#ifndef OTOOL_H
# define OTOOL_H

#include <mach-o/loader.h>

void			set_otool_mode(int mode);
int				get_otool_mode(void);
void			print_text_section(struct section_64 *sect);

#endif
