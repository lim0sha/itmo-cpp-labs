# Лабораторная работа №3. Перегрузка операторов.

Согласно варианту описать указанные типы данных и поместить их в отдельный заголовочный файл, в нем же описать операторы, указанные в варианте. Реализацию функций поместить с отдельный cpp файл.
Написать программу, проверяющую правильность работы – для наглядности и лучшего усвоения материала использовать как явный, так и не явный метод вызова функций операторов (см. пример в конце задания).

Варианты

| № | Тип данных                                                                                                                                   | Операторы                                                                                                                                                                                                                                                                                   |
| - | -------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1 | Комплексное число                                                                                                                            | Умножение комплексного числа на вещественное число. Сложение двух комплексных чисел.<br>Умножение двух комплексных чисел.<br>Длина комплексного числа (используйте для этого, например, операцию «приведение к double» – operator double (Complex&).                                        |
| 2 | Квадрат на плоскости. Задается координатой левого верхнего угла, стороной квадрата и углом, на который квадрат повернут относительно оси OX. | Равенство площадей квадратов (перегрузите операции ==,<br>!=, <, >)<br>Умножение квадрата на вещественное число (увеличивает сторону квадрата).<br>Прибавление к квадрату вектора (смещение квадрата на указанный вектор).                                                                  |
| 3 | Треугольник на плоскости (самостоятельно выбирайте необходимые данные).                                                                      | Равенство площадей треугольников (перегрузите операции<br>\==, !=, <, >) – для вычисления площади можете использовать, например, формулу Герона (зависит от тех данных, что используются для хранения треугольника).<br>Прибавление вектора (смещение треугольника на<br>указанный вектор). |
| 4 | Матрица 3x3                                                                                                                                  | Перемножение двух матриц.<br>Умножение матрицы на вещественное число. Вычитание и сложение матриц.<br>Сравнение матриц (==, !=, >, <);                                                                                                                                                      |
| 5 | Стек целых чисел глубиной не более 100.                                                                                                      | Добавление числа в стек (operator << ). Изъятие числа из стека (operator >>).<br>Не забудьте написать простую функцию (не оператор) для вывода стека на экран – с ней будет удобнее производить<br>отладку.                                                                                 |
| 6 | Массив целых чисел<br>(длина не более 100).                                                                                                  | Объединение двух массивов в один (operator+)<br>Сравнение длин массивов (==, >, < !=).                                                                                                                                                                                                      |
| 7 | Подмножество множества целых чисел от нуля до девяти: { 0, 1, 2, … 9 }.                                                                      | Объединение двух множеств (operator+). Сравнение (== и !=).<br>Добавление числа в множество (operator+=).<br>Изъятие числа из множества (operator-=).                                                                                                                                       |
| 8 | FIFO (очередь) целых<br>чисел длиной не более 100.                                                                                           | Добавить целое число в очередь (operator<<) Взять число из очереди (operator>>)                                                                                                                                                                                                             |


Распределение вариантов

|        | **1** | **2** | **3** | **4** | **5** | **6** | **7** | **8** |        |
| ------ | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------ |
| **1**  |       |       | X     |       |       | X     |       |       | **1**  |
| **2**  |       |       |       | X     |       |       | X     |       | **2**  |
| **3**  | X     |       |       |       | X     |       |       |       | **3**  |
| **4**  |       | X     |       |       |       | X     |       |       | **4**  |
| **5**  |       |       | X     |       |       |       | X     |       | **5**  |
| **6**  |       |       |       | X     |       |       |       | X     | **6**  |
| **7**  | X     |       |       |       |       | X     |       |       | **7**  |
| **8**  |       | X     |       |       |       |       | X     |       | **8**  |
| **9**  |       |       | X     |       |       |       |       | X     | **9**  |
| **10** |       |       |       | X     | X     |       |       |       | **10** |
| **11** | X     |       |       |       |       |       | X     |       | **11** |
| **12** |       | X     |       |       |       |       |       | X     | **12** |
| **13** |       |       | X     |       | X     |       |       |       | **13** |
| **14** |       |       |       | X     |       | X     |       |       | **14** |
| **15** | X     |       |       |       |       |       |       | X     | **15** |
| **16** |       | X     |       |       | X     |       |       |       | **16** |
| **17** |       |       | X     |       |       | X     |       |       | **17** |
| **18** |       |       |       | X     |       |       | X     |       | **18** |
| **19** | X     |       |       |       | X     |       |       |       | **19** |
| **20** |       | X     |       |       |       | X     |       |       | **20** |
| **21** |       |       | X     |       |       |       | X     |       | **21** |
| **22** |       |       |       | X     |       |       |       | X     | **22** |
| **23** | X     |       |       |       |       | X     |       |       | **23** |
| **24** |       | X     |       |       |       |       | X     |       | **24** |
|        | **1** | **2** | **3** | **4** | **5** | **6** | **7** | **8** |        |
