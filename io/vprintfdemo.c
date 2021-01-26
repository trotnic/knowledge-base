#include <stdio.h>
#include <stdarg.h>

void error(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "Error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
} 

int main(int argc, char *argv[]) {
	error("%s", "🥲");
	return 0;
}
