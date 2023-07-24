#include <stdio.h>
typedef struct {
 int temperature;
 double windSpeed;
} weather_t;
void populate(weather_t *weather) {
 int weatherTemp = 5;
 weather->temperature = weatherTemp;
 weather->windSpeed = 50.2;
}
int main(void) {
 weather_t weather;
 populate(&weather);
 printf("%.2f", weather.windSpeed);
 return 0;
}
