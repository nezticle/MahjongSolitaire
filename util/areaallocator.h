#ifndef AREAALLOCATOR_H
#define AREAALLOCATOR_H

#include <QtCore/QSize>

class QRect;
class QPoint;
struct AreaAllocatorNode;

class AreaAllocator
{
public:
    AreaAllocator(const QSize &size);
    ~AreaAllocator();

    QRect allocate(const QSize &size);
    bool deallocate(const QRect &rect);
    bool isEmpty() const { return m_root == 0; }
    QSize size() const { return m_size; }
private:
    bool allocateInNode(const QSize &size, QPoint &result, const QRect &currentRect, AreaAllocatorNode *node);
    bool deallocateInNode(const QPoint &pos, AreaAllocatorNode *node);
    void mergeNodeWithNeighbors(AreaAllocatorNode *node);

    AreaAllocatorNode *m_root;
    QSize m_size;
};

#endif // AREAALLOCATOR_H
