#!/bin/sh

usage='$./clean.sh {--build|--cache}'\
'\n> if left empty, by default both cache and build will get cleaned'\
'\n'

params=$@
if [ $# -eq 0 ]; then
    echo $usage
    params='--build --cache'
fi

for param in $params
do
    case $param in
        --build)
            echo '> cleaning the build dirs...'
            rm -rf build/*
            rm -rf cmake-build-debug/*
            rm -rf cmake-build-release/*
            ;;
        --cache)
            echo '> cleaning the cache dir...'
            rm -rf .cache/*
            ;;
        *)
            echo $usage
            exit 1
    esac
done
