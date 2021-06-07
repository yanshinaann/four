#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
}

//void GraphWidget::itemMoved()
//{
//    if (!timerId)
//        timerId = startTimer(1000 / 25);
//}

//void GraphWidget::addNode(Node *node)
//{
////    scene()->addItem(node);
//}

//void GraphWidget::addEdge(Edge *edge)
//{
////    scene()->addItem(edge);
//}

//void GraphWidget::timerEvent(QTimerEvent *event)
//{
//    Q_UNUSED(event);

//    QList<Node *> nodes;
//    foreach (QGraphicsItem *item, scene()->items()) {
//        if (Node *node = qgraphicsitem_cast<Node *>(item))
//            nodes << node;
//    }

//    foreach (Node *node, nodes)
//        node->calculateForces();

//    bool itemsMoved = false;
//    foreach (Node *node, nodes) {
//        if (node->advancePosition())
//            itemsMoved = true;
//    }

//    if (!itemsMoved) {
//        killTimer(timerId);
//        timerId = 0;
//    }
//}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
