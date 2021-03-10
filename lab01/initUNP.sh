#!/bin/bash
gitpath=https://github.com/k84d/unpv13e.git
cd ~
git clone ${gitpath}
mv unpv13e src
cd src
chmod 777 configure
./configure
cd lib
make
cd ~/src/intro
make daytimetcpsrv
make daytimetcpcli
