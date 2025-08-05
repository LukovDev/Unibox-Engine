@echo off

cd "tools/"
python run.py %*
rmdir /s /q "__pycache__"
cd "../"
