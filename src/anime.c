// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2024 Moe-hacker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 */
#include "include/ruri.h"
// As an easter egg.
void AwA(void)
{
	/*
	 * Nothing is useful at this function, just for fun.
	 */
	// Get the size of terminal.
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	u_short col = size.ws_col;
	if (col % 2 == 1) {
		col -= 1;
	}
	// For centering output.
	char space[col / 2 + 1];
	space[0] = '\0';
	if (col > 60) {
		col /= 2;
		col -= 28;
		memset(space, ' ', col * sizeof(char));
		space[col] = '\0';
	} else {
		strcat(space, "");
	}
	cprintf("\033c");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██    ██████          ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██  ██      ██      ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██████          {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██  ██            {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██████          {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████                              ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██    ██████        ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██          ██        {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██████            {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██████          {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████                              ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c\n");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██                  ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██████          {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██          ██          {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██    ██████          {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c\n");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");

	usleep(100000);
	cprintf("\033c");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c\n");
	cprintf("%s%s\n", space, "{255;255;255}               ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}             ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}             ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}           ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}           ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}         ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}         ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}       ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}       ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}     ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}     ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}     ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}     ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}   ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}   ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}   ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}   ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}   ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}     ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}       ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                 ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                     ████████████████████");
	usleep(100000);
	cprintf("\033c");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c\n");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c");
	cprintf("%s%s\n", space, "{255;255;255}             ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}           ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}           ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}         ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}         ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}       ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}       ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}     ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}     ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}   ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}   ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}   ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}   ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255} ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255} ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255} ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255} ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255} ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}   ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}     ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}               ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                   ████████████████████");
	usleep(100000);
	cprintf("\033c\n");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	usleep(100000);
	cprintf("\033c\n");
	cprintf("%s%s\n", space, "{255;255;255}              ██                        ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██  ██          ██        ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}            ██    ████        ██    ██      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██          ██    ██    ████      ██");
	cprintf("%s%s\n", space, "{255;255;255}          ██      ██████████████████          ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██      ██                  ██        ██");
	cprintf("%s%s\n", space, "{255;255;255}        ██    ██                      ████    ██");
	cprintf("%s%s\n", space, "{255;255;255}      ████████        ██      ██          ████  ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██    ██        ██    ██  ██    ██    ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████      ██    ██  ████  ██    ██  ██    ██████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██  ██    ██      ████  ██  ██  ████████");
	cprintf("%s%s\n", space, "{255;255;255}    ██      ██  ██                          ████");
	cprintf("%s%s\n", space, "{255;255;255}    ██        ██                    ██████    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████        ██   ████           ██      ██  ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██       ██           {255;0;0}██  ██{255;255;255}    ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██         ██           {255;0;0}██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ██          ██   ██████           {255;0;0}██  ██{255;255;255}      ██");
	cprintf("%s%s\n", space, "{255;255;255}  ████    ██  ██                                ██");
	cprintf("%s%s\n", space, "{255;255;255}    ████  ██████          ██    ██            ██");
	cprintf("%s%s\n", space, "{255;255;255}      ██████  ████          ████          ████");
	cprintf("%s%s\n", space, "{255;255;255}                ████                    ████");
	cprintf("%s%s\n", space, "{255;255;255}                    ████████████████████");
	cprintf("%s{clear}\n", "");
}