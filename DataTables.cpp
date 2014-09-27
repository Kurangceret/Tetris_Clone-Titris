#include "DataTables.h"
#include <iostream>
#include "Constant.h"

std::vector<ShapeData> initializeShapeData()
{
	std::vector<ShapeData> data(PlayerBlock::TypeCount);
	//any data allocated with spawnPoint means it is the core blocks
	const sf::Vector2f spawnPoint = sf::Vector2f(0.f, 0.f);

	//Below is the data for the shape to be formed
	//[] is the core block, to build the other 3 blocks
	//data allocated with spawnPoint variable is the core


	//------------------- START L SHAPE--------------//
	//=[=]=
	//=	
	data[PlayerBlock::L_shape].numShape = 4;
	data[PlayerBlock::L_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::L_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::L_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(-1.f, 1.f);
	data[PlayerBlock::L_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(1.f, 0.f);

	//==
	//[=]
	// =
	data[PlayerBlock::L_shape].shape[1].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::L_shape].shape[1].pos[Blocks::Block2] = sf::Vector2f(0.f, -1.f);
	data[PlayerBlock::L_shape].shape[1].pos[Blocks::Block3] = sf::Vector2f(-1.f, -1.f);
	data[PlayerBlock::L_shape].shape[1].pos[Blocks::Block4] = sf::Vector2f(0.f, 1.f);
	
	//	  =
	//=[=]=
	data[PlayerBlock::L_shape].shape[2].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::L_shape].shape[2].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::L_shape].shape[2].pos[Blocks::Block3] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::L_shape].shape[2].pos[Blocks::Block4] = sf::Vector2f(1.f, -1.f);

	//=
	//[=]
	//==
	data[PlayerBlock::L_shape].shape[3].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::L_shape].shape[3].pos[Blocks::Block2] = sf::Vector2f(0.f, -1.f);
	data[PlayerBlock::L_shape].shape[3].pos[Blocks::Block3] = sf::Vector2f(0.f, 1.f);
	data[PlayerBlock::L_shape].shape[3].pos[Blocks::Block4] = sf::Vector2f(1.f, 1.f);
	

	//-------------------- END L SHAPE---------------//


	//------------------- START T SHAPE--------------//

	//=[=]=
	//  =
	data[PlayerBlock::T_shape].numShape = 4;
	data[PlayerBlock::T_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::T_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::T_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::T_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(0.f, 1.f);

	//  =
	//=[=]
	//  =
	data[PlayerBlock::T_shape].shape[1].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::T_shape].shape[1].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::T_shape].shape[1].pos[Blocks::Block3] = sf::Vector2f(0.f, -1.f);
	data[PlayerBlock::T_shape].shape[1].pos[Blocks::Block4] = sf::Vector2f(0.f, 1.f);

	

	//  =
	//=[=]=
	data[PlayerBlock::T_shape].shape[2].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::T_shape].shape[2].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::T_shape].shape[2].pos[Blocks::Block3] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::T_shape].shape[2].pos[Blocks::Block4] = sf::Vector2f(0.f, -1.f);

	// =
	//[=]=
	// =
	data[PlayerBlock::T_shape].shape[3].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::T_shape].shape[3].pos[Blocks::Block2] = sf::Vector2f(0.f, -1.f);
	data[PlayerBlock::T_shape].shape[3].pos[Blocks::Block3] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::T_shape].shape[3].pos[Blocks::Block4] = sf::Vector2f(0.f, 1.f);



	//----------------END T SHAPE--------------//

	//---------------- START S SHAPE---------------//
	
	// [=]=
	//= =
	data[PlayerBlock::S_shape].numShape = 2;
	data[PlayerBlock::S_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::S_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::S_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(0.f, 1.f);
	data[PlayerBlock::S_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(-1.f, 1.f);
	
	// =
	//[=]=
	//   =
	data[PlayerBlock::S_shape].shape[1].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::S_shape].shape[1].pos[Blocks::Block2] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::S_shape].shape[1].pos[Blocks::Block3] = sf::Vector2f(1.f, 1.f);
	data[PlayerBlock::S_shape].shape[1].pos[Blocks::Block4] = sf::Vector2f(0.f, -1.f);

	//----------------END S SHAPE--------------//

	//----------------START O SHAPE---------------//

	//=[=]
	//= =
	data[PlayerBlock::O_shape].numShape = 1;
	data[PlayerBlock::O_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::O_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::O_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(-1.f, 1.f);
	data[PlayerBlock::O_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(0.f, 1.f);

	//----------------END O SHAPE--------------//


	//----------------START I SHAPE---------------//

	//= =[=]=
	data[PlayerBlock::I_shape].numShape = 2;
	data[PlayerBlock::I_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::I_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::I_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::I_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(-2.f, 0.f);

	// =
	//[=]
	// =
	// =
	data[PlayerBlock::I_shape].shape[1].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::I_shape].shape[1].pos[Blocks::Block2] = sf::Vector2f(0.f, 1.f);
	data[PlayerBlock::I_shape].shape[1].pos[Blocks::Block3] = sf::Vector2f(0.f, 2.f);
	data[PlayerBlock::I_shape].shape[1].pos[Blocks::Block4] = sf::Vector2f(0.f, -1.f);

	//----------------END I SHAPE--------------//


	//----------------START Z SHAPE---------------//

	//=[=]
	//  = =
	data[PlayerBlock::Z_shape].numShape = 2;
	data[PlayerBlock::Z_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::Z_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::Z_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(0.f, 1.f);
	data[PlayerBlock::Z_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(1.f, 1.f);

	
	//   =
	//[=]=
	// =

	data[PlayerBlock::Z_shape].shape[1].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::Z_shape].shape[1].pos[Blocks::Block2] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::Z_shape].shape[1].pos[Blocks::Block3] = sf::Vector2f(0.f, 1.f);
	data[PlayerBlock::Z_shape].shape[1].pos[Blocks::Block4] = sf::Vector2f(1.f, -1.f);


	//----------------END Z SHAPE--------------//

	//----------------START J SHAPE---------------//

	//=[=]=
	//    =
	data[PlayerBlock::J_shape].numShape = 4;
	data[PlayerBlock::J_shape].shape[0].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::J_shape].shape[0].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::J_shape].shape[0].pos[Blocks::Block3] = sf::Vector2f(1.f, 0.f);
	data[PlayerBlock::J_shape].shape[0].pos[Blocks::Block4] = sf::Vector2f(1.f, 1.f);


	//  =
	// [=]
	// ==

	data[PlayerBlock::J_shape].shape[1].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::J_shape].shape[1].pos[Blocks::Block2] = sf::Vector2f(0.f, 1.f);
	data[PlayerBlock::J_shape].shape[1].pos[Blocks::Block3] = sf::Vector2f(0.f, -1.f);
	data[PlayerBlock::J_shape].shape[1].pos[Blocks::Block4] = sf::Vector2f(-1.f, 1.f);
		

	//=
	//= [=] =
	data[PlayerBlock::J_shape].shape[2].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::J_shape].shape[2].pos[Blocks::Block2] = sf::Vector2f(-1.f, 0.f);
	data[PlayerBlock::J_shape].shape[2].pos[Blocks::Block3] = sf::Vector2f(-1.f, -1.f);
	data[PlayerBlock::J_shape].shape[2].pos[Blocks::Block4] = sf::Vector2f(1.f, 0.f);

	// = =
	//[=]
	// =
	data[PlayerBlock::J_shape].shape[3].pos[Blocks::Block1] = spawnPoint;
	data[PlayerBlock::J_shape].shape[3].pos[Blocks::Block2] = sf::Vector2f(0.f, -1.f);
	data[PlayerBlock::J_shape].shape[3].pos[Blocks::Block3] = sf::Vector2f(1.f, -1.f);
	data[PlayerBlock::J_shape].shape[3].pos[Blocks::Block4] = sf::Vector2f(0.f, 1.f);

	

	//----------------END J SHAPE--------------//

	return data;
}