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
while read oldrev newrev refname
do
    if [[ $refname = "refs/heads/lab6" ]]; then
        echo "Post-receive hook: Push detected in lab6 branch. Building HTML report..."

        REPORT_FILE="report.md"
        OUTPUT_HTML="report.html"

        git show $newrev:$REPORT_FILE | pandoc -f markdown -t html --self-contained -o ../server>

        if [ $? -eq 0 ]; then
            echo "HTML report generated successfully: $OUTPUT_HTML"
        else
            echo "Error: Failed to generate HTML report."
            exit 1
        fi
    fi
done
```