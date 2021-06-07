#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
//    GraphWidget(const QVector<QVector<int> > &graph);

    void setGraph(const QVector<QVector<int> > &graph);
    void setGraph();
    void itemMoved();

    void updateColor(const QVector<QVector<int>> &nodesGroup);
public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    QGraphicsScene *s;

    int timerId;

    QVector<Node*> nodes;
};

#endif // GRAPHWIDGET_H
