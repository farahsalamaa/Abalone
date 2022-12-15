#include "debug.h"

void exit_error(const char *fmt, ...) {
	/* exit_error affiche SUR LA SORTIE D'ERREUR (stderr) le message 
	 * passé en argument (selon signature printf) 
	 * et interrompt immédiatement le programme.
	 * Si errno est non nul, perror est appliqué plutôt que fprintf
	 */ 
	char s[MAX_ERR];
	va_list argp;
	va_start(argp, fmt);
	//vfprintf(stderr, fmt, argp);
	vsnprintf(s, MAX_ERR, fmt, argp);
	va_end(argp);
	if (errno==0)
		fprintf(stderr, "%s\n", s);
	else
		perror(s);
	exit(EXIT_FAILURE);
}
