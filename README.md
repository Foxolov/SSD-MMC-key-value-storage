# SSD-MMC-key-value-storage

ТЗ:
## Описание задачи
Предлагается реализовать работу с хранилищем по ключу с симуляцией типов памяти SSD/MMC. Не использовать при реализации сторонние библиотеки.

## Общие требования:
* OS – Linux;
* Язык – C;
* Система сборки - make (https://en.wikipedia.org/wiki/Make_(software));
* При реализации учесть систему логирования (в случае возникновения ошибки при работе или при прохождении теста, человеку не знакомому с кодом, должно быть понятно в чем проблема).
## Интерфейс библиотеки “key-value storage” должен включать минимум:
* Чтение;
* Запись;
* Очистку;
* Изменение значения по ключу.
## Необходимо учитывать особенности работы данных видов памяти, основные:
* Износ ячеек памяти (балансировка записи для равномерного износа);
* Произвольный доступ на чтение;
* Постраничная (блочная) запись;
* Необходимость очистки памяти перед перезаписью (блок очистки больше, чем блок записи, например, запись блоками 512, очистка блоками 16К);
* Возможность потери питания при записи;
* Возможность искажения данных без особых причин (необходимость проверять CRC страниц при каждом чтении);
В качестве заключительного этапа предлагается оптимизировать операцию чтения (подобрать алгоритм поиска ключа на усмотрение студента) и написать тесты.
Предлагается реализацию разделить на 3 уровня:
* пользовательский - код, в котором создается библиотека и вызываются интерфейсные функции библиотеки, так же здесь можно реализовать тесты;
* собственно библиотека “key-value storage”;
* симулятор памяти SSD/MMC.

## Этапы реализации
1 Подготовить три уровня – пользовательский, собственно библиотека “key-value storage” и симулятор памяти. Собрать под ОС Linux с помощью make.
2 Реализовать симулятор SSD/MMC учитывая особенности поведения данного вида памяти. Реально данные можно писать/читать в файл на диске. Задавать константами параметры типа – размер страницы записи (write block size), размер блока очистки (erase block size), количество перезаписей страницы и т.д.
3 Реализовать в библиотеке “key-value storage” интерфейсные функции. На данном этапе можно не заботится об эффективности алгоритмов, подойдет перебор элементов.
4 Подобрать алгоритм поиска для записи/перезаписи и реализовать его.
5 Реализовать тесты (можно на пользовательском уровне):
* значение ключа больше страницы;
* потеря питания при записи;
* изменить данные из вне и почитать;
* проверить эффективность чтения/поиска после восстановления питания;
* и т.д.
