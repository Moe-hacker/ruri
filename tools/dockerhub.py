#!/usr/bin/env python3
import requests
import json
import platform
import os
import argparse


def panic(message):
    print("\033[31m", end="")
    print(message)
    print("\033[0m", end="")
    exit(1)


# Get the architecture of host.
def get_host_arch():
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
        "https://auth.docker.io/token?service=registry.docker.io&scope=repository%3Alibrary%2F"
        + image + "%3Apull")
    response = json.loads(response.text)
    if response.__contains__('token') == False:
        panic("Could not get token!")
    return response['token']


# Get the manifests of the image:tag.
def get_tag_manifests(image, tag, token):
    response = requests.get("https://registry-1.docker.io/v2/library/" +
                            image + "/manifests/" + tag,
                            headers={"Authorization": "Bearer " + token})
    if response.status_code != 200:
        panic("Get manifests failed!")
    return json.loads(response.text)


# Get the digest of image:tag.
def get_tag_digest(manifests):
    for i in range(len(manifests['manifests'])):
        if manifests['manifests'][i]['platform'][
                'architecture'] == get_host_arch():
            return manifests['manifests'][i]['digest']
    return None


# Get filelist to download in /blobs/
def get_blobs(image, digest, token):
    ret = []
    response = requests.get("https://registry-1.docker.io/v2/library/" +
                            image + "/manifests/" + digest,
                            headers={
                                "Authorization":
                                "Bearer " + token,
                                "Accept":
                                "application/vnd.oci.image.manifest.v1+json"
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
                  " https://registry-1.docker.io/v2/library/" + image +
                  "/blobs/" + blobs[i] + " -o " + savedir + "/" + blobs[i])


# Get start command.
def get_cmd(image, digest, token):
    response = requests.get("https://registry-1.docker.io/v2/library/" +
                            image + "/manifests/" + digest,
                            headers={
                                "Authorization":
                                "Bearer " + token,
                                "Accept":
                                "application/vnd.oci.image.manifest.v1+json"
                            })
    if response.status_code != 200:
        panic("Get config failed!")
    manifests = json.loads(response.text)
    config = manifests['config']['digest']
    response = requests.get("https://registry-1.docker.io/v2/library/" +
                            image + "/blobs/" + config,
                            headers={
                                "Authorization":
                                "Bearer " + token,
                                "Accept":
                                "application/vnd.oci.image.manifest.v1+json"
                            })
    if response.status_code != 200:
        panic("Get config failed!")
    response = json.loads(response.text)
    for i in range(len(response['config']['Cmd'])):
        print(response['config']['Cmd'][i], end="")
        print(" ", end="")
    print("")


# Download images and unpack.
def pull(image, tag, savedir):
    token = get_token(image)
    manifests = get_tag_manifests(image, tag, token)
    digest = get_tag_digest(manifests)
    blobs = get_blobs(image, digest, token)
    pull_image(image, blobs, token, savedir)
    get_cmd(image, digest, token)


# Search images
def search(image, page_size):
    response = requests.get(
        "https://hub.docker.com/v2/search/repositories/?page_size=" +
        str(page_size) + "&query=" + image)
    if response.status_code != 200:
        panic("Search failed!")
    response = json.loads(response.text)
    for i in range(len(response['results'])):
        if response['results'][i]['is_official']:
            print("\033[33m" + response['results'][i]['repo_name'] +
                  "\033[34m [official]")
        else:
            print("\033[33m" + response['results'][i]['repo_name'])
        if response['results'][i]['short_description'] == "":
            print("  \033[32mNo description found\033[0m")
        else:
            print("  \033[32m" + response['results'][i]['short_description'] +
                  "\033[0m")


def search_tag(image, page_size):
    response = requests.get("https://hub.docker.com/v2/repositories/library/" +
                            image + "/tags/?page_size=" + str(page_size))
    if response.status_code != 200:
        panic("Search failed!")
    response = json.loads(response.text)
    for i in range(len(response['results'])):
        print("\033[32m[" + image + "] " + response['results'][i]['name'])
