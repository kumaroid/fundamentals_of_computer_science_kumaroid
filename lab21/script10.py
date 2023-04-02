import os

# Указываем имя файла, с которым будем сравнивать
filename = "example.txt"

# Получаем суффикс файла
suffix = filename.split(".")[-1]

# Ищем все файлы с таким же суффиксом
files = [f for f in os.listdir(".") if f.endswith(suffix)]

# Проходим по каждому файлу и сравниваем его с указанным файлом
for file in files:
    if file != filename and open(file, "rb").read() == open(filename, "rb").read():
        print("Удаляем файл:", file)
        os.remove(file)