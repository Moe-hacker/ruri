#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
#
#
# This file is part of ruri, with ABSOLUTELY NO WARRANTY.
#
# MIT License
#
# Copyright (c) 2024 Moe-hacker
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
import requests
import json
import platform
import os
import sys


def panic(message):
    print("\033[31m", end="")
    print(message)
    print("\033[0m", end="")
    exit(1)


# Get the architecture of host.
def get_host_arch():
    # TODO: add more architecture support.
    arch = platform.machine()
    if arch == "x86_64":
        arch = "amd64"
    elif arch == "AMD64":
        arch = "amd64"
    elif arch == "aarch64":
        arch = "arm64"
    return arch


# Get authorization token.
def get_token(image):
    response = requests.get(
        "https://auth.docker.io/token?service=registry.docker.io&scope=repository%3Alibrary%2F" + image +
        "%3Apull")
    response = json.loads(response.text)
    if response.__contains__('token') == False:
        panic("Could not get token!")
    return response['token']


# Get the manifests of the image:tag.
def get_tag_manifests(image, tag, token):
    response = requests.get("https://registry-1.docker.io/v2/library/" + image + "/manifests/" + tag,
                            headers={
                                "Authorization": "Bearer " + token,
                                "Accept": "application/vnd.docker.distribution.manifest.list.v2+json"
                            })
    if response.status_code != 200:
        panic("Get manifests failed!")
    # TODO: add more architecture support.
    # print(response.text)
    return json.loads(response.text)


# Get the digest of image:tag.
def get_tag_digest(manifests):
    for i in range(len(manifests['manifests'])):
        if manifests['manifests'][i]['platform']['architecture'] == get_host_arch():
            return manifests['manifests'][i]['digest']
    return None


# Get filelist to download in /blobs/
def get_blobs(image, digest, token):
    ret = []
    response = requests.get("https://registry-1.docker.io/v2/library/" + image + "/manifests/" + digest,
                            headers={
                                "Authorization": "Bearer " + token,
                                "Accept": "application/vnd.oci.image.manifest.v1+json"
                            })
    if response.status_code != 200:
        panic("Get blobs failed!")
    manifests = json.loads(response.text)
    for i in range(len(manifests['layers'])):
        ret.append(manifests['layers'][i]['digest'])
    return ret


# Pull images.
def pull_image(image, blobs, token, savedir):
    os.system("mkdir " + savedir)
    for i in range(len(blobs)):
        print("\033[33mpulling: \033[32m" + blobs[i][7:] + "\033[0m")
        os.system("curl -s -L -H \"Authorization: Bearer " + token + "\"" +
                  " https://registry-1.docker.io/v2/library/" + image + "/blobs/" + blobs[i] + " -o " + savedir +
                  "/" + "rootfs_" + blobs[i][7:])
    os.system("cd " + savedir + " && sudo tar -xvf ./* && rm rootfs_*")


# Get start command.
def get_cmd(image, digest, token):
    print("")
    response = requests.get("https://registry-1.docker.io/v2/library/" + image + "/manifests/" + digest,
                            headers={
                                "Authorization": "Bearer " + token,
                                "Accept": "application/vnd.oci.image.manifest.v1+json"
                            })
    if response.status_code != 200:
        panic("Get config failed!")
    manifests = json.loads(response.text)
    config = manifests['config']['digest']
    response = requests.get("https://registry-1.docker.io/v2/library/" + image + "/blobs/" + config,
                            headers={
                                "Authorization": "Bearer " + token,
                                "Accept": "application/vnd.oci.image.manifest.v1+json"
                            })
    if response.status_code != 200:
        panic("Get config failed!")
    response = json.loads(response.text)
    print("\033[32mDefault start command is:\033[33m")
    for i in range(len(response['config']['Cmd'])):
        print(response['config']['Cmd'][i], end="")
        print(" ", end="")
    print("")
    print("\033[32mRun this command in container to start its service (If need)\033[0m")


# Download images and unpack.
def pull(image, tag, savedir):
    token = get_token(image)
    manifests = get_tag_manifests(image, tag, token)
    digest = get_tag_digest(manifests)
    blobs = get_blobs(image, digest, token)
    pull_image(image, blobs, token, savedir)
    get_cmd(image, digest, token)


# Search images
def search_image(image, page_size):
    response = requests.get("https://hub.docker.com/v2/search/repositories/?page_size=" + str(page_size) +
                            "&query=" + image)
    if response.status_code != 200:
        panic("Search failed!")
    response = json.loads(response.text)
    for i in range(len(response['results'])):
        if response['results'][i]['is_official']:
            print("\033[33m" + response['results'][i]['repo_name'] + "\033[34m [official]")
        else:
            print("\033[33m" + response['results'][i]['repo_name'])
        if response['results'][i]['short_description'] == "":
            print("  \033[32mNo description found\033[0m")
        else:
            print("  \033[32m" + response['results'][i]['short_description'] + "\033[0m")


# Search for tag.
def search_tag(image, page_size):
    response = requests.get("https://hub.docker.com/v2/repositories/library/" + image + "/tags/?page_size=" +
                            str(page_size))
    if response.status_code != 200:
        panic("Search failed!")
    response = json.loads(response.text)
    for i in range(len(response['results'])):
        print("\033[32m[" + image + "] " + response['results'][i]['name'] + "\033[0m")


def show_help():
    print("usage: dockerhub.py [-h] [-s | -t [image]] [-p [image] [tag] [savedir]]")
    print("")
    print("A tool to get rootfs from dockerhub")
    print("")
    print("options:")
    print("  -h, --help                            show this help message and exit")
    print("  -s, --search  [image] <page_size>     search for image, like `docker search`")
    print("  -t, --tag     [image] <page_size>     get tags of image")
    print("  -p, --pull    [image] [tag] [savedir] pull rootfs and unpack to savedir")


def parse_arg(argv):
    if len(argv) < 2:
        show_help()
        exit(1)
    for i in range(1, len(argv)):
        if argv[i] == "-h":
            show_help()
            exit(0)
        elif argv[i] == "--help":
            show_help()
            exit(0)
        elif argv[i] == "-s":
            if i + 1 < len(argv):
                image = argv[i + 1]
                if i + 2 < len(argv):
                    page_size = int(argv[i + 2])
                else:
                    page_size = 20
                search_image(image, page_size)
                exit(0)
            else:
                panic("missing argument [image]")
        elif argv[i] == "--search":
            if i + 1 < len(argv):
                image = argv[i + 1]
                if i + 2 < len(argv):
                    page_size = int(argv[i + 2])
                else:
                    page_size = 20
                search_image(image, page_size)
                exit(0)
            else:
                panic("missing argument [image]")
        elif argv[i] == "-t":
            if i + 1 < len(argv):
                image = argv[i + 1]
                if i + 2 < len(argv):
                    page_size = int(argv[i + 2])
                else:
                    page_size = 20
                search_tag(image, page_size)
                exit(0)
            else:
                panic("missing argument [image]")
        elif argv[i] == "--tag":
            if i + 1 < len(argv):
                image = argv[i + 1]
                if i + 2 < len(argv):
                    page_size = int(argv[i + 2])
                else:
                    page_size = 20
                search_tag(image, page_size)
                exit(0)
            else:
                panic("missing argument [image]")
        elif argv[i] == "-p":
            if i + 3 < len(argv):
                image = argv[i + 1]
                tag = argv[i + 2]
                savedir = argv[i + 3]
                pull(image, tag, savedir)
            else:
                panic("missing argument [image] [tag] [savedir]")
        elif argv[i] == "--pull":
            if i + 3 < len(argv):
                image = argv[i + 1]
                tag = argv[i + 2]
                savedir = argv[i + 3]
                pull(image, tag, savedir)
            else:
                panic("missing argument [image] [tag] [savedir]")
        else:
            panic("unknown argument!")


if __name__ == "__main__":
    parse_arg(sys.argv)
