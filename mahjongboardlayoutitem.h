#ifndef MAHJONGBOARDLAYOUTITEM_H
#define MAHJONGBOARDLAYOUTITEM_H

class MahjongTile;

class MahjongBoardLayoutItem
{
public:
    MahjongBoardLayoutItem(int xValue, int yValue, int dValue);

    int x() { return m_x; }
    int y() { return m_y; }
    int d() { return m_d; }
    MahjongTile *tile() const { return m_tile; }

    void setTile(MahjongTile *tile);


private:
    int m_x;
    int m_y;
    int m_d;
    MahjongTile *m_tile;
};

#endif // MAHJONGBOARDLAYOUTITEM_H
