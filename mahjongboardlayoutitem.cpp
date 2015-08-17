#include "mahjongboardlayoutitem.h"

#include "mahjongtileentity.h"

MahjongBoardLayoutItem::MahjongBoardLayoutItem(int xValue, int yValue, int dValue)
    : m_x(xValue)
    , m_y(yValue)
    , m_d(dValue)
    , m_tile(0)
{

}

void MahjongBoardLayoutItem::setTile(MahjongTileEntity *tile)
{
    m_tile = tile;
}

