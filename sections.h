#ifndef SECTIONS_H
# define SECTIONS_H

char	**get_sections(void);
void	append_section(struct section_64 *sect);
void	save_sections(struct segment_command_64 *seg);

#endif
