#!/bin/bash
green='\033[0;32m'        # Green
red='\033[0;31m'          # Red
color_off='\033[0m'       # Text Reset


cd /opt/blog
git pull origin master && echo -e $green"PULL SUCCESS"$color_off || echo -e $red"PULL FAILED"$color_off
source "/root/venv-mkdocs/bin/activate"
mkdocs build && echo -e $green"BUILD SUCCESS"$color_off || echo -e $red"BUILD FAILED"$color_off
deactivate