#include "include/nekofeng.h"
void face(__useconds_t inr, unsigned int keep)
{
	struct ACTION *action = NULL;
	action = add_action(action, -17, -9,
			    "\033[0m              ██                        ██\n"
			    "\033[0m            ██  ██          ██        ██  ██\n"
			    "\033[0m            ██    ████        ██    ██      ██\n"
			    "\033[0m          ██          ██    ██    ████      ██\n"
			    "\033[0m          ██      ██████████████████          ██\n"
			    "\033[0m        ██      ██                  ██        ██\n"
			    "\033[0m        ██    ██                      ████    ██\n"
			    "\033[0m      ████████        ██      ██          ████  ██\n"
			    "\033[0m      ██    ██        ██    ██  ██    ██    ██  ██\n"
			    "\033[0m    ████      ██    ██  ████  ██    ██  ██    ██████\n"
			    "\033[0m    ██        ██  ██    ██      ████  ██  ██  ████████\n"
			    "\033[0m    ██      ██  ██                          ████\n"
			    "\033[0m    ██        ██                              ██\n"
			    "\033[0m  ████        ██                              ██\n"
			    "\033[0m  ██          ██                              ██\n"
			    "\033[0m  ██          ██                               ██\n"
			    "\033[0m  ██          ██                                ██\n"
			    "\033[0m  ████    ██  ██                                ██\n"
			    "\033[0m    ████  ██████                              ██\n"
			    "\033[0m      ██████  ████                        ████\n"
			    "\033[0m                ████                    ████\n"
			    "\033[0m                    ████████████████████\n");
	play_action(action, inr, keep);
	free_action(action);
}
void mouth(__useconds_t inr, unsigned int keep)
{
	struct ACTION *action = NULL;
	action = add_action(action, 9, 8,
			    "\n"
			    "\n"
			    "  ████\n");
	action = add_action(action, 9, 8,
			    "\n"
			    "\n"
			    " ██████\n");
	action = add_action(action, 9, 8,
			    "\n"
			    "██    ██\n"
			    "  ████\n");
	play_action(action, inr, keep);
	free_action(action);
}
void blink_lefteye(__useconds_t inr, unsigned int keep)
{
	struct ACTION *action = NULL;
	action = add_action(action, 1, 3,
			    "  ██████ \n"
			    "██      ██\n"
			    "  ██████\n"
			    "  ██  ██\n"
			    "  ██████\n");
	action = add_action(action, 1, 3,
			    "\n"
			    "  ██████ \n"
			    "██      ██\n"
			    "  ██  ██\n"
			    "  ██████\n");
	action = add_action(action, 1, 3,
			    "\n\n"
			    "  ██████ \n"
			    "██      ██\n"
			    "  ██████\n");
	action = add_action(action, 1, 3,
			    "\n\n\n"
			    "  ██████ \n"
			    "██████████\n");
	action = add_action(action, 1, 3,
			    "\n\n"
			    "   ████\n"
			    "       ██\n"
			    "  █████\n");
	action = add_action(action, 1, 3,
			    "\n"
			    "  ████\n"
			    "      ██\n"
			    "        ██\n"
			    "  ██████\n");
	play_action(action, inr, keep);
	playback_action(action, inr, keep);
	free_action(action);
}
void blink_righteye(__useconds_t inr, unsigned int keep)
{
	struct ACTION *action = NULL;
	action = add_action(action, 16, 3,
			    "  ██████ \n"
			    "██      ██\n"
			    "  \033[31m██  ██\n"
			    "    ██  \n"
			    "  ██  ██\n");
	action = add_action(action, 16, 3,
			    "\n"
			    "  ██████ \n"
			    "██\033[31m██  ██\033[0m██\n"
			    "    \033[31m██\n"
			    "  ██  ██\n");
	action = add_action(action, 16, 3,
			    "\n\n"
			    "  ██████ \n"
			    "██  \033[31m██\033[0m  ██\n"
			    "  \033[31m██  ██\n");
	action = add_action(action, 16, 3,
			    "\n\n\n"
			    "  ██████  \n"
			    "██\033[31m██  ██\033[0m██ \n");
	action = add_action(action, 16, 3,
			    "\n\n"
			    "  ████\n"
			    "██\n"
			    "  █████\n");
	action = add_action(action, 16, 3,
			    "\n"
			    "    ████\n"
			    "  ██\n"
			    "██\n"
			    "  ██████\n");
	play_action(action, inr, keep);
	playback_action(action, inr, keep);
	free_action(action);
}
void close_and_open_lefteye(__useconds_t inr, unsigned int keep)
{
	struct ACTION *action = NULL;
	action = add_action(action, 1, 3,
			    "  ██████ \n"
			    "██      ██\n"
			    "  ██████\n"
			    "  ██  ██\n"
			    "  ██████\n");
	action = add_action(action, 1, 3,
			    "\n"
			    "  ██████ \n"
			    "██      ██\n"
			    "  ██  ██\n"
			    "  ██████\n");
	action = add_action(action, 1, 3,
			    "\n\n"
			    "  ██████ \n"
			    "██      ██\n"
			    "  ██████\n");
	action = add_action(action, 1, 3,
			    "\n\n\n"
			    "██████████\n"
			    "  ██████  \n");
	action = add_action(action, 1, 3,
			    "\n\n\n"
			    "\n"
			    "  ██████  \n");
	play_action(action, inr, keep);
	playback_action(action, inr, keep);
	free_action(action);
}
void close_and_open_righteye(__useconds_t inr, unsigned int keep)
{
	struct ACTION *action = NULL;
	action = add_action(action, 16, 3,
			    "  ██████ \n"
			    "██      ██\n"
			    "  \033[31m██  ██\n"
			    "    ██  \n"
			    "  ██  ██\n");
	action = add_action(action, 16, 3,
			    "\n"
			    "  ██████ \n"
			    "██\033[31m██  ██\033[0m██\n"
			    "    \033[31m██\n"
			    "  ██  ██\n");
	action = add_action(action, 16, 3,
			    "\n\n"
			    "  ██████ \n"
			    "██  \033[31m██\033[0m  ██\n"
			    "  \033[31m██  ██\n");
	action = add_action(action, 16, 3,
			    "\n\n\n"
			    "  ██████  \n"
			    "██\033[31m██  ██\033[0m██ \n");
	action = add_action(action, 16, 3,
			    "\n\n\n"
			    "\n"
			    "  ██████  \n");
	play_action(action, inr, keep);
	playback_action(action, inr, keep);
	free_action(action);
}
