# Лабораторная работа №1. Базовая работа с git.

## Этапы выполнения работы

### Установка и настройка

Установил git, через файл setup

`git --version` : `git version 2.43.0`

Указал имя и почту:

```
git config --global user.name "Артём"
git config --global user.email "artem.epp@gmail.com"
```

узнал основные команды из книги [Pro Git](https://git-scm.com/book/ru/v2).

### Начало работы с новым проектом

+ Узнал основной синтаксис Markdown 
+ Составил README.md
+ Cоздал первый коммит  
```
git add README.md reports/lab1.md
git commit -m "commit lab1 README"
```

### Отслежавание состояние кода

`git status` : Вывод состояния рабочего каталога
`git diff`: Вывод разницы между коммитами, изменениями

`git status` показывает, что я нахожусь в ветке main и что я изменил файл lab1.  

`git diff` показало, что конкретно я изменил

Добавил в индекс `git add reports/lab1.md`

теперь `git status` показывает готовность lab1 к коммиту.

` git diff README.md`

Вывод: 
```
diff --git a/README.md b/README.md
index b8adf7e..0af0bb7 100644
--- a/README.md
+++ b/README.md
@@ -6,3 +6,6 @@
 ## Студент
 Эпп Артём Андреевич 
 Группа: 5130201/50302
+
+## Преподаватель 
+Сеннов Владимир Николаевич
\ No newline at end of file
```

Коммит изменений:
```
git add reports/lab1.md
git commit -m" change lab1.md"
```

### Откат изменений
Откатил изменения через `git restore`, и файл вернул состояние последнего коммита

При удалении в `git status` появилось:
```
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    reports/lab1.md
```
git подсказыват, как изменить индекс и как отменить изменения

`git restore` вернул состояние коммита

### Ветвление версий

`git branch` :
 ```
lab1-1
*main(* показывает в какой я ветке)
```
При переходе `git checkout lab1-1`, выводится `M       reports/lab1.md`, то есть сообщает о состоянии файлов.
