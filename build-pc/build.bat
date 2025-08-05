@echo off

cd "tools/"
python build.py %*
cd "../"
