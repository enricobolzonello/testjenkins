#!/bin/sh
PM2_EXIST=$(if pm2 list 2> /dev/null | grep -q tsp_webapp; then echo "Yes" ; else echo "No" ; fi)

if [ $PM2_EXIST = Yes ] ; then
    pm2 restart tsp_webapp
    echo "Restart tsp_webapp."
else
    pm2 start file.js --name tsp_webapp
    echo "Started tsp_webapp."
fi