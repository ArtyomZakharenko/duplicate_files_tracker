# Duplicate Files Tracker

# Описание

Данная программа представляет собой утилиту для поиска дубликатов и замене найденных дубликатов на жесткие ссылки.
Во время работы программы ведется протоколирование процесса работы программы в лог-файл. Лог-файлы coхраняются в месте расположения программы, в каталоге Logs.

# Требования

Данная программа предназначена для запуска в ОС GNU/Linux. Для работы программы необходима установленная библиотека OpenSSL.

# Сборка

Для сборки debug-версии программы необходимо сделать следующее:

```bash
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```
Для сборки release-версии программы необходимо сделать следующее:

```bash
mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

# Запуск

Для запуска программы необходимо ввести команду:

```bash
./dft [OPTIONS] [PATH]
```

где OPTIONS - это набор опций, а PATH - это путь к папке, в которой необходимо произвести поиск дубликатов.

# Опции

* -r, --recursive - поиск дубликатов во всех подпапках заданной папки.
* -h, --help - вывод справки по программе.

# Примеры запуска

* ./dft -r /home/user - поиск дубликатов во всех подпапках папки /home/user.
* ./dft /home/user - поиск дубликатов в папке /home/user.
* ./dft -h - вывод справки по программе.

# Пример вывода программы

```bash
$ ./dft -r /home/artsem/test
Duplicate files with hash d784fa8b6d98d27699781bd9a7cf19f0:
/home/artsem/test/Текстовый файл….txt
/home/artsem/test/1 (1).txt

Duplicate files with hash e557499e497c2a43bbc50a21a033c199:
/home/artsem/test/Пояснительная записка (1).docx
/home/artsem/test/Пояснительная записка (2).docx

Removed duplicate file: /home/artsem/test/Текстовый файл….txt
Created hard link for file: /home/artsem/test/Текстовый файл….txt -> /home/artsem/test/1.txt
Removed duplicate file: /home/artsem/test/1 (1).txt
Created hard link for file: /home/artsem/test/1 (1).txt -> /home/artsem/test/1.txt
Removed duplicate file: /home/artsem/test/Пояснительная записка (1).docx
Created hard link for file: /home/artsem/test/Пояснительная записка (1).docx -> /home/artsem/test/Пояснительная записка.docx
Removed duplicate file: /home/artsem/test/Пояснительная записка (2).docx
Created hard link for file: /home/artsem/test/Пояснительная записка (2).docx -> /home/artsem/test/Пояснительная записка.docx

Process finished with exit code 0
```

# Автор

Студент 3 курса ВМСиС БГУИР группы 050541 Захаренко Артем Валерьевич.
Данная программа создана в рамках выполнения курсовой работы по дисциплине "Системное программное обеспечение вычислительных машин."


