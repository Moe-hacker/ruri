#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>
#define X_SIZE 36
#define Y_SIZE 2
struct LAYER {
	char *layer;
	int x_offset;
	int y_offset;
};
struct ACTION {
	struct LAYER *layer;
	struct ACTION *prior;
	struct ACTION *next;
};
struct MSG {
	char *msg;
	struct MSG *next;
};
extern int x;
extern int y;
extern atomic_flag lock;
void spin_lock(atomic_flag *lock);
void spin_unlock(atomic_flag *lock);
void play_action(struct ACTION *action, __useconds_t inr, unsigned int keep);
void playback_action(struct ACTION *action, __useconds_t inr, unsigned int keep);
void free_action(struct ACTION *action);
struct ACTION *add_action(struct ACTION *action, int x_offset, int y_offset, char *layer);
void face(__useconds_t inr, unsigned int keep);
void mouth(__useconds_t inr, unsigned int keep);
void blink_lefteye(__useconds_t inr, unsigned int keep);
void blink_righteye(__useconds_t inr, unsigned int keep);
void close_and_open_lefteye(__useconds_t inr, unsigned int keep);
void close_and_open_righteye(__useconds_t inr, unsigned int keep);
void typewrite_layer(struct LAYER *layer, __useconds_t inr, bool blink);
void clear_typewrite_layer(struct LAYER *layer, __useconds_t inr);
