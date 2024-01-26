#include "blocks.h"

std::vector<Box> Blocks::initBlocks(float m_block_size) {
	std::vector<Box> m_blocks;

	m_blocks.push_back(Box(-7 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-6 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-5 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-4 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-2 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-1 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(0 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(1 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(2 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(5 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(5 * m_block_size, 13 * m_block_size, m_block_size, m_block_size));


	m_blocks.push_back(Box(-8 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 14 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 13 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 12 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 11 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 10 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 9 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 8 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 7 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, 0 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-8 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));


	m_blocks.push_back(Box(8 * m_block_size, 15 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 14 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 13 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 12 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 11 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 10 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 9 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 8 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 7 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 4 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 2 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, 0 * m_block_size, m_block_size, m_block_size));


	m_blocks.push_back(Box(-7 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-6 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-5 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-4 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-3 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-2 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(-1 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(0 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(1 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(2 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(3 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(4 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(5 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(6 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(7 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));
	m_blocks.push_back(Box(8 * m_block_size, -1 * m_block_size, m_block_size, m_block_size));

	return m_blocks;
}
