#!/bin/bash

git add $1
git commit -m "$2"

if [[ -z $3 ]]; then
   BRANCH="master"
else
   BRANCH=$3
fi

git checkout $BRANCH
git push origin $BRANCH