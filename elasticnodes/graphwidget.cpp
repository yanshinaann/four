#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 600, 600);
    setScene(scene);
    s = scene;
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(200, 200);
    setWindowTitle(tr("Graph"));

//    Node *node1 = new Node(this, 0);
//    Node *node2 = new Node(this, 1);
//    scene->addItem(node1);
//    scene->addItem(node2);
//    scene->addItem(new Edge(node1, node2));
//    setGraph();
//    scene->addItem(new Node(this, "0"));

//    node1->setPos(0, 0);

//    shuffle();
}

void GraphWidget::setGraph()
{
//    QRectF f = sceneRect();
//    scene()->clear();
}

void GraphWidget::setGraph(const QVector<QVector<int> > &graph)
{
    nodes.clear();
    this->scene()->clear();

    for (int index = 0; index < graph.size();index++) {
        Node *node = new Node(this, index);
        nodes.push_back(node);
        this->scene()->addItem(node);
    }

    int number = 0;
    foreach (QVector<int> nodeEdges, graph) {
        if (nodeEdges.length() > 0) {
            foreach (int nodeId, nodeEdges) {
                if (nodeId > number)
                    this->scene()->addItem(new Edge(nodes[number], nodes[nodeId]));
            }
        }
        number++;
    }

    shuffle();
}



void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif


void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
   Q_UNUSED(rect);

    // Shadow
   // QRectF sceneRect = this->sceneRect();
    //QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    //QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    //if (rightShadow.intersects(rect) || rightShadow.contains(rect))
     //   painter->fillRect(rightShadow, Qt::darkGray);
   // if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
    //    painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
   // QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
   // gradient.setColorAt(0, Qt::white);
   // gradient.setColorAt(1, Qt::lightGray);
    //painter->fillRect(rect.intersected(sceneRect), gradient);
    //painter->setBrush(Qt::NoBrush);
   // painter->drawRect(sceneRect);

    // Text
   // QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                   // sceneRect.width() - 4, sceneRect.height() - 4);
   // QString message(tr("Click and drag the nodes around, and zoom with the mouse "
     //                  "wheel or the '+' and '-' keys"));

   // QFont font = painter->font();
   // font.setBold(true);
  //  font.setPointSize(14);
   // painter->setFont(font);
    //painter->setPen(Qt::lightGray);
   // painter->drawText(textRect.translated(2, 2), message);
   // painter->setPen(Qt::black);
    //painter->drawText(textRect, message);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::updateColor(const QVector<QVector<int>> &nodesGroup)
{
    QRandomGenerator rand;
    rand.seed(2);
    for (int index = 0; index < nodesGroup.size(); index++){
        int colorR = rand.bounded(256);
        int colorG = rand.bounded(256);
        int colorB = rand.bounded(256);
        for (int indexNode = 0; indexNode < nodesGroup[index].size(); indexNode++){
            nodes[nodesGroup[index][indexNode]]->setColor(QColor(colorR, colorG, colorB));
        }
    }
}
