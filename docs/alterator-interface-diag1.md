Интерфейс Diag1 
===============

Для реализации интерфейса требует создать три файла:

1. \*.backend
2. \*.desktop
3. исполняемый файл

где \* – имя файла.

Описание файлов
===============

\*.backend
---------------

Расположение: /usr/share/alterator/backends

Формат файла представляет из себя последовательность секций.

**Секция Manager – обязательная секция**

- module\_name – имя модуля, который будет обрабатывать запросы. Значение должно быть “executor”.
- node\_name – имя узла в поддереве D-Bus. Значение произвольное, [A-Z][a-z][0-9]_.
- interface\_name – имя интерфейса D-Bus. Указываем diag1.

Пример реализации секции:

```
[Manager]

module_name = executor

node_name = example

interface_name = diag1
```
*Каждая следующая секция – это метод определенный интерфейсом diag1. Интерфейс diag1 требует определения трех методов: info, run, list*

**Секция Info**

Метод Info предназначен для передачи программе информации об инструменте и содержащихся в нем тестах. Данную информацию содержит в себе файл \*.desktop, поэтому нужно указать к нему путь.

- execute — содержимое \*.desktop файла
- stdout\_bytes — должно быть установлено значение enabled

Пример реализации секции:

```
[Info]

execute = cat /usr/share/adttools/example.desktop

stdout_bytes = enabled

stdout_byte_limit = 200000
```

**Секция Run**

Метод Run предназначен для запуска тестов инструмента.

В секции определяется параметр execute, значением которого является путь к исполняемому файлу, принимающий на вход только один параметр.

Интерфейс diag1 определяет два типа сигналов:

1. stdout\_signal\_name — сигнал вывода потока байтов в sdtout
2. stderr\_signal\_name — сигнал вывода потока байтов в stderr

Значения stdout\_signal\_name и stderr\_signal\_name должны иметь значения, эквивалентные испускаемым интерфейсом d-bus. В случае использования alterator-manager значения следующие:

const STDOUT\_SIGNAL\_NAME = "diag1\_stdout\_signal";

const STDERR\_SIGNAL\_NAME = "diag1\_stderr\_signal"

Пример реализации секции:

```
[Run]	

execute = /usr/share/alterator/backends/example.sh {param}

stdout_signal_name = diag1_stdout_signal

stderr_signal_name = diag1_stderr_signal

thread_limit = 3
```

Вместо {param} будет подставлено название теста, полученного из метода list.

**Секция List**

Метод List предназначен для получения списка названий тестов(для использования в методе Run), содержащихся в инструменте. В секции определяется параметр execute, значение которого это путь к исполняемому файлу а также конкретный параметр, в ходе анализа которого программа возвращает построчно список названий тестов.

аction\_id – идентификатор для polkit, позволяющий запускать метод без административных привилегий.

Пример реализации секции:

``` 
[List]

execute = /usr/share/alterator/backends/example.sh -l

stdout_strings = enabled

action_id = list
```
*Более подробно с форматом .backend-файлов можно ознакомиться в репозитории проекта [alterator-manager](https://gitlab.basealt.space/alt/alterator-manager/-/blob/master/docs/README-ru.md).*


**\*.desktop**
---------------

Расположение: любое. Рекомендуется /usr/share/adttools

Этот файл предназначен для настройки отображения текстовых данных об инструменте и его тестах в пользовательском интерфейсе ADT.

Формат файла представляет из себя последовательность секций.

Обязательные для заполнения параметры:

name = <название пакета>

name = <название теста>

Формат:

**Обязательная секция Desktop Entry**

```
[Desktop Entry]

name = <название инструмента>

name[ru_RU] = <название инструмента на русском>

name[en_EN] = < название инструмента на английском>

category = <название категории>

category[ru_RU] = <название категории на русском>

category[en_EN] = <название категории на английском>

description = <описание инструмента>

description[ru_RU] = <описание инструмента на русском>

description[en_EN] = <описание инструмента на английском>

icon=system-run
```

**Далее нужно указать секцию для каждого тестового метода**
```

[<название теста>]

name = <название теста>

name[ru_RU] = <название теста на русском>

name[en_US] = test <название теста на английском>

description = <описание теста>

description[ru_RU] = <описание теста на русском>

description[en_US] = <описание теста на английском>
```

Исполняемый файл
---------------

Расположение: любая исполняемая директория (bin)

Требования к исполняемому файлу:

при получении на вход параметра -l (или любой другой флаг, указанный в файле *.backend в секции list в параметре execute) выдавать список названий тестов построчно в stdout. Программа также должна принимать в качестве параметра каждое значение из списка названий тестов, для запуска этого теста. Во время работы теста, справочную информацию необходимо отправлять в stdout, информацию об ошибках - в stderr. Если тестирование не выявило ошибок, то код возврата должен быть 0, если были выявлены ошибки, то отличный от 0.

**Пример:**

```
$ example -l

test1

test2

$ example test1

some diagnostic information for test1...

```

# Пример файла example.backend
```
[Manager]
module_name = executor
node_name = example
interface_name = diag1

[Info]
execute = cat /usr/share/adttools/example.desktop
stdout_bytes = enabled
stdout_byte_limit = 200000

[Run]
execute = /usr/share/alterator/backends/example.sh {param}
stdout_signal_name = diag1_stdout_signal
stderr_signal_name = diag1_stderr_signal
thread_limit = 3

[List]
execute = /usr/share/alterator/backends/example.sh -l
stdout_strings = enabled
stdout_strings_limit = 200000
action_id = list
```

# Пример файла example.desktop
```
[Desktop Entry]
name=example
name[ru_RU]=тестовый пакет
name[en_US]=example package

description=diag_1 description
description[ru_RU]=описание 
description[en_US]=description 

icon=system-run

[test1]
name = test1
name[ru_RU]=10 строк в stdout
name[en_US]=10 strings to stdout
description=тест записывает 10 строк в stdout
description[ru_RU]=записывает 10 строк в stdout
description[en_US]=write 10 strings to stdout

[test2]
name = test2
name[ru_RU]=10 строк в stderr
name[en_US]=10 strings to stderr
description=тест записывает 10 строк в stderr
description[ru_RU]=записывает 10 строк в stderr
description[en_US]=writes 10 strings to stderr
```

# Пример исполняемого файла
```
#!/bin/bash
DOMAIN="www.basealt.ru"
PROG="net-diag"
VERSION=0.0.1
ipv6_address="2001:4860:4860::8888"
ping_count=3
runcmd=run

show_usage(){
    echo "Active Directory net diagnostic tool"
    echo ""
    echo "Usage: $PROG [options] [<check/test-function-name>]"
    echo ""
    echo "<check/test-function-name> must be a function name from the list of tests"
    echo ""
    echo "Options:"
    echo "  -h, --help      This message"
    echo "  -V, --version      Display version number"
    echo "  -l, --list      List of tests"
    echo ""
    exit 0;
}

print_version(){
echo "$PROG" ": " "$VERSION"
}

check_ipv4(){
ping -c "$ping_count" -W 1 -4 "$DOMAIN" >/dev/null 2>&1
exit $?
}

check_ipv6(){
ping -c "$ping_count" -W 1 -6 "$ipv6_address" >/dev/null 2>&1
exit $?
}

if [ "$#" -gt 0 ];then
for input in "$@"; do
    case "$input" in
  -h | --help) show_ usage
   ;;
  -l | --list) listcmd=1
   ;;
  -v | --version) print_version
   ;;
  check_ipv4) check_ipv4
   ;;
  check_ipv6) check_ipv6
   ;;
  *) echo "Unrecognized option: $input"
   ;;
  esac
done
fi


list_run(){
    echo "$1"
}

run(){
    local retval=126
    local func="$1"
    $func 2>&1 | retval=0  retval=$?
    return $retval
}

if ! test -z $listcmd; then
    runcmd=list_run
fi

$runcmd check_ipv4 "Check ipv4"
$runcmd check_ipv6 "Check ipv6"

```

