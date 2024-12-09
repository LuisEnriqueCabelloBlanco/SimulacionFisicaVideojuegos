#include "MainScene.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
MainScene::MainScene()
{
	//addForce(new GravityGenerator(this));
	addForce(new WindGenerator(this, Vector3(0), 1, 0));


}

MainScene::~MainScene()
{

}
