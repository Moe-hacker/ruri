#include "include/nekofeng.h"
static int get_last_line_size(char *buf)
{
	if (buf == NULL) {
		return 0;
	}
	char *tmp = NULL;
	int ret = 0;
	for (size_t i = strlen(buf); i > 0; i--) {
		if (buf[i] == '\n') {
			tmp = strdup(&buf[i + 1]);
			break;
		}
	}
	for (size_t i = 0; i < strlen(tmp); i++) {
		// Color.
		if (tmp[i] == '\033') {
			for (size_t j = i; j < strlen(tmp); j++) {
				if (tmp[j] == 'm') {
					i = j;
					break;
				}
			}
			continue;
		}
		ret++;
	}
	free(tmp);
	return ret;
}
static char *del_last_line(char *buf)
{
	if (buf == NULL) {
		return NULL;
	}
	char *tmp = strdup(buf);
	for (size_t i = strlen(buf); i > 0; i--) {
		if (buf[i] == '\n') {
			tmp[i] = '\0';
			break;
		}
	}
	free(buf);
	return tmp;
}
static int get_lines(char *buf)
{
	int j = 0;
	for (size_t i = 0; i < strlen(buf); i++) {
		if (buf[i] == '\n') {
			j++;
		}
	}
	return j;
}
void typewrite_layer(struct LAYER *layer, __useconds_t inr, bool blink)
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
			// Color.
			if (layer->layer[i] == '\033') {
				// Be mindful! This might overflow.
				char tmp[1024] = { '\0' };
				for (size_t j = i; j < strlen(layer->layer); j++) {
					tmp[j - i] = layer->layer[j];
					tmp[j - i + 1] = 0;
					if (layer->layer[j] == 'm') {
						i = j;
						printf("%s", tmp);
						break;
					}
				}
				continue;
			}
			if (blink) {
				printf("#");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D");
				printf("£");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D");
				printf("&");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D");
				printf("*");
				fflush(stdout);
				usleep(inr / 8);
				printf("\033[1D");
			}
			printf("%c", layer->layer[i]);
			fflush(stdout);
			usleep(inr);
		} else {
			printf("\033[1C");
		}
	}
}
void clear_typewrite_layer(struct LAYER *layer, __useconds_t inr)
{
	int y_offset = get_lines(layer->layer);
	char *buf = strdup(layer->layer);
	int x_offset = 0;
	for (int i = y_offset; i > 0; i--) {
		x_offset = get_last_line_size(buf);
		buf = del_last_line(buf);
		for (int j = x_offset; j > 0; j--) {
			printf("\033[%dH", y + layer->y_offset + i);
			printf("\033[%dG", x + layer->x_offset + j - 1);
			printf(" ");
			fflush(stdout);
			usleep(inr);
		}
	}
	free(buf);
}
