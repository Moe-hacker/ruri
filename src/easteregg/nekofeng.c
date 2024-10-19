#include "include/nekofeng.h"
int x;
int y;
atomic_flag lock = ATOMIC_FLAG_INIT;
void spin_lock(atomic_flag *lock)
{
	while (atomic_flag_test_and_set(lock)) {
	}
}
void spin_unlock(atomic_flag *lock)
{
	atomic_flag_clear(lock);
}
// init() function for getting window size.
static void init()
{
	printf("\033c");
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	x = size.ws_col / 2 - X_SIZE / 2;
	y = size.ws_row / 2 - Y_SIZE / 2;
}
void *test0(void *arg)
{
	face(100000, 15);
	return arg;
}
void *test1(void *arg)
{
	close_and_open_lefteye(100000, 1);
	blink_lefteye(100000, 5);
	return arg;
}
void *test2(void *arg)
{
	close_and_open_righteye(100000, 1);
	blink_righteye(100000, 5);
	return arg;
}
void *test3(void *arg)
{
	mouth(100000, 15);
	return arg;
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
	pthread_t t0, t1, t2, t3;
	pthread_create(&t0, NULL, test0, NULL);
	pthread_create(&t3, NULL, test3, NULL);
	pthread_create(&t1, NULL, test1, NULL);
	pthread_create(&t2, NULL, test2, NULL);
	sleep(15);
	printf("\n\033[?25h");
}
