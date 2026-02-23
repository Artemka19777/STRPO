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

Добавил в индекс `git add reports/lab1.md`. Теперь `git status` показывает готовность lab1 к коммиту.

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
git подсказыват, как изменить индекс и как отменить изменения. `git restore` вернул состояние коммита

### Ветвление версий

`git branch` :
 ```
lab1-1
*main(* показывает в какой я ветке)
```
При переходе `git checkout lab1-1`, выводится `M reports/lab1.md`, то есть сообщает о состоянии файлов.

При переключении веток появилось сообщение: `M README.md` и произошло переключение на ветку lab1-1. Изменения в файле README.md перенеслись в ветку lab1-1 и остались в Changes.

### Слияние веток, конфликты

Для слияния веток, нужно переключиться в основную ветку:`git checkout main`. Но консоль выдает ошибку, связанную с незакомиченными изменениями. Git не может перенести изменения, как в прошлый раз, т.к. версии lab1.md отличаются, поэтому сначала делает коммит, а потом переключаемся.

Слияние прошло через `Fast-forward`, т.e. все изменения прошли без конфликтов.

При слиянии с изменением одинх и тех же строк, строк в конце, либо соседних возникает конфликт, который нужно разрешить самому, т.е. выбирать предпочтительную версию.
```
Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Auto-merging reports/lab1.md
CONFLICT (content): Merge conflict in reports/lab1.md
Automatic merge failed; fix conflicts and then commit the result.
```
После слияния ветка lab1-1 уже не нужна, (если мы не хотим продолжить разработку конкретно в этой ветке) поэтому ее можно удалить `git branch -d lab1-1`

### Работа с удаленным репозиторием
Добавил SSH токен. Забыл, как вы рассказывали на онлайн занятии, поэтому спросил у Chatgpt.

```
git remote add origin
git push -u origin main
```
### Синхронизация с удаленным репозиторием

Скопировал удаленный репозиторий `git clone`, через SSH токен и получил те же файлы

`git fetch` скачал измения, но не применил их.

`git pull` применил и слил изменения.

### История изменений

Merge: 5a0031d 58f88ce
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 16:29:55 2026 +0300

    pull remote repository

commit 58f88ce7d33d4ac6f417266d57cb8e8473ef6d2b
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 16:14:05 2026 +0300

    commit in clone repository

commit 5a0031d09afcd2fe60a248159cf30d7755b84922
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 16:12:45 2026 +0300

    add second section

commit ecfc012c5f7382ff3f23007f8781f1adb73a0f0a
Merge: 4db72d1 1a3fd44
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 15:41:28 2026 +0300

    merge lab1-1 with main

commit 1a3fd445f506544e9eef21549c3b1aa7a989fafc
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 15:37:19 2026 +0300

    change for merge

commit 4db72d1784d9da052be27723b576fbae81e8f2f3
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 15:35:04 2026 +0300

    rename heading

commit 0c3899bf60dd036c3c53467173a2daab1493b946
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 15:30:29 2026 +0300

    commit in lab1

commit a34b16c0f0c3a30e5af237786739f232218b1794
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 15:11:51 2026 +0300

    commit in new branch(lab1-1)

commit c819abb1003ca57766819dee850de8e6fc030235
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 11:16:57 2026 +0300

     change lab1.md

commit 7f7258f8e87fd1ca76d8a2d6423deaba31bc6531
Author: Artem <artem.epp@gmail.com>
Date:   Tue Feb 17 10:54:22 2026 +0300

    commit lab1 README

commit 525e94656fa67e5a28c27e215cb9f98640c04514
Author: Artem <artem.epp@gmail.com>
Date:   Mon Feb 16 23:27:34 2026 +0300

    first commit
    