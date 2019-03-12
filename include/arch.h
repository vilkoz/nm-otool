#ifndef ELF_64_H
# define ELF_64_H

void	handle_64(char *ptr);
void	handle_32(char *ptr);
void	handle_archive(char *ptr, const char *filename);
void	handle_fat_binary(void *ptr);

#endif
