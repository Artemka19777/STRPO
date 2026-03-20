# Лабораторная работа №6. Простые CI-CD пайплайны

## Этапы выполнения работы

### Базовые хуки в Git на стороне клиента

Хуки - это скрипты, которые выполняются автоматически при определенных событиях

| Хук | Когда выполняется | Можно прервать |
|----|----|----|
| pre-commit | перед созданием коммита | да |
| prepare-commit-msg | перед открытием редактора сообщения | нет |
| commit-msg | после ввода сообщения коммита | да |
| post-commit | после коммита | нет |
| pre-push | перед отправкой изменений | да |

Источник: https://git-scm.com/book/ru/v2

Хук, который будет проверять файлы перед коммитом

```
cd .git/hooks
touch pre-commit
chmod +x pre-commit
```
Далее открваем хук 
```
nano pre-commit
```
Код:
```
#!/bin/bash

echo "Checking for forbidden patterns..."

files=$(git diff --cached --name-only)

for file in $files
do
    if grep -E "$forbidden_patterns" "$file"; then
        echo "ERROR: Forbidden content detected in $file"
        exit 1
    fi
done

echo "Check passed"
exit 0
```
Создадим код, который проверяет сообщение коммита.
Сообщение должно быть больше 10 символов

```
#!/bin/bash

commit_msg_file=$1
commit_msg=$(cat $commit_msg_file)

if [[ ${#commit_msg} -lt 10 ]]; then
    echo "Commit message too short!"
    exit 1
fi
exit 0
```
Вот выводы хуков:
`git commit -m"dsf"`
```
Checking for forbidden patterns...
Check passed
Commit message too short!
```
```
Checking for forbidden patterns...
ERROR: Forbidden content detected in reports/lab6.md
```
Из-за того, что я приводил в отчете код bash, где пропписаны запрещенные слова, мне не удавалось сделать коммит, пришлось удалить некоторые строчки кода.

### Хуки Git на стороне сервера
```
cd ..
artem@DESKTOP-3R7C7GG /mnt/d  $ git clone ./STRPO ./server
```
Далее переходим в основном репозиторий и добавляем сервер как удаленный репозиторий 
```
git remote add server ../server
```
Теперь можно делать push 
` git psuh server main`

Конвертировать Markdown в HTML можно через утилиту **pandoc**

```
#!/bin/bash

while read oldrev newrev refname
do
    if [[ $refname == "refs/heads/lab6-pr" ]]; then
        echo "Post-receive hook: Push detected in lab6-pr branch. Building HTML report..."

        REPORT_FILE="report.md"
        OUTPUT_HTML="report.html"

        git show $newrev:$REPORT_FILE | pandoc -f markdown -t html --self-contained -o ../../$OUTPUT_HTML

        if [ $? -eq 0 ]; then
            echo "HTML report generated successfully: ../../$OUTPUT_HTML"
        else
            echo "Error: Failed to generate HTML report."
            exit 1
        fi
    fi
done
```
Вывод на консоли при пуше:
```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 12 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 339 bytes | 56.00 KiB/s, done.
Total 4 (delta 3), reused 0 (delta 0), pack-reused 0
remote: Post-receive hook: Push detected in lab6-pr branch. Building HTML report...
remote: [WARNING] Deprecated: --self-contained. use --embed-resources --standalone
remote: [WARNING] This document format requires a nonempty <title> element.
remote:   Defaulting to '-' as the title.
remote:   To specify a title, use 'title' in metadata or --metadata title="...".
remote: HTML report generated successfully: ../../lab6.html
To ../server
 + cb5b9db...6af46c5 lab6-pr -> lab6-pr (forced update)
```
файл отображается.
![](/reports/imgs/61.png)

# Сборка с помощью CMake
Основные понятия:

* Проект (Project): Логическая единица верхнего уровня, содержащая цели и правила сборки. Задается командой project().

* Цель (Target): Конечный результат сборки  add_executable() или add_library().

* Исполняемый файл (Executable): Готовая программа, которую можно запустить.

* Библиотека (Library): Набор скомпилированного кода(.a, .lib, .so, .dll).

Конструкции:
+ target_link_libraries(lab6 lab6_lib) 
+ add_executable(lab6 main.cpp)
+ add_library(lab6_lib
    stack.cpp
    stack.h
)
+ target_include_directories(цель PRIVATE/INTERFACE/PUBLIC путь)
+ target_link_libraries(цель PRIVATE/INTERFACE/PUBLIC библиотека)

Источники: https://habr.com/ru/articles/904992/, https://cmake.org/cmake/help/latest/index.html

#### CMake вместо Make
переписал lab1 на `CMake`. в папке `tests` создал отедельный файл `CMakeLists.txt` и подключил его к соновному через `add_subdirectory(tests)`

Как проводить сборку:
* перейти в директорию `build` и сгенерируовать файлы сборки через `cmake ..`. Вывод компилятора:
    ```
    -- Configuring done (0.0s)
    -- Generating done (0.2s)
    -- Build files have been written to: /mnt/d/STRPO/struct_LAB/lab1/build
    ```
* собрать проект через `make`
    ```
    [  6%] Building CXX object CMakeFiles/lab1_library.dir/src/barrel.cpp.o
    [ 12%] Building CXX object CMakeFiles/lab1_library.dir/src/matrix.cpp.o
    ...
    [ 93%] Building CXX object tests/CMakeFiles/test_rect_properties.dir/test_rect_properties.cpp.o
    [100%] Linking CXX executable test_rect_properties
    [100%] Built target test_rect_properties
    ```
* запустить `./lab1`
* `ctest`
### Автоматизация задач CMake в git
Ответвился от ветки lab6-pr, чтобы остались наработки. 

Добавил к предыдущему хуку `pre-commit` код, который запускает тесты через `ctest`: 
```
branch=$(git rev-parse --abbrev-ref HEAD)

if [ "$branch" = "dev" ]; then
    echo "Running CMake tests..."

    repo_root=$(git rev-parse --show-toplevel)
    cd "$repo_root/struct_LAB/lab1" || exit 1

    mkdir -p build
    cd build || exit 1

    cmake ..
    make
    ctest || { echo "Tests failed. Commit aborted."; exit 1; }

    echo "All tests passed"
fi
```
теперь при коммите выдает следущее:
```
git commit -m"commit in branch dev"
Checking for forbidden patterns...
Check passed
Running CMake tests...
-- Configuring done (0.1s)
...
[100%] Built target test_rect_properties
Test project /mnt/d/STRPO/struct_LAB/lab1/build
    Start 1: test_bounding_rect
1/4 Test #1: test_bounding_rect ...............   Passed    0.01 sec
    Start 2: test_rect_basic_methods
2/4 Test #2: test_rect_basic_methods ..........   Passed    0.01 sec
    Start 3: test_rect_operations
3/4 Test #3: test_rect_operations .............   Passed    0.01 sec
    Start 4: test_rect_properties
4/4 Test #4: test_rect_properties .............   Passed    0.01 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.08 sec
All tests passed
[dev 9d356b6] commit in branch dev
 1 file changed, 24 insertions(+), 1 deletion(-)
```
