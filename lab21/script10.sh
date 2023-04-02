#!/bin/bash

# Указываем имя файла, с которым будем сравнивать
filename="example.txt"

# Получаем суффикс файла
suffix="${filename##*.}"

# Ищем все файлы с таким же суффиксом
files=$(find . -type f -name "*.$suffix")

# Проходим по каждому файлу и сравниваем его с указанным файлом
for file in $files; do
    if cmp -s "$filename" "$file"; then
        echo "Удаляем файл: $file"
        rm "$file"
    fi
done