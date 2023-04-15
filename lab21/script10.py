import os


filename = "example.txt"
suffix = filename.split(".")[-1]

files = [f for f in os.listdir(".") if f.endswith(suffix)]

# Проходим по каждому файлу и сравниваем его с указанным файлом
for file in files:
    if file != filename and open(file, "rb").read() == open(filename, "rb").read():
        print("Удаляем файл:", file)
        os.remove(file)
