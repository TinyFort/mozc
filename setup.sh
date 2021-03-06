#!/bin/bash -e

#http://stackoverflow.com/a/246128/5209556
#https://stackoverflow.com/questions/35006457
SOURCE="${BASH_SOURCE[0]:-$0}"
while [ -h "$SOURCE" ]; do
    DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
    SOURCE="$(readlink "$SOURCE")"
    [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

cd $DIR

if [ ! -e .git ]; then
    git clone \
        https://github.com/TinyFort/Kurage.git \
        tmp \
        --branch product \
        --no-checkout \
        --depth 1 \
        --no-single-branch
    mv --update tmp/.git .
    rm -rf tmp
    git reset \
        --hard \
        --recurse-submodules \
        origin/product
    git submodule update --init
fi

cd docker
bash setup.sh
