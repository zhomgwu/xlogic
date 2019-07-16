#!/bin/bash

cd bin
sql2cpp ../../mysql_script/game_db.sql src/server_db game_db
