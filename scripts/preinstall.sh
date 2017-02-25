#!/bin/bash

. ./scripts/env.sh

cd $DEPS

echo "Downloading $SCID from $SCID_URL"

curl -C - --fail --output $SCID_FILE $SCID_URL || wget --continue $SCID_URL -O $SCID_FILE

if [ $? != 0 ] ; then
    echo "Unable to download scid"
    exit 1
fi

rm -rf $SCID_DEPS

unzip $SCID_FILE

mv $SCID $SCID_DEPS

cd $SCID_DEPS
patch -p1 < ../../patches/0001-NodeJS-patch.patch
