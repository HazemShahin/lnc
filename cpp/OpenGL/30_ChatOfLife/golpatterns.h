#pragma once
#include <vector>
#include <string>


namespace GOL {

	struct Pattern {
		std::string name;
		std::vector< std::vector<uint8_t> > pattern;
	};



	//Still lifes

	Pattern block{ "Block",
		{	{1,1},
			{1,1}
		}
	};

	Pattern beehive{ "Bee-hive",
		{	{0,1,1,0},
			{1,0,0,1},
			{0,1,1,0}
		}
	};

	Pattern loaf{ "Loaf",
		{	{0,1,1,0},
			{1,0,0,1},
			{0,1,0,1},
			{0,0,1,0}
		}
	};

	Pattern boat{ "Boat",
		{	{1,1,0},
			{1,0,1},
			{0,1,0}
		}
	};

	Pattern tub{ "Tub",
		{	{0,1,0},
			{1,0,1},
			{0,1,0}
		}
	};



//Oscillators
	Pattern blinker{ "Blinker",
		{	{1,1,1}
		}
	};

	Pattern toad{ "Toad",
		{	{0,1,1,1},
			{1,1,1,0}
		}
	};

	Pattern beacon{ "Beacon",
		{	{1,1,0,0},
			{1,1,0,0},
			{0,0,1,1},
			{0,0,1,1}
		}
	};

	Pattern pulsar{ "Pulsar",
		{	{0,0,1,1,1,0,0,0,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,1,0,1,0,0,0,0,1},
			{1,0,0,0,0,1,0,1,0,0,0,0,1},
			{1,0,0,0,0,1,0,1,0,0,0,0,1},
			{0,0,1,1,1,0,0,0,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,0,0,0,1,1,1,0,0},
			{1,0,0,0,0,1,0,1,0,0,0,0,1},
			{1,0,0,0,0,1,0,1,0,0,0,0,1},
			{1,0,0,0,0,1,0,1,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,0,0,0,1,1,1,0,0}
		}
	};
	Pattern pentadecathlon{ "Penta-decathlon",
		{	{0,0,1,0,0,0,0,1,0,0},
			{1,1,0,1,1,1,1,0,1,1},
			{0,0,1,0,0,0,0,1,0,0}
		}
	};

//Spaceships

	Pattern glider{ "Glider",
		{	{1,0,0},
			{0,1,1},
			{1,1,0}
		}  
	};

	Pattern lwss{ "Light-weight spaceship",
		{	{1,0,0,1,0},
			{0,0,0,0,1},
			{1,0,0,0,1},
			{0,1,1,1,1}
		}
	};

	Pattern mwss{ "Middle-weight spaceship",
		{	{0,0,1,0,0,0},
			{1,0,0,0,1,0},
			{0,0,0,0,0,1},
			{1,0,0,0,0,1},
			{0,1,1,1,1,1}
		}
	};

	Pattern hwss{ "Heavy-weight spaceship",
		{	{0,0,1,1,0,0,0},
			{1,0,0,0,0,1,0},
			{0,0,0,0,0,0,1},
			{1,0,0,0,0,0,1},
			{0,1,1,1,1,1,1}
		}
	};

//miscellaneous

	Pattern acorn{ "Acorn",
		{	{0,1,0,0,0,0,0},
			{0,0,0,1,0,0,0},
			{1,1,0,0,1,1,1}
		}
	};
}
