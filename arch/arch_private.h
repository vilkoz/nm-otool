#ifndef ARCH_PRIVATE_H
# define ARCH_PRIVATE_H

# define IS_EXTERNAL(a) ((a) & N_EXT)
# define CPU_SUBTYPE_X86_ALL ((cpu_subtype_t)3)

void	nm(char *ptr, char *filename);

#endif
