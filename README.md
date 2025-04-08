# 🐍 Snake Game for Arduino

Простой, но увлекательный проект аркадной игры **"Змейка"**, реализованной на платформе Arduino. Проект написан на языке C++ с использованием Arduino API и позволяет поностальгировать по классической игре прямо на микроконтроллере!

## 🎯 Описание

Змейка двигается по матрице (обычно LED 8x8 или дисплей), съедает "еду", увеличиваясь в размере. Цель игры — не врезаться в стены и не съесть саму себя.

Игра реализована без сторонних библиотек и демонстрирует основы работы с:

- массивами и динамическими структурами
- обработкой ввода с кнопок/джойстика
- рендерингом на дисплей/матрицу
- системами координат

## ⚙️ Требования

- Arduino Uno / Nano / совместимая плата
- LED-матрица 8x8 или OLED-дисплей (или другой тип дисплея, который ты используешь)
- Джойстик или 4 кнопки управления (вверх/вниз/влево/вправо)
- Резисторы, провода, макетная плата

## 🚀 Установка

1. Склонируй репозиторий:
   ```bash
   git clone https://github.com/username/snake-arduino.git
