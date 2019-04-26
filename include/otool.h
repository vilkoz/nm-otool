#ifndef OTOOL_H
# define OTOOL_H

#include <mach-o/loader.h>

void			set_otool_mode(int mode);
int				get_otool_mode(void);
void			otool_print_text_section_64(struct segment_command_64 *seg,
					const char *ptr);
void			otool_print_text_section_32(struct segment_command *seg,
					const char *ptr);

#endif
