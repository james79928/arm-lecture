#include "game.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
//Player1
int16_t player1X = 10;
int16_t player1Y = 10;
uint16_t player1W = 60;
uint16_t player1H = 10;
uint8_t player1IsReversed = 1;

//Player2
int16_t player2X = LCD_PIXEL_WIDTH - 20;
int16_t player2Y = LCD_PIXEL_HEIGHT - 20;
uint16_t player2W = 60;
uint16_t player2H = 10;
uint8_t player2IsReversed = 0;

//Ball
uint16_t ballSize = 5;
int16_t ballX = ( LCD_PIXEL_WIDTH - 5 )/2;
int16_t ballY = ( LCD_PIXEL_HEIGHT - 5 )/2;
int16_t ballVX = 5;
int16_t ballVY = 5;
uint8_t ballIsRun = 0;

//Mode
uint8_t demoMode = 0;
#endif

typedef enum turn_around{
	right ,
	left ,
	up ,
	down ,
};

int body;
//srand(time(NULL));

typedef struct Snake{
	int16_t x;
	int16_t y;
	enum turn_around direction;
	enum turn_around pre_direction;	
	struct Snake *next;
};

struct{
	int16_t x;
	int16_t y;
}dot = {0 , 0}; 

int8_t first = 1;
struct Snake snake = {0 , 0 , 0 , 0 , NULL};
struct Snake *snakep = &snake , *snake_tmp;
int body = 1;
enum turn_around enable;
int8_t repeat = 1;

void
add_snake()
{
	struct Snake *p , *tmp;
	for(p = snakep ; p ; p = p->next)
		tmp = p;
	p = (struct Snake*)pvPortMalloc(sizeof(struct Snake));
	switch(tmp->direction){
		case right:
			p->x = tmp->x-ballVX;
			p->y = tmp->y;
			p->direction = tmp->direction;
			p->pre_direction = tmp->pre_direction;
			p->next = NULL;
			tmp->next = p;
			break;
		case left:
			p->x = tmp->x+ballVX;
			p->y = tmp->y;
			p->direction = tmp->direction;
			p->pre_direction = tmp->pre_direction;
			p->next = NULL;
			tmp->next = p;
			break;
		case up:
			p->x = tmp->x;
			p->y = tmp->y+ballVY;
			p->direction = tmp->direction;
			p->pre_direction = tmp->pre_direction;
			p->next = NULL;
			tmp->next = p;
			break;
		case down:
			p->x = tmp->x;
			p->y = tmp->y-ballVY;
			p->direction = tmp->direction;
			p->pre_direction = tmp->pre_direction;
			p->next = NULL;
			tmp->next = p;
			break;
	}
	
}

void
BallReset()
{
#if 0
	ballX = ( LCD_PIXEL_WIDTH - 5 ) / 2;
	ballY = ( LCD_PIXEL_HEIGHT - 5 ) / 2;

	ballVX = 5;
	ballVY = 5;

	ballIsRun = 1;
#endif
}

void
GAME_EventHandler1()
{
	if( STM_EVAL_PBGetState( BUTTON_USER ) ){

//		player1IsReversed = 0;
                player2IsReversed = 1;
		enable = down;

		while( STM_EVAL_PBGetState( BUTTON_USER ) );
           	player2IsReversed = 0;

//		player1IsReversed = 1;
	}
}

void
GAME_EventHandler2()
{
//	if( IOE_TP_GetState()->TouchDetected ){
	if( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6) ){
		
		snake_tmp = snakep;
		snake_tmp->direction = right;
//		player2IsReversed = 1;

//		while( IOE_TP_GetState()->TouchDetected );
		while( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6) )
			player2IsReversed = 0;
	}
}

void
GAME_EventHandler3()
{
	if( ballIsRun == 0 ){
		BallReset();
	}
}


#if 0
void
GAME_EventHandler4()
{
	//RCC_ClocksTypeDef RCC_Clocks;
	//uint8_t togglecounter = 0x00;

  	while(1)
  	{    
      		/* Toggle LED5 */
      		STM_EVAL_LEDToggle(LED3);
      		vTaskDelay(100);
      		STM_EVAL_LEDToggle(LED4);
      		vTaskDelay(100);
  	}
}
#endif

void
GAME_EventHandler5()
{

	if( GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) ){
                player2IsReversed = 1;
		enable = right;
                while( GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) );
               		 player2IsReversed = 0;
        }
#if 1
	if( GPIO_ReadInputDataBit(GPIOE ,GPIO_Pin_3) ){
                player2IsReversed = 1;
		enable = left;
                while( GPIO_ReadInputDataBit(GPIOE ,GPIO_Pin_3) );
               		 player2IsReversed = 0;
	}
#endif
	if( GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) ){
                player2IsReversed = 1;
		enable = up;
                while( GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) );
               		 player2IsReversed = 0;
        }
	if( GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) ){
                player2IsReversed = 1;
		enable = down;
                while( GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) );
               		 player2IsReversed = 0;
        }

}
#if 0
void
GAME_EventHandler6()
{
	if( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) ){
                player2IsReversed = 1;
		enable = left;
                while( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) );
               		 player2IsReversed = 0;
        }
}
void
GAME_EventHandler7()
{
	if( GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) ){
                player2IsReversed = 1;
		enable = up;
                while( GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8) );
               		 player2IsReversed = 0;
        }
}
#endif
#if 0
void
GAME_EventHandler8()
{
	if( GPIO_ReadInputDataBit(GPIOC ,GPIO_Pin_13) ){
                player2IsReversed = 1;
		enable = down;
                while( GPIO_ReadInputDataBit(GPIOC ,GPIO_Pin_13) );
               		 player2IsReversed = 0;
        }
}
#endif
//int color1 = LCD_COLOR_WHITE;
//int color2 = LCD_COLOR_WHITE;

void
GAME_Update()
{
#if 0
	//Player1
	LCD_SetTextColor( LCD_COLOR_BLACK );
	LCD_DrawFullRect( player1X, player1Y, player1W, player1H );
	LCD_DrawFullRect( player2X, player2Y, player2W, player2H );

	if( demoMode == 0 ){

		if( player1IsReversed )
			player1X -= 5;
		else
			player1X += 5;

		if( player1X <= 0 )
			player1X = 0;
		else if( player1X + player1W >= LCD_PIXEL_WIDTH )
			player1X = LCD_PIXEL_WIDTH - player1W;

		//Player2
		if( player2IsReversed )
			player2X -= 5;
		else
			player2X += 5;

		if( player2X <= 0 )
			player2X = 0;
		else if( player2X + player2W >= LCD_PIXEL_WIDTH )
			player2X = LCD_PIXEL_WIDTH - player2W;

		//Ball
		if( ballIsRun == 1 ){

			LCD_SetTextColor( LCD_COLOR_BLACK );
			LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

			//Touch wall
			ballX += ballVX;
			if( ballX <= 0 ){
				ballX = 0;
				ballVX *= -1;
			}
			else if( ballX + ballSize >= LCD_PIXEL_WIDTH ){
				ballX = LCD_PIXEL_WIDTH - ballSize;
				ballVX *= -1;
			}

			//PONG!
			ballY += ballVY;
			if( ballY + ballSize >= player2Y ){
				if( ballX + ballSize >= player2X && ballX <= player2X + player2W ){
					color1 = LCD_COLOR_RED;
					if( ballX - ballSize <= player2Y + player2W/4 ){
						ballVY =-3;
						ballVX =-7;
					}
					else if( ballX >= player2Y + player2W - player2W/4 ){
						ballVY =-3;
						ballVX = 7;
					}
					else if( ballX + ballSize < player2Y + player2W/2 ){
						ballVY =-7;
						ballVX =-3;
					}
					else if( ballX > player2Y + player2W/2 ){
						ballVY =-7;
						ballVX = 3;
					}
					else{
						ballVY =-9;
						ballVX = 0;
					}
				}
				else{
					
					color1 = color2 = LCD_COLOR_WHITE;
					BallReset();
				}
			}

			if( ballY <= player1Y + player1H ){
					if( ballX + ballSize >= player1X && ballX <= player1X + player1W ){
					color2 = LCD_COLOR_BLUE;
						if( ballX - ballSize <= player1Y + player1W/4 ){
							ballVY = 3;
							ballVX =-7;
						}
						else if( ballX >= player1Y + player1W - player1W/4 ){
							ballVY = 3;
							ballVX = 7;
						}
						else if( ballX + ballSize < player1Y + player1W/2 ){
							ballVY = 7;
							ballVX =-3;
						}
						else if( ballX > player1Y + player1W/2 ){
							ballVY = 7;
							ballVX = 3;
						}
						else{
							ballVY = 9;
							ballVX = 0;
						}
					}
					else{
						color1 = color2 = LCD_COLOR_WHITE;
						BallReset();
					}
				}
			}
		}
		else{	//if demoMode == 1

			//Player1 move
			if( ballVY < 0 ){
				if( player1X + player1W/2 < ballX + ballSize/2 ){
					player1X += 8;
					player2X += 2;
				}
				else{
					player1X -= 8;
					player2X -= 2;
				}
			}

			//Player2 move
			if( ballVY > 0 ){
				if( player2X + player2W/2 < ballX + ballSize/2 ){
					player1X += 2;
					player2X += 8;
				}
				else{
					player1X -= 2;
					player2X -= 8;
				}

			}

			if( player1X <= 0 )
				player1X = 0;
			else if( player1X + player1W >= LCD_PIXEL_WIDTH )
				player1X = LCD_PIXEL_WIDTH - player1W;

			if( player2X <= 0 )
				player2X = 0;
			else if( player2X + player2W >= LCD_PIXEL_WIDTH )
				player2X = LCD_PIXEL_WIDTH - player2W;


			//Ball
			if( ballIsRun == 1 ){

				LCD_SetTextColor( LCD_COLOR_BLACK );
				LCD_DrawFullRect( ballX, ballY, ballSize, ballSize );

				//Touch wall
				ballX += ballVX;
				if( ballX <= 0 ){
					ballX = 0;
					ballVX *= -1;
				}
				else if( ballX + ballSize >= LCD_PIXEL_WIDTH ){
					ballX = LCD_PIXEL_WIDTH - ballSize;
					ballVX *= -1;
				}

				//PONG!
				ballY += ballVY;
				if( ballY + ballSize >= player2Y ){
					if( ballX + ballSize >= player2X && ballX <= player2X + player2W ){
					if( ballX - ballSize <= player2Y + player2W/4 ){
						ballVY =-3;
						ballVX =-7;
					}
					else if( ballX >= player2Y + player2W - player2W/4 ){
						ballVY =-3;
						ballVX = 7;
					}
					else if( ballX + ballSize < player2Y + player2W/2 ){
						ballVY =-7;
						ballVX =-3;
					}
					else if( ballX > player2Y + player2W/2 ){
						ballVY =-7;
						ballVX = 3;
					}
					else{
						ballVY =-9;
						ballVX = 0;
					}
				}
				else
					BallReset();
			}

			if( ballY <= player1Y + player1H ){
				if( ballX + ballSize >= player1X && ballX <= player1X + player1W ){
					if( ballX - ballSize <= player1Y + player1W/4 ){
						ballVY = 3;
						ballVX =-7;
					}
					else if( ballX >= player1Y + player1W - player1W/4 ){
						ballVY = 3;
						ballVX = 7;
					}
					else if( ballX + ballSize < player1Y + player1W/2 ){
						ballVY = 7;
						ballVX =-3;
					}
					else if( ballX > player1Y + player1W/2 ){
						ballVY = 7;
						ballVX = 3;
					}
					else{
						ballVY = 9;
						ballVX = 0;
					}
				}
				else
					BallReset();
			}
		}
	}
#endif
if(repeat){
	uint32_t rand = RNG_GetRandomNumber();	
	if(first){
		dot.x = (rand%(LCD_PIXEL_WIDTH/ballSize))*ballSize+2;
		dot.y = (rand%(LCD_PIXEL_HEIGHT/ballSize))*ballSize+2;
//		dot.x = ( LCD_PIXEL_WIDTH )/2+2;
		snake.x = ( LCD_PIXEL_WIDTH )/2;
		snake.y = ( LCD_PIXEL_HEIGHT )/2;
		snake.direction = RNG_GetRandomNumber()%4;
		snake.pre_direction = snake.direction;
		first = 0;	 
	}

	if((snakep->x+2 == dot.x) && (snakep->y+2 == dot.y)){
		add_snake();
		body++;
		LCD_SetTextColor( LCD_COLOR_BLACK );
		LCD_DrawFullCircle( dot.x, dot.y, 2 );			
//		dot.x = (RNG_GetRandomNumber()%(LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT))%LCD_PIXEL_WIDTH;
//		dot.y = (RNG_GetRandomNumber()%(LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT))/LCD_PIXEL_HEIGHT;
		dot.x = (rand%(LCD_PIXEL_WIDTH/ballSize))*ballSize+2;
		dot.y = (rand%(LCD_PIXEL_HEIGHT/ballSize))*ballSize+2;
//		dot.y = ( LCD_PIXEL_HEIGHT )/2+2;
	} 
#if 0
		//Player2
		if( player2IsReversed )
			player2X -= 5;
		else
			player2X += 5;
#endif
	for(snake_tmp = snakep ; snake_tmp ; snake_tmp = snake_tmp->next)
		snake_tmp->pre_direction = snake_tmp->direction;
	for(snake_tmp = snakep ; snake_tmp ; snake_tmp = snake_tmp->next)
		if(snake_tmp->next)
			snake_tmp->next->direction = snake_tmp->pre_direction;
	//Player2
	if( player2IsReversed ){
//		enable = right;	
		switch(enable){
			case right:
				(snakep->direction == left)?(snakep->direction=left):(snakep->direction=right);
				break;
			case left:
				(snakep->direction == right)?(snakep->direction=right):(snakep->direction=left);
				break;
			case up:
				(snakep->direction == down)?(snakep->direction=down):(snakep->direction=up);
				break;
			case down:
				(snakep->direction == up)?(snakep->direction=up):(snakep->direction=down);
				break;
		}
	}
//		snakep->direction = right;
	LCD_SetTextColor( LCD_COLOR_BLACK );
//	LCD_DrawFullRect( snake.x, snake.y-(body-1)*ballSize, ballSize, ballSize );		//配合上面LCD_SetTextColor function把前一個畫的矩形用黑色（背景颜色）蓋掉
	uint16_t clear_x;
	uint16_t clear_y;
	for(snake_tmp = snakep ; snake_tmp ; snake_tmp = snake_tmp->next){
//		snake_tmp->pre_direction = snake_tmp->direction;
//		if(snake_tmp->next)
//			snake_tmp->next->direction = snake_tmp->pre_direction;
		switch(snake_tmp->direction){
			case right:
				ballVX = 5;
				ballVY = 0;
				snake_tmp->x += ballVX;										//ballVX:positive-->right
				clear_x = snake_tmp->x-ballSize;
				clear_y = snake_tmp->y;
				break;
			case left:
				ballVX = 5;
				ballVY = 0;
				snake_tmp->x -= ballVX;										//ballVX:negative-->left
				clear_x = snake_tmp->x+ballSize;
				clear_y = snake_tmp->y;
				break;
			case up:
				ballVY = 5;
				ballVX = 0;
				snake_tmp->y -= ballVY;										//ballVX:negative-->up
				clear_x = snake_tmp->x;
				clear_y = snake_tmp->y+ballSize;
				break;
			case down:
				ballVY = 5;
				ballVX = 0;
				snake_tmp->y += ballVY;										//ballVX:positive-->down
				clear_x = snake_tmp->x;
				clear_y = snake_tmp->y-ballSize;
				break;
		}
	}
	LCD_DrawFullRect( clear_x, clear_y, ballSize, ballSize );			
	

	for(snake_tmp = snakep ; snake_tmp ; snake_tmp = snake_tmp->next){
		if( snake_tmp->x < 0 ){							
			snake_tmp->x = LCD_PIXEL_WIDTH - ballSize;
		}
		else if( snake_tmp->x + ballSize > LCD_PIXEL_WIDTH ){
			snake_tmp->x = 0;
		}

		if( snake_tmp->y < 0 ){
			snake_tmp->y = LCD_PIXEL_HEIGHT - ballSize;
		}
		else if( snake_tmp->y + ballSize > LCD_PIXEL_HEIGHT ){
			snake_tmp->y = 0;
		}
	}

	for(snake_tmp = snakep->next ; snake_tmp ; snake_tmp = snake_tmp->next){
		if((snakep->x == snake_tmp->x) &&(snakep->y == snake_tmp->y)){
			repeat = 0;
			break;
		}
	}

}
#if 0
	LCD_SetTextColor( LCD_COLOR_BLACK );
	LCD_DrawFullRect( ballX, ballY-(body-1)*ballSize, ballSize, ballSize );					//配合上面LCD_SetTextColor function把前一個畫的矩形用黑色（背景颜色）蓋掉
	enum turn_around turn = down;
	switch(turn){
		case right:
			ballX += ballVX;							//ballVX:positive-->right
			ballVY = 0;
			break;
		case left:
			ballX -= ballVX;							//ballVX:negative-->left
			ballVY = 0;
			break;
		case up:
			ballY -= ballVY;							//ballVX:negative-->up
			ballVX = 0;
			break;
		case down:
			ballY += ballVY;							//ballVX:positive-->down
			ballVX = 0;
			break;
	}
	
	if( ballX <= 0 ){							
		ballX = LCD_PIXEL_WIDTH - ballSize;
	}
	else if( ballX + ballSize >= LCD_PIXEL_WIDTH ){
		ballX = 0;
	}

	if( ballY <= 0 ){
		ballY = LCD_PIXEL_HEIGHT - ballSize;
	}
	else if( ballY + ballSize >= LCD_PIXEL_HEIGHT ){
		ballY = 0;
	}
#endif
}

void
GAME_Render()
{
#if 0
	int i;
	for(i = 0 ; i < body ; i++){
		if(i == 0)
			LCD_SetTextColor( LCD_COLOR_GREEN );
		else
			LCD_SetTextColor( LCD_COLOR_RED );
			LCD_DrawFullRect( ballX, ballY-i*ballSize, ballSize, ballSize );
	}
	LCD_SetTextColor( LCD_COLOR_WHITE );
	LCD_DrawFullCircle( dot.x, dot.y, 1);
#endif
	int i;
	struct Snake *p = snakep;
	for(i = 0 ; p ; i++){
		if(i == 0){
			LCD_SetTextColor( LCD_COLOR_GREEN );
			LCD_DrawFullRect( p->x, p->y, ballSize, ballSize );
		}
		else{
			LCD_SetTextColor( LCD_COLOR_RED );
			LCD_DrawFullRect( p->x, p->y, ballSize, ballSize );
		}
//		LCD_DrawFullRect( p->x, p->y, ballSize, ballSize );
		p = p->next;
	}
	LCD_SetTextColor( LCD_COLOR_WHITE );
	LCD_DrawFullCircle( dot.x, dot.y, 2);
//	LCD_SetTextColor( LCD_COLOR_BLUE );
//      LCD_DrawFullRect( player2X, player2Y, player2W, player2H );

}

#if 0
GAME_Render_Dot()
{

	LCD_SetTextColor( LCD_COLOR_WHITE );
	LCD_DrawFullCircle( dot_x, dot_y, 1);
}
#endif
