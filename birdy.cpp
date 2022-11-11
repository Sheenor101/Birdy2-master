// include the raylib library
#include "raylib.h"

// defining the struct/group
struct Anim
{
	Rectangle rec; 
	Vector2 pos;
	int frame; 
	float updateTime; 
	float runningTime;  
};

//main entry point
int main(){
//specifying the variables value - const int - it cannot be modified by programmer later on
 const int windowWidth{700};
 const int windowHeight{450};
 //initialise the game window along with height, width and name
InitWindow(windowWidth,windowHeight,"Birdy");
//Inialise music
InitAudioDevice();


// load the different textures that will be used in the game
Texture2D obstacle = LoadTexture("resources/Drone.png");
Texture2D birdy = LoadTexture("resources/birdy.png");
Texture2D sky = LoadTexture("resources/sky.png");

//Defining the birdy ainimation
Anim birdyAnim;
////the rectangle that the birdy texture is in should be the width of the texture/6 (6 frames in texture)
birdyAnim.rec.width = birdy.width/6;
//height of rectangle should be same as birdy texture height 
birdyAnim.rec.height = birdy.height;

birdyAnim.rec.x = 0;
birdyAnim.rec.y = 0;
//starting position of bird - x axis
birdyAnim.pos.x = windowWidth/6 - birdyAnim.rec.width/6;
//starting position of bird - y axis
birdyAnim.pos.y = windowHeight/2 - birdyAnim.rec.height/2;
// starting frame for birdy
birdyAnim.frame = 0;
//how quickly the frames change
birdyAnim.updateTime = 1.0/12.0;
birdyAnim.runningTime = 0.0;

//defining the rectangle of the obstacle drone
Rectangle obRec;
//rectangle should be same width as drone
obRec.width = obstacle.width;
//rectangle should be same height as drone
obRec.height = obstacle.height; 
//position of rectangle on x and y axis
obRec.x = 0;
obRec.y = 0;

//defines the drone's x and y vector for position and speed
Vector2 obPos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }; 
Vector2 obSpeed = { 5.0f, 4.0f };




//defining the rectangle for the background sky
Rectangle skyRec;
//defining the width and height of the rectangle that the background will be in
skyRec.width = sky.width*10;
skyRec.height = sky.height;
//the starting position on x and y axis of the background rectangle
skyRec.x = 0;
skyRec.y = 0;
//Defining the sky position on x and y axis
Vector2 skyPos;
skyPos.x = windowWidth/2 - skyRec.width/2;
skyPos.y = windowHeight - skyRec.height;

//defining velocity integer for drone
int obVel{0};
//defining speed integer
int speed {400};
// defining velocity
int velocity{0};
// defining the boolean for collision
bool collision{};

// load the misuc from the resource file
Music music = LoadMusicStream("resources/Music.wav");
//play the music
PlayMusicStream(music);

//set the frame rate per second for the game
SetTargetFPS(60); 

//while loop for window showing what should happen while it's open
while(!WindowShouldClose()){

// Get time in seconds for last frame drawn (delta time). Constant - cannot be changed
const float deltaTime{GetFrameTime()};

// have music play in a loop
UpdateMusicStream(music);

// defining the rectangle for the drone 
Rectangle obstacleRec{
		obPos.x,
		obPos.y,
		obRec.height,
		obRec.width,
	
	};
	//defining the rectangle for the birdy
Rectangle birdyRec{
	birdyAnim.pos.x,
	birdyAnim.pos.y,
	birdyAnim.rec.height,
	birdyAnim.rec.width	
	};



// if key D is pressed,
	if(IsKeyDown(KEY_D))
{
	//the bird is moving right
	birdyAnim.pos.x += speed*deltaTime;
	// The bird changes facing direction
	birdyAnim.rec.width = birdy.width/6;
// adding frame time onto the running time
	birdyAnim.runningTime += deltaTime; 
	// if statement to Limit the frame cycle rate/speed of flaps
	if(birdyAnim.runningTime >= birdyAnim.updateTime)
	{
	birdyAnim.runningTime = 0.0;
	// changes to next frame as bird is moving
	birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;
	// if the birdy frame number is greater than 5 (the last frame), then it goes back to the first frame
	birdyAnim.frame++;
	if (birdyAnim.frame>5){
	birdyAnim.frame = 0;
	}

	}
}
//once the key D is released, the frames stop at frame 2
if(IsKeyReleased(KEY_D))
{birdyAnim.frame = 2;
birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;}

// if key a is pressed,
if(IsKeyDown(KEY_A))
{
	//the bird is moving left
	birdyAnim.pos.x -= speed*deltaTime;
	// The bird changes facing direction
	birdyAnim.rec.width = -birdy.width/6;
// adding frame time onto the running time
	birdyAnim.runningTime += deltaTime; 
	// if statement to Limit the frame cycle rate/speed of flaps
	if(birdyAnim.runningTime >= birdyAnim.updateTime)
	{
	birdyAnim.runningTime = 0.0;
	//makes bird flap
	birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;
	//cycles through each frame of bird texture
	birdyAnim.frame++;
	// if the birdy frame number is greater than 5 (the last frame), then it goes back to the first frame
	if (birdyAnim.frame>5){
	birdyAnim.frame = 0;
	}

	}
}
//once the key A is released, the frames stop at frame 3
if(IsKeyReleased(KEY_A))
{birdyAnim.frame = 3;
birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;}

//Same as above, only to move "up" when W is pressed
if(IsKeyDown(KEY_W))
{
	birdyAnim.pos.y -= speed*deltaTime;
	birdyAnim.rec.width = -birdy.width/6;

	birdyAnim.runningTime += deltaTime; 
	if(birdyAnim.runningTime >= birdyAnim.updateTime)
	{
	birdyAnim.runningTime = 0.0;
	birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;
	birdyAnim.frame++;
	if (birdyAnim.frame>5){
	birdyAnim.frame = 0;
	}

	}
}
//once the key W is released, the frames stop at frame 4
if(IsKeyReleased(KEY_W))
{birdyAnim.frame = 4;
birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;}

//Same as Above, only to move "down" when S is pressed
if(IsKeyDown(KEY_S))
{
	birdyAnim.pos.y += speed*deltaTime;
	birdyAnim.rec.width = -birdy.width/6;

	birdyAnim.runningTime += deltaTime; 
	if(birdyAnim.runningTime >= birdyAnim.updateTime)
	{
	birdyAnim.runningTime = 0.0;
	birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;
	birdyAnim.frame++;
	if (birdyAnim.frame>5){
	birdyAnim.frame = 0;
	}

	}
}
//once the key S is released, the frames stop at frame 5
if(IsKeyReleased(KEY_S))
{birdyAnim.frame = 5;
birdyAnim.rec.x = birdyAnim.frame* birdyAnim.rec.width;}

// Bouncing drone logic - I'm not too sure excatly what these mean as I copied the code from the raylib examples
        obPos.x += obSpeed.x;
        obPos.y += obSpeed.y;
        if ((obPos.x >= (GetScreenWidth() - obRec.width)) || (obPos.x <= obRec.width)) obSpeed.x *= -1.0f;
        if ((obPos.y >= (GetScreenHeight() - obRec.height)) || (obPos.y <= obRec.height)) obSpeed.y *= -1.0f;


//check if a collision happens between birdy and drone
	if(CheckCollisionRecs(birdyRec,obstacleRec)){
		collision = true;
	}
// Setup canvas (framebuffer) to start drawing  
BeginDrawing();



//posY += velocity;
birdyAnim.pos.y += velocity * deltaTime; 
obPos.x += obVel * deltaTime; 

// Set background colour
ClearBackground(WHITE); 


// if statement - if there is a collision, write "birdy died" on screen and animate a red birdy falling	
if (collision){DrawText("Birdy Died!!",290,200,30,BLACK);
	// animate dead birdy dropping until off screen
if(birdyAnim.pos.y <= (GetScreenHeight())){
// draw dead birdy "red" 
DrawTextureRec(birdy,birdyAnim.rec,birdyAnim.pos,RED);
// draw obstacle white
DrawTextureRec(obstacle,obRec,obPos,WHITE);
//birdy drops down 1  - slowly
birdyAnim.pos.y += 1;}
	}
// if there is no collision...
	else{


//draw each image/texture to the screeen. the background goes first, i discovered
DrawTextureRec(sky, skyRec,skyPos, WHITE); skyPos.x -= 1;
DrawTextureRec(birdy,birdyAnim.rec,birdyAnim.pos,WHITE);
DrawTextureRec(obstacle,obRec,obPos,WHITE);

// draw rectangles around both Birdy and Drone 
DrawRectangleLines(obPos.x, obPos.y, obRec.width, obRec.height, BLACK);
DrawRectangleLines(birdyAnim.pos.x, birdyAnim.pos.y, birdyRec.width, birdyRec.height, BLACK);

// Writes text on the screen
DrawText("Save Birdy from the Drone!",10,10,12,DARKGRAY);
	}
// End canvas drawing   
EndDrawing();
}
//Unloads each texture to save memory
UnloadTexture(birdy);
UnloadTexture(obstacle);
UnloadTexture(sky);

// CLoses the windoe when the game has ended
CloseWindow();
}