#ifndef GRAPH_H
#define GRAPH_H

#include "QVector"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


class Graph
{
public:
    explicit Graph(const QVector<QVector<int>> &nodes);
    explicit Graph(const QString &name);
    explicit Graph() = default;

    QVector<QVector<int>> getGraph();

    QVector<QVector<int>> searchComponents() const;

    void save(const QString &name) const;
    void load(const QString &name);

    static QJsonDocument convertGraphToJsonDoc(const QVector<QVector<int>> &graph);
    static QVector<QVector<int>> convertJsonDocToGraph(const QJsonDocument &json);

private:
    QVector<QVector<int>> nodes;

    void findNodes(int n, QVector<int> *result, QVector<int> *used) const;
};

#endif // GRAPH_H
