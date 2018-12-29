#!/bin/bash

REPO_DIR="$(git rev-parse --show-toplevel)"

echo "Copy flatbuffers build files to libs/serialization..."
# copy all TS files to the client
cp  "${REPO_DIR}/include/executionGraph/serialization/schemas/ts/"* \
    "${REPO_DIR}/gui/executionGraphGui/client/libs/serialization/src/lib"

echo "Copy flatbuffers build files to libs/messages..."
cp  "${REPO_DIR}/gui/executionGraphGui/messages/schemas/ts/"* \
    "${REPO_DIR}/gui/executionGraphGui/client/libs/messages/src/lib"
