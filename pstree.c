// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2023 Moe-hacker
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
#include "ruri.h"
struct PSTREE
{
    pid_t pid;
    // Child process.
    struct PSTREE *child;
    // The next node, it has the same parent process with current node.
    struct PSTREE *next;
};
struct PSTREE *add_pid(struct PSTREE *pstree, pid_t pid)
{
    /*
     * If current pstree struct is NULL, add pid info here.
     * Or we try the ->next node.
     */
    if (pstree == NULL)
    {
        pstree = (struct PSTREE *)malloc(sizeof(struct PSTREE));
        pstree->pid = pid;
        pstree->next = NULL;
        pstree->child = NULL;
        return pstree;
    }
    pstree->next = add_pid(pstree->next, pid);
    return pstree;
}
struct PSTREE *add_child(struct PSTREE *pstree, pid_t ppid, pid_t pid)
{
    /*
     * If we find ppid in pstree nodes, add pid to the child struct of its ppid.
     * Or this function will do nothing.
     * So we can always run add_child(pstree,ppid,pid) to check && add a pid.
     */
    if (pstree == NULL)
    {
        return NULL;
    }
    if (pstree->pid == ppid)
    {
        pstree->child = add_pid(pstree->child, pid);
        return pstree;
    }
    pstree->next = add_child(pstree->next, ppid, pid);
    pstree->child = add_child(pstree->child, ppid, pid);
    return pstree;
}
pid_t get_ppid(pid_t pid)
{
    /*
     * Just a simple function that reads /proc/pid/stat and return the ppid.
     */
    pid_t ppid = 0;
    char path[PATH_MAX];
    sprintf(path, "%s%d%s", "/proc/", pid, "/stat");
    char buf[8192];
    char ppid_buf[256];
    int fd = open(path, O_RDONLY);
    read(fd, buf, sizeof(buf));
    int j = 0;
    for (int i = 0; i < sizeof(buf); i++)
    {
        if (j == 3)
        {
            for (int k = 0; buf[k + i] != ' '; k++)
            {
                ppid_buf[k] = buf[k + i];
            }
            break;
        }
        if (buf[i] == ' ')
        {
            j++;
        }
    }
    ppid = atoi(ppid_buf);
    return ppid;
}
char *getpid_name(pid_t pid)
{
    /*
     * Just like above.
     */
    char path[PATH_MAX];
    sprintf(path, "%s%d%s", "/proc/", pid, "/stat");
    char buf[8192];
    char name_buf[PATH_MAX];
    int fd = open(path, O_RDONLY);
    read(fd, buf, sizeof(buf));
    int j = 0;
    for (int i = 0; i < sizeof(buf); i++)
    {
        if (j == 1)
        {
            for (int k = 0; buf[k + i + 1] != ')'; k++)
            {
                name_buf[k] = buf[k + i + 1];
                name_buf[k + 1] = '\0';
            }
            break;
        }
        if (buf[i] == ' ')
        {
            j++;
        }
    }
    char *name = strdup(name_buf);
    return name;
}
char *getpid_stat(pid_t pid)
{
    /*
     * Just like above.
     */
    char path[PATH_MAX];
    sprintf(path, "%s%d%s", "/proc/", pid, "/stat");
    char buf[8192];
    char stat_buf[PATH_MAX];
    int fd = open(path, O_RDONLY);
    read(fd, buf, sizeof(buf));
    int j = 0;
    for (int i = 0; i < sizeof(buf); i++)
    {
        if (j == 2)
        {
            for (int k = 0; buf[k + i] != ' '; k++)
            {
                stat_buf[k] = buf[k + i];
                stat_buf[k + 1] = '\0';
            }
            break;
        }
        if (buf[i] == ' ')
        {
            j++;
        }
    }
    char *stat = strdup(stat_buf);
    return stat;
}
void print_tree(struct PSTREE *pstree, int depth)
{
    /*
     * How this function works:
     * Print info of current pid.
     * Print info of the child tree of current pid.
     * Print info of ->next node.
     */
    if (pstree == NULL)
    {
        return;
    }
    char *color[] = {"\033[1;38;2;0;0;255m", "\033[1;38;2;0;255;0m", "\033[1;38;2;255;0;0m"};
    if (depth > 0)
    {
        for (int i = 0; i < depth + 1; i++)
        {
            printf("%s: ", color[i % 3]);
        }
        printf("\n");
        for (int i = 0; i < depth; i++)
        {
            printf("%s: ", color[i % 3]);
        }
        printf("%s:·> ", color[depth % 3]);
    }
    printf("\033[1;38;2;137;180;250m%d\033[1;38;2;245;194;231m (%s) \033[1;38;2;254;228;208m%s\n", pstree->pid, getpid_stat(pstree->pid), getpid_name(pstree->pid));
    print_tree(pstree->child, depth + 1);
    print_tree(pstree->next, depth);
}
void pstree(pid_t parent)
{
    /*
     * This function gets the pid that is bigger than parent,
     * Try to add them to pstree struct if they are child of parent that is given.
     * then call print_tree to print pid tree info.
     */
    DIR *proc_dir = opendir("/proc");
    struct dirent *file;
    int len = 0;
    while ((file = readdir(proc_dir)) != NULL)
    {
        if (file->d_type == DT_DIR)
        {
            if (atoi(file->d_name) > parent)
            {
                len++;
            }
        }
    }
    seekdir(proc_dir, 0);
    int pids[len + 1];
    int i = 0;
    while ((file = readdir(proc_dir)) != NULL)
    {
        if (file->d_type == DT_DIR)
        {
            if (atoi(file->d_name) > parent)
            {
                pids[i] = atoi(file->d_name);
                i++;
            }
        }
    }
    closedir(proc_dir);
    struct PSTREE *pstree = NULL;
    pstree = add_pid(pstree, parent);
    for (int i = 0; i < len; i++)
    {
        pstree = add_child(pstree, get_ppid(pids[i]), pids[i]);
    }
    print_tree(pstree, 0);
}