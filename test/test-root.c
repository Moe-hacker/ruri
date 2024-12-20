#include "../src/include/ruri.h"
int main()
{
	// Timeout: 400s
	// This file will ensure that the test will not stuck.
	pid_t pid = fork();
	if (pid > 0) {
		int status;
		for (int i = 0; i < 400; i++) {
			sleep(1);
			if (waitpid(pid, &status, WNOHANG) == pid) {
				exit(status);
			}
		}
		if (waitpid(pid, &status, WNOHANG) == 0) {
			kill(pid, SIGKILL);
			printf("Timeout\n");
			exit(114);
		}
		exit(0);
	}
	char *command[] = { "bash", "test-root.sh", NULL };
	execvp(command[0], command);
	return 0;
}