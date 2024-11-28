#include "Hero.h"
#include "data/DataCenter.h"//控制螢幕
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"

namespace HeroSetting {
	static constexpr char gif_root_path[50] = "./assets/gif/Hero";
	static constexpr char gif_postfix[][10] = {
		"left", "back", "front", "right"
	};
}

void Hero::init()
{
    for(size_t type=0;type<static_cast<size_t>(HeroState::HEROSTATE_MAX);++type)
    {
        char buffer[50];
        sprintf(buffer,"%s/dragonite_%s.gif",
                HeroSetting::gif_root_path,
                HeroSetting::gif_postfix[static_cast<int>(type)]);
        gifPath[static_cast<HeroState>(type)] = std::string{buffer};       
    }
    DataCenter *DC = DataCenter::get_instance();
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    shape.reset(new Rectangle{DC->window_width/2,
                              DC->window_height/2,
                              DC->window_width/2+gif->width,
                              DC->window_height/2+gif->height,
                             }       
               );                        
}


void Hero::draw()
{
    //below is to load gif from GIFCneter
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    algif_draw_gif(gif,
                   shape->center_x()-gif->width/2,
                   shape->center_y()-gif->height/2,
                   0
                 );//flip->圖片翻轉
}

void Hero::update()
{
    DataCenter *DC = DataCenter::get_instance();
    if(DC->key_state[ALLEGRO_KEY_W])
    {
        shape->update_center_y(shape->center_y()-speed);
        state = HeroState::BACK;
    }
    else if(DC->key_state[ALLEGRO_KEY_A])
    {
        shape->update_center_x(shape->center_x()-speed);
        state = HeroState::LEFT;
    }
    else if(DC->key_state[ALLEGRO_KEY_S])
    {
        shape->update_center_y(shape->center_y()+speed);
        state = HeroState::FRONT;
    }
        if(DC->key_state[ALLEGRO_KEY_D])
    {
        shape->update_center_x(shape->center_x()+speed);
        state = HeroState::RIGHT;
    }
}



