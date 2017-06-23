#pragma once

#include <QtCore/QUuid>
#include <QtWidgets/QGraphicsObject>

#include "Connection.hpp"
#include "NodeState.hpp"
#include "NodeGeometry.hpp"

class QGraphicsProxyWidget;

namespace QtNodes
{

class NodeIndex;
class FlowScene;

/// Class reacts on GUI events, mouse clicks and
/// forwards painting operation.
class NodeGraphicsObject : public QGraphicsObject
{
  Q_OBJECT

public:
  NodeGraphicsObject(FlowScene& scene, const NodeIndex& index);

  virtual
  ~NodeGraphicsObject();

  NodeIndex
  index() const;
  
  NodeGeometry&
  geometry();
  
  NodeGeometry const&
  geometry() const;
  
  NodeState&
  nodeState();
  
  NodeState const&
  nodeState() const;

  QRectF
  boundingRect() const override;

  void
  setGeometryChanged();

  /// Visits all attached connections and corrects
  /// their corresponding end points.
  void
  moveConnections() const;

  
  void reactToPossibleConnection(PortType,
                                 NodeDataType,
                                 QPointF const & scenePoint);

  void
  resetReactionToConnection();

  
  enum { Type = UserType + 1 };

  int
  type() const override { return Type; }

  void
  lock(bool locked);

protected:
  void
  paint(QPainter*                       painter,
        QStyleOptionGraphicsItem const* option,
        QWidget*                        widget = 0) const override;

  QVariant
  itemChange(GraphicsItemChange change, const QVariant &value) override;

  void
  mousePressEvent(QGraphicsSceneMouseEvent* event) override;

  void
  mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

  void
  mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  void
  hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

  void
  hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

  void
  hoverMoveEvent(QGraphicsSceneHoverEvent *) override;

  void
  mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
  void
  embedQWidget();

private:

  FlowScene& _scene;
  
  const NodeIndex& _nodeIndex;
  
  NodeGeometry _geometry;
  
  NodeState _state;
  
  bool _locked;

  // either nullptr or owned by parent QGraphicsItem
  QGraphicsProxyWidget * _proxyWidget;

};
}
