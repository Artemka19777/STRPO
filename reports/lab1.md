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