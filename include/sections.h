#ifndef SECTIONS_H
# define SECTIONS_H

char	**get_sections(void);
void	save_sections_64(struct segment_command_64 *seg);
void	save_sections_32(struct segment_command *seg);
void	free_sections(void);

#endif
