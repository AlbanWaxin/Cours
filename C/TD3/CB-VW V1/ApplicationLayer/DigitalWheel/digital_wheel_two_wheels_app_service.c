#include <stdlib.h>
#include "instantiate.h"
#include "digital_wheel_two_wheels_app_service.h"

struct twoWheels
{
    digital_wheel wheel1;
    digital_wheel wheel2;
};

twoWheels DigitalWheelAppService_two_wheels_construct(int debut, int fin)
{
    INSTANTIATE(twoWheels);
    self->wheel1 = DigitalWheel_construct(debut,fin);
    self->wheel2 = DigitalWheel_construct(debut,fin);
    return self;
}

void DigitalWheelAppService_two_wheels_collect(twoWheels self)
{
    DigitalWheel_collect(self->wheel1);
    DigitalWheel_collect(self->wheel2);
    free(self);
}

void DigitalWheelAppService_two_wheels_initialize(twoWheels self)
{
    DigitalWheel_initialize(self->wheel1);
    DigitalWheel_initialize(self->wheel2);
}

void DigitalWheelAppService_two_wheels_move(twoWheels self, int wheel_speed1, int wheel_speed2)
{
    for (int i = 0; i < wheel_speed1; i++)
    {
     DigitalWheel_move_to_next_position(self->wheel1);
    }
    for (int i = 0; i < wheel_speed2; i++)
    {
     DigitalWheel_move_to_next_position(self->wheel2);
    }
    
}

static void display(digital_wheel wheel, void (*f)(int))
{
    f(DigitalWheel_get_current_position(wheel));
}

void DigitalWheelAppService_two_wheels_display(twoWheels self,void (*f)(int))
{
    display(self->wheel1,f);
    display(self->wheel2,f);   
}


