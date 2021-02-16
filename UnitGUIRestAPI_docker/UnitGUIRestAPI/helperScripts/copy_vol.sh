#!/bin/sh

echo Google@2020 | sudo -S cp -R /var/lib/docker/volumes/taacVolume1/_data/workspace/jenkinsDocker /var/lib/docker/volumes/volBuild/_data/
echo Google@2020 | sudo -S cp /home/testVolume/build.sh /var/lib/docker/volumes/volBuild/_data/
echo Google@2020 | sudo -S cp /home/testVolume/testrun.sh /var/lib/docker/volumes/volBuild/_data/
