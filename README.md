# Gore driver

Создает /dev/gore устройство

Не редко встречал людей с никами /dev/....... да и думал почему бы и не сделать подобный драйвер

Драйвер создает устройство /dev/gore

При ```sudo cat /dev/gore``` он будет выдавать рандомную фразу из ['словаря'](https://github.com/nedokaka/linux-gore-driver/blob/main/gore.c#L11)

Пулл реквесты приветствуются

### Сборка

```shell
make
```
### Инклюд в ядро

В папке с ядром

```shell
curl -LSs "https://raw.githubusercontent.com/nedokaka/linux-gore-driver/main/linux/kernel-include.sh" | bash
```

### Хау ту инсталл

#### Временно (до перезагрузки)

```shell
make install
```

#### На постоянку

[Модулем](https://www.clearlinux.org/clear-linux-documentation/guides/kernel/kernel-modules.html)

[В ядро](#инклюд-в-ядро)

### Смена имени устройству

gore.c -> [DEVICE_NAME](https://github.com/nedokaka/linux-gore-driver/blob/main/gore.c#L8) замените на что вам нужно :>

### Удаление из ядра

В папке с ядром

```shell
curl -LSs "https://raw.githubusercontent.com/nedokaka/linux-gore-driver/main/linux/kernel-include.sh" | bash -s -- --cleanup

```
