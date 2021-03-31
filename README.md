# Processes algo

### Вариант #23
Сравните и выведите в консоль время работы последовательного и параллельного с использованием 
нескольких процессов алгоритмов, каждый из которых выделяет в динамической памяти символьный массив 
размером 100 Мб и, рассматривая его содержимое как абстрактную переписку, определяет 
эмоциональную окраску последней. Переписка считается оптимистичной, если диграфов `:)` в ней больше, 
чем диграфов `:(`, в противном случае переписка признается пессимистичной.

#### Итог: #### 

В 476 раз быстрее при паралельной реализации (mac 2017 2,3 GHz 2‑ядерный Intel Core i5)

<pre>
Consistent algorithm time: 0.566633
Parallel algorithm time: 0.001190
Emotional color positive
</pre>

[![Build Status](https://travis-ci.com/Blackblackofficial/Struct-HTML-Paralels.svg?branch=hw-2)](https://travis-ci.com/Blackblackofficial/Struct-HTML-Paralels)
[![codecov](https://codecov.io/gh/Blackblackofficial/Struct-HTML-Paralels/branch/hw-2/graph/badge.svg?token=gy3WneDO92)](https://codecov.io/gh/Blackblackofficial/Struct-HTML-Paralels)