#include "Map_Tile.h"

void TileMap::clear()
{

	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				for (size_t k = 0; k < this->map[x][y][z].size(); k++)
				{
					delete this->map[x][y][z][k];
					this->map[x][y][z][k] = NULL;
				}
				this->map[x][y][z].clear();
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
	std::cout << this->map.size();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{

	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	
	this->maxSizeWorldGrid = sf::Vector2u(width, height);
	this->maxSizeWorldF = sf::Vector2f(static_cast<float>(width) * gridSize, static_cast<float>(height) * gridSize);
	this->layers = 1;
	this->textureFile = texture_file;


	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
	this->actualLayer = 0;


	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<std::vector<Tile*> >>());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		throw "ERROR TILE TEXTURE NOT LOADED";


	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}


const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rec, const bool collision, const short type)
{
	
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
	
			this->map[x][y][z].push_back(new Tile(x , y , this->gridSizeF, this->tileSheet, tex_rec, collision, type));
		
	}
}


void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (not this->map[x][y][z].empty())
		{
			delete this->map[x][y][z][this->map[x][y][z].size()-1];
			this->map[x][y][z].pop_back();

		}
	}
}
void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text-file.
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texture file
	All tiles:
	gridPos x y layer
	Texture rect x y
	collision
	type
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString()
								<< " "; //MAKE SURE THIS LAST SPACE IS NOT SAVED!!!!
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back(
				new Tile(
					x, y,
					this->gridSizeF,
					this->tileSheet,
					sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
					collision,
					type
				)
			);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}


void TileMap::updateRenderCollisionRange(Entity* entity)
{
	this->actualLayer = 0;
	this->fromX = entity->getGridPosition(this->gridSizeU).x-1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;


	this->toX = entity->getGridPosition(this->gridSizeU).x + 4;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeU).y-1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;


	this->toY = entity->getGridPosition(this->gridSizeU).y + 4;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;


}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	bool player = false;
	if (Player* p1 = dynamic_cast<Player*>(entity))
		player = true;

	if (entity->getPosition().x  < 0.f)
	{
		entity->setPos(sf::Vector2f(0.f, entity->getPosition().y));
		entity->stopVelocityX();
		if (not player)
			entity->changeHeading();

	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width  > this->maxSizeWorldF.x)
	{
	entity->stopVelocityX();
	entity->setPos(sf::Vector2f(this->maxSizeWorldF.x - entity->getGlobalBounds().width  , entity->getPosition().y));
	if (not player)
		entity->changeHeading();
	}


	if (entity->getPosition().y  < 0.f)
	{	
		
		entity->setPos(sf::Vector2f(entity->getPosition().x, 0.0f));	
		entity->stopVelocityY();
		if (not player)
			entity->changeHeading();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{	
		
		entity->setPos(sf::Vector2f(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height ));	
		entity->stopVelocityY();
		if (not player)
			entity->changeHeading();
			
	}


	this->updateRenderCollisionRange(entity);






	for (size_t x = fromX; x < this->toX; x++)
	{
		for (size_t y = fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->actualLayer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->actualLayer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (this->map[x][y][this->actualLayer][k]->getCollision() &&
					this->map[x][y][this->actualLayer][k]->intersects(nextPositionBounds)
					)
				{
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPos(sf::Vector2f(playerBounds.left, wallBounds.top - playerBounds.height));
						if (not player)
							entity->changeHeading();
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPos(sf::Vector2f(playerBounds.left, wallBounds.top + wallBounds.height));
						if (not player)
							entity->changeHeading();

					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();

						entity->setPos(sf::Vector2f(wallBounds.left - playerBounds.width, playerBounds.top));
						if (not player)
							entity->changeHeading();
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();

						entity->setPos(sf::Vector2f(wallBounds.left + wallBounds.width, playerBounds.top));
						if (not player)
							entity->changeHeading();
					}
				}
			}
		}

	}
}




void TileMap::update(const float& dt)
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	if (entity)
	{
		for (size_t x = fromX; x < this->toX; x++)
		{
			for (size_t y = fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->actualLayer].size(); k++)
				{
					this->map[x][y][this->actualLayer][k]->render(target);
					if (this->map[x][y][this->actualLayer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->actualLayer][k]->getPosition());
						//target.draw(this->collisionBox);
					}
				}
			}

		}
	}
	else
	{

		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto& z : y)
				{
					for (auto* k : z)

					{
						
							k->render(target);
							if (k->getCollision())
							{
								this->collisionBox.setPosition(k->getPosition());
							//	target.draw(this->collisionBox);
							}
						
					}


				}

				
			}
		}
	}
}