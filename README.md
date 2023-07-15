# Smart calculator implementation in C
1. Для использования данной программы необходимо находиться в папке src/ ш выполнить команду "make install". Она создаст исполняемый файл "calculator" в папке build

2. Данная программа имеет три режима "Smart calc", "Credit calc" и "Deposit calc". 
    - Smart calc позволяет вычислять результаты математичких функций, а также строить их графики, используя переменную X
    - Credit calc позволяет рассчитать данные по кредиту, на определенный срок, по определенной ставке
    - Deposit calc нужен для рассчета доходности вклада

3. Для запуска тестов, в папке src/, выполните команду "make test", результаты будут выведены в консоль

4. Для проверки покрытия тестами в src/ выполните команду "make gcov_report", результат будет открыт как html страница

5. Для создания диструбитва в src/ выполните команду "make dist"

6. Для выполнения всех коаманд в порядке очередности используйте "make all"

### Если возникают проблеиыы при запуске на Ubuntu$:
#### Для нормальной работы на Ubuntu необходимо иметь библиотки qt, а также компилятор g++ и clang:
    sudo apt install qt6-base-dev
    sudo apt install qt5-qmake
    sudo apt install g++
    sudo apt install clang
#### Стоит проверить какая версия qt выбрана по умолчанию или превентивно сделать следующее:
    qtchooser -install qt6 ${your path to qt6, usually /usr/lib/x86_64-linux-gnu/qt6}
    QT_SELECT=qt6
    export QT_SELECT
#### Для работы с графиками необходим LibOpenGL:
    sudo apt install libgl-dev
#### Для запуска тестов и проверки покрытия нужна библиотека check и lcov:
    sudo apt install check
    sudo apt install lcov
