// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#ifndef TREE_VISUALIZER_H
#define TREE_VISUALIZER_H

#endif // TREE_VISUALIZER_H

#pragma once
#include "tree_classes.hpp"
#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <sstream>

#define DEF_WINDOW_SIZE 1300, 800
#define DEF_X 300
#define DEF_Y 50
#define DEF_RADIUS 30
#define DEF_OFFSET_X 200
#define DEF_OFFSET_Y DEF_RADIUS * 4
#define DEF_FONT "Arial", DEF_RADIUS / 3
#define DEF_LINE_WIDTH 5
#define LINE_ZVALUE 0
#define ELLIPSE_ZVALUE 1
#define TEXT_ZVALUE 2

template <typename T>
class TreeVisualizer : public QMainWindow {
  public:
  TreeVisualizer(QWidget *parent = nullptr, Tree<T> *tree = nullptr) : QMainWindow(parent) {
    resize(DEF_WINDOW_SIZE);
    QGraphicsView *view = new QGraphicsView(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setScene(scene);
    setCentralWidget(view);
    QGraphicsEllipseItem *rootItem = addNodeToScene(scene, tree->getRoot(), DEF_X, DEF_Y, DEF_RADIUS);
    int offSetX = DEF_RADIUS * tree->getNodes().size();
    addNodeToSceneRecursive(scene, rootItem, tree->getRoot(), DEF_X, DEF_Y, offSetX, DEF_RADIUS);
  }

  private:
  QGraphicsEllipseItem *addNodeToScene(QGraphicsScene *scene, const Node<T> *node, int x, int y, int radius) {
    /* Turn Node into a circle */
    QGraphicsEllipseItem *circle = scene->addEllipse(x - radius, y - radius, 2 * radius, 2 * radius, QPen(), QBrush(Qt::gray));
    circle->setZValue(ELLIPSE_ZVALUE);

    /* Insert text in Node */
    std::stringstream tmp = std::stringstream();
    tmp << node->getValue();
    std::string s = tmp.str();
    QGraphicsTextItem *text = scene->addText(QString::fromStdString(s));
    text->setFont(QFont(DEF_FONT));
    text->setZValue(TEXT_ZVALUE);
    text->setDefaultTextColor(Qt::black); // Set text color to white for better visibility
    text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);

    return circle;
  }

  void addNodeToSceneRecursive(QGraphicsScene *scene, QGraphicsEllipseItem *parentItem, const Node<T> *parent,
                               int parentX, int parentY, int offsetX, int radius) {
    auto child_num = parent->children.size();
    if (offsetX > 3000) {
      offsetX = 3000;
    }
    if (offsetX < radius * 2 * child_num) {
      offsetX = radius * 2 * child_num;
    }
    else {
      offsetX -= radius * 2;
    }
    int childY = parentY + DEF_OFFSET_Y;
    int childX;
    if (child_num > 0) {
      childX = parentX - ((offsetX / 2) * (child_num - 1));
    }

    for (unsigned i = 0; i < child_num; ++i) {
      Node<T> *child = parent->children[i];
      QGraphicsEllipseItem *childItem = addNodeToScene(scene, child, childX, childY, radius);

      QGraphicsLineItem *lineItem = scene->addLine(parentItem->rect().center().x(),
                                                   parentItem->rect().center().y() + radius, childItem->rect().center().x(),
                                                   childItem->rect().center().y() - radius);
      QPen pen(Qt::black);
      pen.setWidth(DEF_LINE_WIDTH);
      pen.setCapStyle(Qt::RoundCap);
      pen.setJoinStyle(Qt::RoundJoin);
      lineItem->setPen(pen);
      lineItem->setZValue(LINE_ZVALUE);

      int new_offsetX;
      new_offsetX = std::max(radius * 2 * (child_num), offsetX / (child_num)-2 * radius);

      addNodeToSceneRecursive(scene, childItem, child, childX, childY, new_offsetX, radius);
      childX += offsetX;
    }
  }
};

