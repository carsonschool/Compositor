#include <QApplication>
#include <QWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsDropShadowEffect>

class CustomCompositor : public QApplication
{
    Q_OBJECT

public:
    CustomCompositor(int &argc, char **argv)
        : QApplication(argc, argv)
    {
        initializeGraphicsScene();
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::GraphicsSceneMousePress) {
            auto mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            m_lastMousePos = mouseEvent->scenePos();
            return true;
        } else if (event->type() == QEvent::GraphicsSceneMouseMove) {
            auto mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            QPointF delta = mouseEvent->scenePos() - m_lastMousePos;
            m_windowItem->moveBy(delta.x(), delta.y());
            m_lastMousePos = mouseEvent->scenePos();
            return true;
        }
        return QApplication::eventFilter(obj, event);
    }

    void initializeGraphicsScene()
    {
        m_scene = new QGraphicsScene();
        m_view = new QGraphicsView(m_scene);

        m_windowItem = new QGraphicsRectItem(0, 0, 200, 150);
        m_windowItem->setBrush(QColor(200, 200, 255));
        m_windowItem->setFlag(QGraphicsItem::ItemIsMovable);
        m_scene->addItem(m_windowItem);

        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
        effect->setBlurRadius(10);
        effect->setOffset(5, 5);
        m_windowItem->setGraphicsEffect(effect);

        m_view->setRenderHint(QPainter::Antialiasing);
        m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        m_view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
        m_view->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
        m_view->setWindowTitle("Desktop Environment Compositor");
        m_view->resize(800, 600);
        m_view->setSceneRect(0, 0, 800, 600);

        m_scene->installEventFilter(this);
    }

    int exec()
    {
        m_view->show();
        return QApplication::exec();
    }

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    QGraphicsRectItem *m_windowItem;
    QPointF m_lastMousePos;
};

int main(int argc, char **argv)
{
    CustomCompositor compositor(argc, argv);
    return compositor.exec();
}
