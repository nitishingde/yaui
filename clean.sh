#!/bin/sh

usage='$./clean.sh {--build|--cache}'

if [ $# -eq 0 ]; then
    echo $usage
    exit 1
fi

for param in $@
do
    case $param in
        --build)
            rm -rf build/*
            ;;
        --cache)
            rm -rf .cache/*
            ;;
        *)
            echo $usage
            exit 1
    esac
done
