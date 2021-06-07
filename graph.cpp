#include "graph.h"

Graph::Graph(const QVector<QVector<int> > &nodes)
    :nodes(nodes)
{

}

Graph::Graph(const QString &name)
{
    load(name);
}

QVector<QVector<int>> Graph::getGraph()
{
    return nodes;
}

QVector<QVector<int>> Graph::searchComponents() const
{
    QVector<QVector<int>> nodesGroup;

    QVector<int> *used = new QVector<int>();
    for (int number = 0; number < nodes.size() | used->size() < nodes.size(); number++) {
        if (used->contains(number))
            continue;
        QVector<int> *result = new QVector<int>();
        findNodes(number, result, used);
        nodesGroup.push_back(*result);
        delete result;
    }
    delete used;
    return nodesGroup;
}

void Graph::findNodes(int n, QVector<int> *result, QVector<int> *used) const
{
    used->push_back(n);
    result->push_back(n);
    foreach (int element, nodes[n]) {
        if (!used->contains(element))
            findNodes(element, result, used);
    }
}

void Graph::save(const QString &name) const
{
    QFile file(name);
    file.open(QFile::WriteOnly);
    QJsonDocument doc = convertGraphToJsonDoc(searchComponents());
    file.write(doc.toJson());
    file.close();
}

void Graph::load(const QString &name)
{
    QFile file(name);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument().fromJson(file.readAll());
    file.close();
    nodes = convertJsonDocToGraph(doc);
}

QJsonDocument Graph::convertGraphToJsonDoc(const QVector<QVector<int> > &graph)
{
    QJsonObject obj;

    for (int indNode = 0; indNode < graph.size(); indNode++){
        QJsonArray array;
        for (int indIdentityNode = 0; indIdentityNode < graph[indNode].size(); indIdentityNode++)
            array.push_back(graph[indNode][indIdentityNode]);
        obj.insert("Group "+QString::number(indNode), array);
    }

    return QJsonDocument(obj);
}

QVector<QVector<int> > Graph::convertJsonDocToGraph(const QJsonDocument &json)
{
    QVector<QVector<int>> nodes;
    QJsonObject obj = json.object();

    for (int indNode = 0; indNode < obj.size(); indNode++){
        QJsonArray arrayJson = obj.value(QString::number(indNode)).toArray();
        QVector<int> array;
        for (int indIdentityNode = 0; indIdentityNode < arrayJson.size(); indIdentityNode++)
            array.push_back(arrayJson[indIdentityNode].toInt());
        nodes.push_back(array);
    }
    if (obj.empty())
        qDebug("exception");

    return nodes;
}
