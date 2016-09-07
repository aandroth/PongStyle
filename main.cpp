
#include "sfwdraw.h"
#include "Paddle.h"
#include "Ball.h"

Paddle playerPaddle, enemyPaddle;
Ball gameBall;
void collisionController(Paddle padd, Ball * ball);
bool paddleRightAndBallCollision(Paddle padd, Ball ball);
bool paddleLeftAndBallCollision(Paddle padd, Ball ball);
bool paddleTopAndBallCollision(Paddle padd, Ball ball);
bool paddleBottomAndBallCollision(Paddle padd, Ball ball);
bool paddleAndBallCollisionX(Paddle, Ball);
bool paddleAndBallCollisionY(Paddle, Ball);

bool gameIsActive = true;
unsigned playerPoints = 0;

void main()
{
	sfw::initContext(800, 600, "NSFW Draw");

	playerPaddle.texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	playerPaddle.xPos = 100;
	playerPaddle.yPos = 200;
	playerPaddle.width = 10;
	playerPaddle.height = 100;

	enemyPaddle.texture = sfw::loadTextureMap("./Images/Paddle.png", 10, 50);
	enemyPaddle.xPos = 700;
	enemyPaddle.yPos = 200;
	enemyPaddle.width = 10;
	enemyPaddle.height = 100;

	gameBall.xPos = 200;
	gameBall.yPos = 250;
	gameBall.xVel = 9;
	gameBall.yVel = 9;
	gameBall.radius = 10;
	gameBall.color = WHITE;

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

		if (enemyPaddle.yPos < gameBall.yPos)
		{
			enemyPaddle.yPos += 8;
			paddleAndBallCollisionY(enemyPaddle, gameBall);
		}
		else if (enemyPaddle.yPos - enemyPaddle.height > gameBall.yPos)
		{
			enemyPaddle.yPos -= 8;
			paddleAndBallCollisionY(enemyPaddle, gameBall);
		}

		if (sfw::getKey(KEY_UP) && playerPaddle.yPos < 600)
		{
			playerPaddle.yPos += 8;
			if (paddleAndBallCollisionY(playerPaddle, gameBall))
			{
				gameBall.yPos += 8;
				gameBall.yVel = abs(gameBall.yVel);
			}
		}
		else if(sfw::getKey(KEY_DOWN) && (playerPaddle.yPos - playerPaddle.height > 0))
		{
			playerPaddle.yPos -= 10;
			if (paddleAndBallCollisionY(playerPaddle, gameBall))
			{
				gameBall.yPos -= 10;
				gameBall.yVel = -(abs(gameBall.yVel));
			}
		}

		if (gameBall.xPos + gameBall.radius > 800)
		{
			gameBall.xVel = -gameBall.xVel;
		}
		else if (gameBall.xPos < 0)
		{
			//gameIsActive = false;
			gameBall.xVel = -gameBall.xVel;
		}
		
		if (paddleAndBallCollisionX(playerPaddle, gameBall) || paddleAndBallCollisionX(enemyPaddle, gameBall))
		{
			gameBall.xVel = -gameBall.xVel;
		}
		if(paddleAndBallCollisionY(playerPaddle, gameBall) ||
			(paddleAndBallCollisionY(enemyPaddle, gameBall) ||
			(gameBall.yPos + gameBall.radius >= ceilingValue) ||
				(gameBall.yPos - gameBall.radius <= floorValue)))
		{
			gameBall.yVel = -gameBall.yVel;
		}

		playerPoints += 1;
		sfw::drawString(font, std::to_string(playerPoints).c_str(), 0, 600, 48, 48, 0, ' ');

		gameBall.xPos += gameBall.xVel;
		gameBall.yPos += gameBall.yVel;
	}

	sfw::termContext();
}

void collisionController(Paddle padd, Ball * ball)
{
	if (paddleRightAndBallCollision)
	{
		ball->xVel = -ball->xVel;
		ball->xPos -= 10;
	}
	if (paddleLeftAndBallCollision)
	{
		ball->xVel = -ball->xVel;
		ball->xPos -= 10;
	}
	if (paddleRightAndBallCollision)
	{
		ball->xVel = -ball->xVel;
		ball->xPos -= 10;
	}
	if (paddleRightAndBallCollision)
	{
		ball->xVel = -ball->xVel;
		ball->xPos -= 10;
	}
}

bool paddleRightAndBallCollision(Paddle padd, Ball ball)
{
	if ((ball.xPos - ball.radius < padd.xPos + padd.width && ball.xPos - ball.radius > padd.xPos) &&
		((ball.yPos - ball.radius > padd.yPos - padd.height && ball.yPos - ball.radius < padd.yPos) || (ball.yPos + ball.radius > padd.yPos - padd.height && ball.yPos + ball.radius < padd.yPos)))
	{
		return true;
	}
	return false;
}

bool paddleLeftAndBallCollision(Paddle padd, Ball ball)
{
	if ((ball.xPos + ball.radius < padd.xPos + padd.width && ball.xPos + ball.radius > padd.xPos) &&
		((ball.yPos - ball.radius > padd.yPos - padd.height && ball.yPos - ball.radius < padd.yPos) || (ball.yPos + ball.radius > padd.yPos - padd.height && ball.yPos + ball.radius < padd.yPos)))
	{
		return true;
	}
	return false;
}

bool paddleTopAndBallCollision(Paddle padd, Ball ball)
{
	if ((padd.yPos < ball.yPos + ball.radius && padd.yPos > ball.yPos - ball.radius) &&
		((padd.xPos > ball.xPos - ball.radius && padd.xPos < ball.xPos + ball.radius) || (padd.xPos + padd.width > ball.xPos - ball.radius && padd.xPos + padd.width < ball.xPos + ball.radius)))
	{
		return true;
	}
	return false;
}

bool paddleBottomAndBallCollision(Paddle padd, Ball ball)
{
	if ((padd.yPos - padd.height < ball.yPos + ball.radius && padd.yPos - padd.height > ball.yPos - ball.radius) &&
		((padd.xPos > ball.xPos - ball.radius && padd.xPos < ball.xPos + ball.radius) || (padd.xPos + padd.width > ball.xPos - ball.radius && padd.xPos + padd.width < ball.xPos + ball.radius)))
	{
		return true;
	}
	return false;
}



bool paddleAndBallCollisionX(Paddle padd, Ball ball)
{
	// Detect if the ball hit the front face of the paddle

	if (((gameBall.yPos + gameBall.radius >= padd.yPos - padd.height && gameBall.yPos + gameBall.radius <= padd.yPos) || // Ball top is between y's of paddle
		(gameBall.yPos - gameBall.radius >= padd.yPos - padd.height && gameBall.yPos - gameBall.radius <= padd.yPos)) && // Ball bottom is between y's of paddle
		((gameBall.xPos - gameBall.radius <= padd.xPos + padd.width && gameBall.xPos - gameBall.radius >= padd.xPos) || // Ball left is between x's of paddle
		(gameBall.xPos + gameBall.radius <= padd.xPos + padd.width && gameBall.xPos + gameBall.radius >= padd.xPos)))    // Ball right is between x's of paddle
	{
		return true;
	}
	return false;
}

bool paddleAndBallCollisionY(Paddle padd, Ball ball)
{
	// Detect if the ball hit the top or bottom face of the paddle
	if (((padd.xPos >= gameBall.xPos - gameBall.radius && padd.xPos <= gameBall.xPos + gameBall.radius) || // Ball top is between y's of paddle
		(padd.xPos + padd.width >= gameBall.xPos - gameBall.radius && padd.xPos + padd.width <= gameBall.xPos + gameBall.radius)) && // Ball bottom is between y's of paddle
		((padd.yPos >= gameBall.yPos - gameBall.radius && padd.yPos <= gameBall.yPos + gameBall.radius) || // Ball top is between y's of paddle
		(padd.yPos - padd.height >= gameBall.yPos - gameBall.radius && padd.yPos - padd.height <= gameBall.yPos + gameBall.radius)))    // Ball right is between x's of paddle
	{
		return true;
	}

	return false;
}