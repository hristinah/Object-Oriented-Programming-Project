## Софийски университет „Св. Климент Охридски“
## Факултет по математика и информатика
![image1](https://user-images.githubusercontent.com/89635038/131332104-bc94ea9a-b91c-439e-87ee-022bba11c934.gif)
## Тема за проект
# Работа със SVG файлове

### курс Обектно-ориентирано програмиране
### за специалности Информатика, Компютърни науки и Софтуерно инженерство
### Летен семестър 2016/2017 г.

В рамките на този проект е разработено приложение, което работи със файлове във Scalable Vector Graphics (SVG) формат. Приложението може да зарежда фигури от файла, да извършва върху тях дадени операции, след което може да записва промените обратно на диска.

За улеснение, в рамките на проекта ще работим само с основните фигури (basic shapes) в SVG. То ще поддържа три от тях - линия, кръг и правоъгълник, като при нужда лесно да можете да добавите поддръжка на нови фигури. За повече информация за това кои са базовите фигури, вижте https://www.w3.org/TR/SVG/shapes.html.

Също така, за улеснение считаме, че координатната система, в която работим е тази по подразбиране: положителната полуос X сочи надясно, а положителната полуос Y сочи надолу.

Когато зареждаме съдържанието на един SVG файл, ще прочетем само фигурите, които приложението поддържа, и можем да игнорирате всички останали SVG елементи.

След като заредим фигурите, потребителят да може да изпълнява дадените в следващия раздел команди, които добавят, изтриват или променят фигурите.


## Начин на работа
Програма позволява на потребителя да отваря файлове (open), да извършва върху тях някакви операции, след което да записва промените обратно в същия файл (save) или в друг, който потребителят посочи (save as). Има и опция за затваряне на файла, без записване на промените (close). За целта, когато програмата ви се стартира, тя позволява на потребителя да въвежда команди и след това да ги изпълнява. Командите могат да имат нула, един или повече параметри, които се изреждат един след друг, разделени с интервали.

Когато отворим даден файл, неговото съдържание се зарежда в паметта, след което файлът се затваря. Всички промени, които потребителят направи след това се пазят в паметта, но не се записват обратно, освен ако потребителят изрично не укаже това.

Освен ако не е казано друго, всяка от командите извежда съобщение, от което да е ясно дали е успяла и какво е било направено.

Главните команди са:
### Open
Зарежда съдържанието на даден файл. Ако такъв не съществува се създава нов с празно съдържание. След като файлът бъде отворен и се прочете, той се затваря и приложението ви вече не трябва да работи с него, освен ако потребителят не поиска да запише обратно направените промени (вижте командата save по-долу), в който случай файлът трябва да се отвори наново. 

Всички останали команди могат да се изпълняват само ако има успешно зареден файл.

Ако при зареждането на данните, приложението открие грешка, то извежда подходящо съобщение за грешка и прекратява своето изпълнение.
```
> open C:\Temp\file.xml 
Successfully opened file.xml
```
### Close
Затваря текущо отворения документ. Затварянето изчиства текущо заредената информация и след това програмата не може да изпълнява други команди, освен отваряне на файл (Open).
```
> close
Successfully closed file.xml
```
### Save
Записва направените промени обратно в същия файл, от който са били прочетени данните.
```
> save
Successfully saved file.xml
```
### Save As
Записва направените промени във файл, като позволява на потребителя да укаже неговия път.
```
> saveas "C:\Temp\another file.xml"
Successfully saved another file.xml
```
### Exit
Излиза от програмата
```
> exit
Exiting the program...
```
## Други Операции
| | |
------------ | -------------
**Print**	| Извежда на екрана всички фигури.
**Create** |	Създава нова фигура.
**Erase**	| Изтрива фигура
**Translate**	| Транслира една или всички фигури. Ако потребителят не посочи конкретна фигура, тогава се транслират всички фигури; ако се посочи конкретна – променя се само тя.
**Within**	| Извежда на екрана всички фигури, които изцяло се съдържат в даден регион. Потребителят може да укаже какъв да бъде регионът – кръг или правоъгълник

<br>
<br>


### Примерен SVG файл figures.svg
```
<?xml version="1.0" standalone="no"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
  "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg>
  <rect x="5" y="5" width="10" height="10" fill="green" />
  <circle cx="5" cy="5" r="10" fill="blue" />
  <rect x="100" y="60" width="10" height="10" fill="red" />
</svg>
```
### Пример за работа на програмата
```
> open figures.svg
Successfully opened figures.svg

> print
1. rectangle are5 5 10 10 green
2. circle 5 5 10 blue
3. rectangle 100  60 10 10 red

> create rectangle -1000 -1000 10 20 yellow
Successfully created rectangle (4)

> print
1. rectangle 1 1 10 20 green
2. circle 5 5 10 blue
3. rectangle 100 60 10 10 red
4. rectangle -1000 -1000 10 20 yellow

> within rectangle 0 0 30 30
1. rectangle 5 5 10 10 green

> within circle 0 0 5
No figures are located within circle 0 0 5

> erase 2
Erased a circle (2)

> erase 100
There is no figure number 100!

> print
1. rectangle 5 5 10 10 green
2. rectangle 100 60 10 10 red
3. rectangle -1000 -1000 10 20 yellow

> translate vertical=”10” horizontal=”100”
Translated all figures

> print
1. rectangle 105 15 10 10 green
2. rectangle 200 70 10 10 red
3. rectangle -900 -990 10 20 yellow

> save
Successfully saved the changes to figures.svg

> exit
Exit
```
<br>
<br>
## Тестване
Тестването на програмата е извършено изцяло с GoogleTest.

