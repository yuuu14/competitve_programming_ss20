#!/bin/bash
git add .
git commit -m "$1"

if [[ -z $2 ]]; then
    BRANCH="master"
else
    BRANCH=$2
fi

git checkout $BRANCH
git push origin $BRANCH
