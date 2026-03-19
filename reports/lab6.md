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