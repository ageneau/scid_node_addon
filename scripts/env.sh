#!/bin/bash

ROOT=`pwd`
DEPS=$ROOT/deps
BUILD=$ROOT/src/scid
SCID_VERSION=4.6.4
SCID_SHA=04be5344fd7a164061fa34df66a924a82bbf112c
SCID_SHA_SHORT=04be534
SCID=scid-${SCID_SHA}
SCID_DEPS=$DEPS/scid
SCID_FILE=/tmp/$SCID.zip
SCID_URL=https://github.com/ageneau/scid/archive/${SCID_SHA_SHORT}.zip
