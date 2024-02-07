#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include "Camera.h" //подгружаем свои библиотеки
#include "Maph.h"
using namespace sf;  //пространство имён sf

RenderWindow window(VideoMode(1920, 1080), "Sky of Motherland. 1.0", Style::Fullscreen); //создаём окно
class Player {  //создаем универсальный объект класса Player
private: float x = 0;
      float y = 0;
public:
    float w, h, speedx = 0, speedy = 0, dx, dy;
    int dir = 0, score = 0; //DIRection - напрваление
    String file;
    Texture texture;
    Sprite sprite;
    Player(String F, int x1, int y1, float w1, float h1) {
        file = F;
        w = w1;
        h = h1;
        texture.loadFromFile("C:/Users/*****/Downloads/" + file);  //описываем класс
        sprite.setTexture(texture);
        x = x1;
        y = y1;
        sprite.setTextureRect(IntRect(w, h, w, h));
    }
    void update(float time)
    {
        switch (dir) {
        case 0: {    //случаи движения спрайта: 1 - вперед, 1 - вперед и вверх, 2 - вперед и вниз
            dx = speedx;
            dy = 0;
            break;
        }
        case 1: {
            dx = speedx;
            dy = speedy;
            break;
        }
        case 2: {
            dx = speedx;
            dy = -speedy;
            break;
        }
        }
        x += dx * time;
        y += dy * time;

        speedx = 0;  //зануляем скорости  по x и по y
        speedy = 0;

        sprite.setPosition(x, y);
        interactionWithMap();

    }

    void interactionWithMap() //ф-ция взаимодействия с картой
    {

        for (int i = y / 32; i < (y + h) / 32; i++)
            for (int j = x / 32; j < (x + w) / 32; j++) //икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
            {
                        if (Map[i][j] == '1') { //если символ равен 's' - звезда
                    ++score;
                    Map[i][j] = ' '; //убираем звезду, типа взяли бонус.
                }
            }
    }

  float playerCoordinateX() {
      return x;  //возвращаем координаты
   }
    float playerCoordinateY() {
  return y;
   }

};

int main()
{
    randomMapGenerate(); //подключаем функцию рандомной генерации

    Font font;
    font.loadFromFile("C:/Users/*****/Downloads/1942.ttf");  //зазгружаем шрифт для текста
    Text text1("", font, 50);
    //Text text2("", font, 50);

    Image map_image; //объект изображения для карты
    map_image.loadFromFile("C:/Users/*****/Downloads/_MAP_.png"); //загружаем файл для карты
    Texture map; //текстура карты
    map.loadFromImage(map_image); //заряжаем текстуру картинкой
    Sprite s_map; //создаём спрайт для карты
    s_map.setTexture(map); //заливаем текстуру спрайтом
    
    Texture background; //фоновое изображение
    background.loadFromFile("C:/Users/*****/Downloads/skyofmotherland (2).png");
    Sprite back;
    back.setTexture(background);
   
    camera.reset(sf::FloatRect(0, 0, 1920, 1080));   //камера вида
    Player p("Yakset.png", 200, 1000, 169, 45); // самолет (сам спрайт)

    Music fly;
    fly.openFromFile("C:/Users/*****/Downloads/MainAudio.ogg");  //звук летящего самолета
    fly.play(); 

    float Frame = 0;
    Clock clock;  //создаем класс типа Clock для работы со временем

    while (window.isOpen()) { 

        float time = clock.getElapsedTime().asMicroseconds();  //логика передвижения завязана на времени
        clock.restart();
        time = time / 4000;
        Event event;
        while (window.pollEvent(event)) {  //без этого ничего не будет работать:)
if (event.type == Event::Closed) //чтобы окно работало
                window.close();          
        } 
        if (Keyboard::isKeyPressed(Keyboard::D)) //если нажата кнопка
            {
            p.dir = 0; //один из случаев движения
            p.speedx = 1.4; //скорость движения
            Frame += 0.06 * time;   //скорость анимации
            if (Frame > 3) Frame = Frame - 3;
            p.sprite.setTextureRect(IntRect(169 * int(Frame), 45, 169, -45)); // проходимся по фото самолета
            p.sprite.setRotation(180); //угол поворота
           getplayercoordinateforview(p.playerCoordinateX(), p.playerCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
        {
            p.dir = 2;
            p.speedx = 1.4;
            p.speedy = 0.8;
            Frame += 0.001 * time;
            if (Frame > 3) Frame = Frame - 3;
            p.sprite.setTextureRect(IntRect(169 * int(Frame), 45, 169, -45));
            p.sprite.setRotation(172);
           getplayercoordinateforview(p.playerCoordinateX(), p.playerCoordinateY());
        }
        if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
        {
            p.dir = 1;
            p.speedx = 1.4;
            p.speedy = 0.8;
            Frame += 0.001 * time;
            if (Frame > 3) Frame = Frame - 3;
            p.sprite.setTextureRect(IntRect(169 * int(Frame), 45, 169, -45));
            p.sprite.setRotation(188);
            getplayercoordinateforview(p.playerCoordinateX(), p.playerCoordinateY());
        }
        
        p.update(time);  //setting time
        window.setView(camera);  
        window.clear();
        window.draw(back);
        for (int i = 0; i < hight; ++i)
            for (int j = 0; j < width; ++j)
            {
                if (Map[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 0, 0)); //если встретили символ пробел, то рисуем 1й квадратик          
                if ((Map[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
                if ((Map[i][j] == '1')) s_map.setTextureRect(IntRect(33, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик

                s_map.setPosition(j * 32, i * 32); //по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                window.draw(s_map);//рисуем квадратики на экран
            }

        text1.setString("STARS COLLECTED: " + std::to_string(p.score));
        text1.setPosition(camera.getCenter().x + 200, camera.getCenter().y - 500);
        window.draw(text1);//рисую этот текст

        //text2.setString("You Win!" + std::to_string(p.score));
        //text2.setPosition(camera.getCenter().x + 200, camera.getCenter().y - 600); 

        //if (p.score == 5) {
        //    window.draw(text2);
        //}
        window.draw(p.sprite);
        window.display();
    }
                                    
    return 0;
}
