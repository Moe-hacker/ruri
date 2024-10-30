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
static char *line_get_username(const char *_Nonnull p)
{
	/*
	 * Get username by line.
	 */
	char *ret = malloc(128);
	ret[0] = '\0';
	// /etc/passwd format:
	// name:password:uid:gid:comment:home directory:login shell
	// So we only need the string before the first colon.
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == ':') {
			break;
		}
		ret[i] = p[i];
		ret[i + 1] = '\0';
	}
	return ret;
}
static uid_t line_get_uid(const char *_Nonnull p)
{
	/*
	 * Get uid by line.
	 */
	uid_t ret = 0;
	// /etc/passwd format:
	// name:password:uid:gid:comment:home directory:login shell
	// So we need to skip 2 colons.
	for (int i = 0; i < 2; i++) {
		if (strchr(p, ':') == NULL) {
			return 0;
		}
		p = strchr(p, ':') + 1;
	}
	// Now, after we skip 2 colons, we can get the uid.
	// Read the uid until we meet the next colon.
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == ':') {
			return ret;
		}
		ret = ret * 10 + (uid_t)(p[i] - '0');
	}
	return 0;
}
static char *get_username(uid_t uid)
{
	/*
	 * Get username by uid.
	 */
	int fd = open("/etc/passwd", O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		return NULL;
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = malloc((size_t)size + 1);
	read(fd, buf, (size_t)size);
	buf[size] = '\0';
	close(fd);
	char *p = buf;
	uid_t tmpuid;
	char *tmpusername;
	// Every time, we get the username and uid by line.
	// If the uid is equal to the uid we want, we return the username.
	while (true) {
		tmpusername = line_get_username(p);
		tmpuid = line_get_uid(p);
		if (tmpuid == uid) {
			free(buf);
			return tmpusername;
		}
		free(tmpusername);
		p = strchr(p, '\n');
		if (p == NULL) {
			break;
		}
		p = p + 1;
	}
	free(buf);
	return NULL;
}
static uid_t line_get_uid_lower(const char *_Nonnull p)
{
	/*
	 * Get uid_lower by line.
	 */
	uid_t ret = 0;
	// /etc/subuid format:
	//   foo:uid_lower:uid_count
	// So we need to skip a colon.
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	p = strchr(p, ':') + 1;
	// Check if there is still a colon.
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	// Read the uid_lower until we meet the next colon.
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == ':') {
			return ret;
		}
		ret = ret * 10 + (uid_t)(p[i] - '0');
	}
	return ret;
}
static uid_t line_get_uid_count(const char *_Nonnull p)
{
	/*
	 * Get uid_count by line.
	 */
	uid_t ret = 0;
	// /etc/subuid format:
	//   foo:uid_lower:uid_count
	// So we need to skip 2 colons.
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	p = strchr(p, ':') + 1;
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	p = strchr(p, ':') + 1;
	// Check if there is a \n (newline).
	if (strchr(p, '\n') == NULL) {
		return 0;
	}
	// Read the uid_count until we meet the newline.
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == '\n') {
			return ret;
		}
		ret = ret * 10 + (uid_t)(p[i] - '0');
	}
	return ret;
}
static void get_uid_map(char *_Nonnull user, struct ID_MAP *_Nonnull id_map)
{
	/*
	 * Get uid_map.
	 */
	id_map->uid_lower = 0;
	id_map->uid_count = 0;
	// Read file to memory.
	int fd = open("/etc/subuid", O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		return;
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = malloc((size_t)size + 1);
	read(fd, buf, (size_t)size);
	buf[size] = '\0';
	close(fd);
	// Find username in /etc/subuid.
	char *map = strstr(buf, user);
	if (map == NULL) {
		// If username is not in /etc/subuid.
		id_map->uid_lower = 0;
		id_map->uid_count = 0;
		return;
	}
	// Get uid_lower and uid_count.
	id_map->uid_lower = line_get_uid_lower(map);
	id_map->uid_count = line_get_uid_count(map);
	free(buf);
}
static gid_t line_get_gid_lower(const char *_Nonnull p)
{
	/*
	 * See comments in line_get_uid_lower().
	 */
	gid_t ret = 0;
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	p = strchr(p, ':') + 1;
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == ':') {
			return ret;
		}
		ret = ret * 10 + (gid_t)(p[i] - '0');
	}
	return ret;
}
static gid_t line_get_gid_count(const char *_Nonnull p)
{
	/*
	 * See comments in line_get_uid_count().
	 */
	gid_t ret = 0;
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	p = strchr(p, ':') + 1;
	if (strchr(p, ':') == NULL) {
		return 0;
	}
	p = strchr(p, ':') + 1;
	if (strchr(p, '\n') == NULL) {
		return 0;
	}
	for (int i = 0; p[i] != '\0'; i++) {
		if (p[i] == '\n') {
			return ret;
		}
		ret = ret * 10 + (gid_t)(p[i] - '0');
	}
	return ret;
}
static void get_gid_map(const char *_Nonnull user, struct ID_MAP *_Nonnull id_map)
{
	/*
	 * Get gid_map.
	 */
	id_map->gid_lower = 0;
	id_map->gid_count = 0;
	// /etc/subgid format:
	//   foo:gid_lower:gid_count
	//   bar:gid_lower:gid_count
	int fd = open("/etc/subgid", O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		return;
	}
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = malloc((size_t)size + 1);
	read(fd, buf, (size_t)size);
	buf[size] = '\0';
	close(fd);
	char *map = strstr(buf, user);
	if (map == NULL) {
		id_map->gid_lower = 0;
		id_map->gid_count = 0;
		return;
	}
	// Get gid_lower and uid_count.
	id_map->gid_lower = line_get_gid_lower(map);
	id_map->gid_count = line_get_gid_count(map);
	free(buf);
}
struct ID_MAP get_idmap(uid_t uid, gid_t gid)
{
	/*
	 * Get uid_map and gid_map.
	 * This function will return a ID_MAP struct for `newuidmap` and `newgidmap`.
	 * If there is any error, all the id_map will be 0.
	 */
	struct ID_MAP ret;
	ret.uid = uid;
	ret.gid = gid;
	char *username = get_username(uid);
	log("{base}Username: {cyan}%s\n", username);
	if (username == NULL) {
		ret.uid_lower = 0;
		ret.uid_count = 0;
		ret.gid_lower = 0;
		ret.gid_count = 0;
		return ret;
	}
	get_uid_map(username, &ret);
	get_gid_map(username, &ret);
	log("{base}uid: {cyan}%d\n", ret.uid);
	log("{base}gid: {cyan}%d\n", ret.gid);
	log("{base}uid_lower: {cyan}%d\n", ret.uid_lower);
	log("{base}uid_count: {cyan}%d\n", ret.uid_count);
	log("{base}gid_lower: {cyan}%d\n", ret.gid_lower);
	log("{base}gid_count: {cyan}%d\n", ret.gid_count);
	free(username);
	return ret;
}