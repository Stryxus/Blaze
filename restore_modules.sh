#!/bin/sh

git rm --cached Sources/css/thirdparty/*
git rm --cached FFMpegCore
git rm --cached json
git rm --cached libpng
git rm --cached libsass
git rm --cached libwebp
git rm --cached NUglify
git rm --cached Sources/css/thirdparty/*

set -e

git config -f .gitmodules --get-regexp '^submodule\..*\.path$' |
    while read path_key path
    do
        url_key=$(echo $path_key | sed 's/\.path/.url/')
        url=$(git config -f .gitmodules --get "$url_key")
        git submodule add --force $url $path
    done