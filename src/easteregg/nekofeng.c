#include "include/nekofeng.h"
int x;
int y;
// init() function for getting window size.
static void init()
{
	printf("\033c");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	x = size.ws_col / 2 - X_SIZE / 2;
	y = size.ws_row / 2 - Y_SIZE / 2;
}
void test()
{
	close_and_open_lefteye(100000, 1);
	blink_lefteye(100000, 5);
}
void test2()
{
	close_and_open_righteye(100000, 1);
	blink_righteye(100000, 5);
}
void AwA()
{
	printf("\033[?25l");
	init();
	struct LAYER layer;
	layer.layer = "\033[1;38;2;254;228;208m\n"
		      "          Keep moe.\n"
		      "          Keep cool.\n"
		      "         Keep hacking.\n"
		      "Keep on the side of technology.\n\n"
		      "      But talk is cheap,\n"
		      "       Show me the code.\n";
	layer.x_offset = 3;
	layer.y_offset = -2;
	typewrite_layer(&layer, 50000, true);
	sleep(2);
	clear_typewrite_layer(&layer, 50000);
	pid_t pid = fork();
	if (pid == 0) {
		test();
		exit(0);
	} else {
		waitpid(pid, NULL, WNOHANG);
	}
	pid = fork();
	if (pid == 0) {
		test2();
		exit(0);
	} else {
		waitpid(pid, NULL, WNOHANG);
	}
	printf("\n\033[?25h");
}
