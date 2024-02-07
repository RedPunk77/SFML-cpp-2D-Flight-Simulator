#include <SFML/Graphics.hpp>
using namespace sf;

View camera; //объект типа view
View getplayercoordinateforview(float x, float y) {
  camera.setCenter(x + 100, y);
  float tempX = x; float tempY = y;//считываем координаты игрока и проверяем их, чтобы убрать края

  if (x < 1000) tempX = 1000; //убираем из вида левую сторону
  if (y < 500) tempY = 500; //верхнюю сторону
  if (y > 520) tempY = 520; //нижнюю сторону  

  camera.setCenter(tempX, tempY);
  return camera;
}
