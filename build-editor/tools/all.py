#
# all.py - Скрипт который запускает сначала систему сборки, потом запускает бинарник.
#


# Импортируем:
import os
import sys


# Если этот файл запускают:
if __name__ == "__main__":
    os.chdir("build-editor/")  # Мы находимся в корне проекта в котором нет файлов build/run. Переходим в папку сборки.
    if sys.platform == "win32":
        os.system("build.bat && run.bat")
    else: os.system("bash build.sh && bash run.sh")
