#include "include/ruri.h"
// Show some extra info when segfault.
static void sighandle(int sig)
{
	signal(sig, SIG_DFL);
	int clifd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
	char buf[1024];
	ssize_t bufsize = read(clifd, buf, sizeof(buf));
	fprintf(stderr, "\033[1;38;2;254;228;208m");
	fprintf(stderr, "%s\n", "  .^.   .^.");
	fprintf(stderr, "%s\n", "  /⋀\\_ﾉ_/⋀\\");
	fprintf(stderr, "%s\n", " /ﾉｿﾉ\\ﾉｿ丶)|");
	fprintf(stderr, "%s\n", " ﾙﾘﾘ >  x )ﾘ");
	fprintf(stderr, "%s\n", "ﾉノ㇏  ^ ﾉ|ﾉ");
	fprintf(stderr, "%s\n", "      ⠁⠁");
	fprintf(stderr, "Seems that it's time to abort.\n");
	fprintf(stderr, "SIG: %d\n", sig);
	fprintf(stderr, "UID: %u\n", getuid());
	fprintf(stderr, "PID: %d\n", getpid());
	fprintf(stderr, "CLI: ");
	for (ssize_t i = 0; i < bufsize - 1; i++) {
		if (buf[i] == '\0') {
			fputc(' ', stderr);
		} else {
			fputc(buf[i], stderr);
		}
	}
	fprintf(stderr, "\nThis message might caused by an internal error.\n");
	fprintf(stderr, "If you think something is wrong, please report at:\n");
	fprintf(stderr, "\033[4;1;38;2;254;228;208m%s\033[0m\n\n", "https://github.com/Moe-hacker/ruri/issues");
}
// Catch coredump signal.
void register_signal(void)
{
	signal(SIGABRT, sighandle);
	signal(SIGBUS, sighandle);
	signal(SIGFPE, sighandle);
	signal(SIGILL, sighandle);
	signal(SIGQUIT, sighandle);
	signal(SIGSEGV, sighandle);
	signal(SIGSYS, sighandle);
	signal(SIGTRAP, sighandle);
	signal(SIGXCPU, sighandle);
	signal(SIGXFSZ, sighandle);
}
