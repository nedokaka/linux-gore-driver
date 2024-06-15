<h1 id="gore-driver">
    Gore driver
</h1>

Создает /dev/gore устройство

Не редко встречал людей с никами /dev/....... да и думал почему бы и не сделать подобный драйвер

Драйвер создает устройство /dev/gore

При ```sudo cat /dev/gore``` он будет выдавать рандомную фразу из ['словаря'](https://github.com/nedokaka/linux-gore-driver/blob/main/gore.c#L11)

Пулл реквесты приветствуются

<h3 id="include-to-kernel">
    Сборка
<h3>

```shell
make
```
<h3 id="include-to-kernel">
    Инклюд в ядро
</h3>

В папке с ядром

```shell
curl -LSs "https://raw.githubusercontent.com/nedokaka/linux-gore-driver/main/kernel/kernel-include.sh" | bash
```

<h3 id="instoll">
    Временно (до перезагрузки)
<h3>

<h4 id="instoll-1">
    Хау ту инсталл
<h4>

```shell
make install
```

<h4 id="instoll-2">
    На постоянку
<h4>

[Модулем](https://www.clearlinux.org/clear-linux-documentation/guides/kernel/kernel-modules.html)

[В ядро](#include-to-kernel)

<h3 id="change-nama">
    Смена имени устройству
<h3>

gore.c -> [DEVICE_NAME](https://github.com/nedokaka/linux-gore-driver/blob/main/gore.c#L8) замените на что вам нужно :>

<h3 id="remove-fro,-kernel">
    Удаление из ядра
</h3>

В папке с ядром

```shell
curl -LSs "https://raw.githubusercontent.com/nedokaka/linux-gore-driver/main/kernel/kernel-include.sh" | bash --cleanup
```
