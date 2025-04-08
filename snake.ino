#include <GyverMAX7219.h>
MAX7219 < 1, 1, 5 > mtrx; 
#include "GyverTM1637.h"
GyverTM1637 disp(8, 9);


#define J_VRX 0
#define J_VRY 1
#define J_SW 3
#define ZERO 500
int limit = 200;
int fx = 0;
int fy = 0;
int clr = 1;
int x = 0;
int y = 0;
boolean ate = true;
int foodx = 7;
int foody = 7;
int tik = 0;  
int score = 0;

struct SKnot{
  int x;
  int y; 
};
class CSnake{  
  int len;
  SKnot body[20];
  int vx;
  int vy;
  bool eaten;
public:
  CSnake(){
    reset();
  }

  void reset(){
    len = 3;
    body[0] = {0,0};
    body[1] = {0,1};
    body[2] = {0,2};    
    vx = 0;
    vy = 1;
    eaten = false;      
  }
  void render(){
    for (int i = 0; i < len; i++){
      mtrx.dot(body[i].x, body[i].y);
    }
  }
  void move(){
    SKnot tail = body[0];
    for (int i = 0; i < len - 1; i++)
      body[i] = body[i+1];

    body[len - 1].x += vx;
    body[len - 1].y += vy;
    if (eaten){
      for (int i = len - 1; i >= 0; i--)
        body[i + 1] = body[i];
      body[0] = tail;
      len += 1;
      eaten = false;
    }
  }
  void changev(int nvx, int nvy){
    if (nvx == -vx)
      return;
    if (nvy == -vy)
      return;
    vx = nvx;
    vy = nvy;
  }
  bool isout(){
    if (body[len - 1].x < 0 || body[len -1].x > 7)
      return true;
    if (body[len - 1].y < 0 || body[len -1].y > 7)
      return true;
    if (ismybody(body[len - 1].x, body[len - 1].y, false))
      return true;
    return false;
  }

  void eat(){
    eaten = true;
  
  }
  bool ismybody(int x, int y, bool include_head=true){
    int size = include_head?len:len-1;
    for (int i = 0; i < size; i++){
      if (body[i].x == x && body[i].y == y)
        return true;
    }
    return false;   
  }


};
CSnake snake;
void gameover(){
  mtrx.fill();
  mtrx.update();
  delay(1000);
  score = 0;
  snake.reset();
  spawnfood();
  x = 0;
  y = 0;
}

void spawnfood(){
  while (true){
    foodx = random(8);
    foody = random(8);
    if (!snake.ismybody(foodx, foody))
      break; 
  }
}



void setup() {
  disp.clear();        // очистить
  disp.brightness(7);  // яркость 0-7
  
  mtrx.begin();       
  mtrx.setBright(5);  
  
  Serial.begin(9600);
  
  pinMode(J_SW, INPUT_PULLUP);
  spawnfood();

}

void loop(){
  mtrx.clear();
  snake.render();
  //Мигание еды
  if (tik % 2 == 0) 
    mtrx.dot(foodx, foody);
  mtrx.update();
  delay(500);

  //ОПРЕДЕЛЕНИЕ НАПРАВЛЕНИЯ
  int val = analogRead(J_VRX);
  if (val > ZERO + limit){
    y = 0;
    x = 1;
  }
  else if (val < ZERO - limit){
    y = 0;
    x = -1;
  }
  val = analogRead(J_VRY);
  if (val > ZERO + limit){
    x = 0;
    y = 1;
  }
  else if (val < ZERO - limit){
    x = 0;
    y = -1;
  }
  snake.changev(x, y);

  snake.move();
  //Проверка на смерть
  if (snake.isout()){
    gameover();
    return;
  }
  //Проверка на жор
  if (snake.ismybody(foodx, foody)) {
    snake.eat();
    score += 1;
    spawnfood();
  }
  disp.displayInt(score);
  tik += 1;  
}
//
//
//
//
//
//
//
//
//
//

void loop2() {
    // Изменение лимита
  if (Serial.available() > 0) limit = Serial.parseInt();



    //
  int val = analogRead(J_VRX);
  if (val > ZERO + limit){
    y = 0;
    x = 1;
  }
  else if (val < ZERO - limit){
    y = 0;
    x = -1;
  }

    //Путь по Y
  val = analogRead(J_VRY);
  if (val > ZERO + limit){
    x = 0;
    y = 1;
  }
  else if (val < ZERO - limit){
    x = 0;
    y = -1;
  }

  // Вывод значений в порт
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.println(digitalRead(J_SW) * 1);
  clr = digitalRead(J_SW) * 1;

  // Изменение координаты огонька
  // Границы X и Y
  if (fx + x > 7) fx = 7;
  else if (fx + x < 0) fx = 0;
  else fx = fx + x;

  if (fy + y > 7) fy = 7;
  else if (fy + y < 0) fy = 0;
  else fy = fy + y;

  //Проверка на жор
  if (foodx == fx && foody == fy){
    ate = true;
  }
  //Жор
  if (ate == true){
    foodx = random(8);
    foody = random(8);
    ate = false;
    score = score + 1;
  }
  // Пишем очки
  disp.displayInt(score);

  
  //Рисуем еду
  if (tik % 2 == 0) mtrx.dot(foodx, foody);
  else mtrx.dot(foodx, foody, 0);
  

  //Рисуем точку
  
  mtrx.dot(fx, fy);     // пиксель на координатах 0,0
  mtrx.update();
  delay(300);
  mtrx.clear();

  
  //Следующий тик
  tik = tik + 1;
}
