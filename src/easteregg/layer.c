#include "include/nekofeng.h"
static void clear_layer(struct LAYER *layer)
{
	int y_offset = 0;
	int x_offset = 0;
	printf("\033[%dH", y + layer->y_offset);
	printf("\033[%dG", x + layer->x_offset);
	for (size_t i = 0; i < strlen(layer->layer); i++) {
		// The next line.
		if (layer->layer[i] == '\n') {
			y_offset++;
			x_offset = 0;
			printf("\033[%dH", y + layer->y_offset + y_offset);
			printf("\033[%dG", x + layer->x_offset);
			continue;
		}
		// Unicode.
		if (layer->layer[i] > 0x7f) {
			i += 2;
		}
		// Color.
		if (layer->layer[i] == '\033') {
			for (size_t j = i; j < strlen(layer->layer); j++) {
				if (layer->layer[j] == 'm') {
					i = j;
					break;
				}
			}
			continue;
		}
		// Skip space.
		if (layer->layer[i] != ' ') {
			printf("\033[%dG", x + layer->x_offset + x_offset);
			printf("%c", ' ');
		}
		x_offset++;
	}
	fflush(stdout);
}
static void print_layer(struct LAYER *layer)
{
	int y_offset = 0;
	printf("\033[%dH", y + layer->y_offset);
	printf("\033[%dG", x + layer->x_offset);
	for (size_t i = 0; i < strlen(layer->layer); i++) {
		// The next line.
		if (layer->layer[i] == '\n') {
			y_offset++;
			printf("\033[%dH", y + layer->y_offset + y_offset);
			printf("\033[%dG", x + layer->x_offset);
			continue;
		}
		// '#' means a ' ' to cover the layer under it.
		if (layer->layer[i] == '#') {
			printf(" ");
		} // Skip space.
		else if (layer->layer[i] != ' ') {
			printf("%c", layer->layer[i]);
		} else {
			printf("\033[1C");
		}
	}
	printf("\033[0m");
	fflush(stdout);
}
void play_action(struct ACTION *action, __useconds_t inr, unsigned int keep)
{
	struct ACTION **p = &action;
	while ((*p) != NULL) {
		print_layer((*p)->layer);
		usleep(inr);
		if ((*p)->next == NULL) {
			sleep(keep);
		}
		clear_layer((*p)->layer);
		p = &((*p)->next);
	}
}
void playback_action(struct ACTION *action, __useconds_t inr, unsigned int keep)
{
	struct ACTION **p = &action;
	while ((*p)->next != NULL) {
		p = &((*p)->next);
	}
	while ((*p) != NULL) {
		print_layer((*p)->layer);
		usleep(inr);
		if ((*p)->prior == NULL) {
			sleep(keep);
		}
		clear_layer((*p)->layer);
		p = &((*p)->prior);
	}
}
void free_action(struct ACTION *action)
{
	struct ACTION *p = action;
	while (p != NULL) {
		struct ACTION *t = p;
		p = p->next;
		free(t->layer->layer);
		free(t->layer);
		free(t);
	}
}
struct ACTION *add_action(struct ACTION *action, int x_offset, int y_offset, char *layer)
{
	struct ACTION **p = &action;
	struct ACTION *prior = action;
	while (*p != NULL) {
		prior = *p;
		p = &((*p)->next);
	}
	(*p) = malloc(sizeof(struct ACTION));
	(*p)->layer = malloc(sizeof(struct LAYER));
	(*p)->layer->x_offset = x_offset;
	(*p)->layer->y_offset = y_offset;
	(*p)->layer->layer = strdup(layer);
	(*p)->next = NULL;
	(*p)->prior = prior;
	return action;
}
