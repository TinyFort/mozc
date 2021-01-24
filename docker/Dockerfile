# SPDX-License-Identifier: AGPL-3.0
# Copyright (C) 2019-2020 Coooooooozy

FROM debian:10

ENV DEBIAN_FRONTEND=noninteractive

## Generate locale
ARG lang=0
RUN apt-get update  -y \
 && apt-get install -y --no-install-recommends \
    fonts-noto-cjk \
    locales    
RUN echo "ja_JP.UTF-8 UTF-8" > /etc/locale.gen \
 && echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen \
 && echo "${lang} UTF-8" >> /etc/locale.gen
RUN locale-gen ${lang}
RUN /usr/sbin/update-locale LANG=${lang}

## Common packages for linux
RUN apt-get update  -y \
 && apt-get install -y --no-install-recommends \
    apt-transport-https \
    apt-utils \
    bzip2 \
    ca-certificates \
    clang \
    cmake \
    curl \
    fonts-noto-cjk \
    git \
    gnupg \
    libboost-all-dev \
    libc++-dev \
    libc++abi-dev \
    make \
    nano \
    ninja-build \
    nkf \
    patch \
    pkg-config \
    python \
    python-six \
    python3-six \
    rsync \
    ruby \
    software-properties-common \
    unzip \
    wget

## Packages for linux desktop
RUN apt-get update  -y \
 && apt-get install -y --no-install-recommends \
    libglib2.0-dev \
    libgtk2.0-dev \
    libibus-1.0-dev \
    libxcb-xfixes0-dev \
    qt5-default \
    qtbase5-dev 

## Bazel
## https://docs.bazel.build/versions/master/install-ubuntu.html
RUN apt-get install -y \
    curl \
    gnupg \
    libncurses5
RUN curl -fsSL https://bazel.build/bazel-release.pub.gpg \
  | gpg --dearmor > bazel.gpg
RUN mv bazel.gpg /etc/apt/trusted.gpg.d/
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" \
  | tee /etc/apt/sources.list.d/bazel.list
RUN apt-get update -y \
 && apt-get install -y --no-install-recommends \
    bazel

## Packages for Android
RUN apt-add-repository 'deb http://security.debian.org/debian-security stretch/updates main' \
 && apt-get update -y \
 && apt-get install -y --no-install-recommends \
    lib32z1 \
    lib32ncurses-dev \
    lib32stdc++6 \
    libc6-i386 \
    libjsr305-java zip \
    openjdk-11-jdk \
    openjdk-11-jre-headless

## Clean up
RUN apt-get -y update \
 && apt-get -y upgrade \
 && apt-get autoremove -y \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

ENV DEBIAN_FRONTEND=

## Setup build user
ARG gid=0
ARG uid=0
RUN groupadd -g ${gid} craft
RUN useradd \
    --gid craft \
    --uid ${uid} \
    --shell /bin/bash \
    --home /home/builder \
    --create-home \
    builder

## Setup develop environment
USER builder
RUN mkdir -p /home/builder/workspace/

## Android SDK/NDK
## Install sdkmanager and tools
## https://developer.android.com/studio/index.html
## https://developer.android.com/studio/command-line/sdkmanager.html
WORKDIR /home/builder/workspace
ENV ANDROID_HOME /home/builder/workspace/Android/Sdk
RUN mkdir -p ${ANDROID_HOME}/cmdline-tools
ENV PATH $PATH:${ANDROID_HOME}/cmdline-tools/tools:${ANDROID_HOME}/cmdline-tools/tools/bin

RUN curl -Lo a.zip \
    https://dl.google.com/android/repository/commandlinetools-linux-6609375_latest.zip \
 && unzip -o -d $ANDROID_HOME/cmdline-tools a.zip \
 && rm a.zip
RUN echo y | sdkmanager --verbose "build-tools;30.0.2"
RUN echo y | sdkmanager --verbose "cmake;3.10.2.4988404"
RUN echo y | sdkmanager --verbose "cmdline-tools;latest"
RUN echo y | sdkmanager --verbose "emulator"
RUN echo y | sdkmanager --verbose "extras;android;m2repository"
RUN echo y | sdkmanager --verbose "extras;google;google_play_services"
RUN echo y | sdkmanager --verbose "extras;google;m2repository"
RUN echo y | sdkmanager --verbose "ndk;21.3.6528147"
RUN echo y | sdkmanager --verbose "patcher;v4"
RUN echo y | sdkmanager --verbose "platform-tools"
RUN echo y | sdkmanager --verbose "platforms;android-30"
RUN echo y | sdkmanager --verbose "sources;android-30"
RUN echo y | sdkmanager --verbose "platforms;android-29"
RUN echo y | sdkmanager --verbose "sources;android-29"
RUN echo y | sdkmanager --verbose "platforms;android-28"
RUN echo y | sdkmanager --verbose "sources;android-28"
RUN echo y | sdkmanager --verbose "platforms;android-27"
RUN echo y | sdkmanager --verbose "sources;android-27"
RUN echo y | sdkmanager --update

ENV PATH $PATH:${ANDROID_HOME}/platform-tools:${ANDROID_HOME}/build-tools/30.0.2
ENV ANDROID_NDK_HOME ${ANDROID_HOME}/ndk/21.3.6528147
ENV PATH $PATH:${ANDROID_NDK_HOME}

## Android Studio
## https://developer.android.com/studio/index.html?hl=en#downloads
WORKDIR /home/builder/workspace
RUN curl -Lo a.tar.gz \
    https://redirector.gvt1.com/edgedl/android/studio/ide-zips/4.0.2.0/android-studio-ide-193.6821437-linux.tar.gz \
 && tar -xvzf a.tar.gz \
 && rm a.tar.gz

WORKDIR /home/builder/workspace

# Ignore root
USER root
RUN usermod -L root
USER builder

CMD bash
