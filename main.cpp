
#include "sfwdraw.h"
#include "Paddle.h"
#include "Ball.h"
#include "Collision.h"

Paddle playerPaddle, enemyPaddle;
Ball gameBall;
bool gameIsActive = true;
unsigned playerPoints = 0;

void main()
{
	sfw::initContext(800, 600, "NSFW Draw");

	unsigned ceilingValue = 600, floorValue = 10;

	float acc = 0;
	char c = '\0';

	sfw::setBackgroundColor(BLACK);

	while (gameIsActive && sfw::stepContext())
	{
		sfw::drawTexture(playerPaddle.texture, playerPaddle.xPos, playerPaddle.yPos, playerPaddle.width, playerPaddle.height, 0, false, 0, WHITE);
		sfw::drawTexture(enemyPaddle.texture, enemyPaddle.xPos, enemyPaddle.yPos, enemyPaddle.width, enemyPaddle.height, 0, false, 0, RED);
		sfw::drawCircle(gameBall.xPos, gameBall.yPos, gameBall.radius, 12, gameBall.color);

		unsigned font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
		playerPoints += 1;
		sfw::drawString(font, std::to_string(playerPoints).c_str(), 0, 600, 48, 48, 0, ' ');

		// Move Enemy paddle
		if (enemyPaddle.yPos < gameBall.yPos)
		{
			enemyPaddle.moveUp(ceilingValue);
		}
		else if (enemyPaddle.yPos - enemyPaddle.height > gameBall.yPos)
		{
			enemyPaddle.moveDown(floorValue);
		}

		// Move Player paddle
		if (sfw::getKey(KEY_UP))
		{
			playerPaddle.moveUp(ceilingValue);
		}
		else if(sfw::getKey(KEY_DOWN))
		{
			playerPaddle.moveDown(floorValue);
		}

		paddleCollisionController(playerPaddle, &gameBall);
		paddleCollisionController(enemyPaddle, &gameBall);
		boundaryCollisionController(&gameBall, ceilingValue, floorValue);

		gameBall.xPos += gameBall.xVel;
		gameBall.yPos += gameBall.yVel;
	}

	sfw::termContext();
}