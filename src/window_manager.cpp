#include <QtCompositor/QWaylandCompositor>
#include <QtCompositor/QWaylandSurface>
#include <QtCompositor/QWaylandShellSurface>
#include <QtCompositor/QWaylandInputDevice>
#include <QtCompositor/QWaylandXdgShellV5>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>

class MyCompositor : public QWaylandCompositor
{
public:
    MyCompositor(QWindow *window)
        : QWaylandCompositor(window)
    {
        // Create the input device
        m_inputDevice = new QWaylandInputDevice(this);

        // Connect signals for input events
        connect(m_inputDevice, &QWaylandInputDevice::mousePressEvent, this, &MyCompositor::handleMousePressEvent);
        connect(m_inputDevice, &QWaylandInputDevice::mouseMoveEvent, this, &MyCompositor::handleMouseMoveEvent);
        connect(m_inputDevice, &QWaylandInputDevice::mouseReleaseEvent, this, &MyCompositor::handleMouseReleaseEvent);
        connect(m_inputDevice, &QWaylandInputDevice::keyPressEvent, this, &MyCompositor::handleKeyPressEvent);
        connect(m_inputDevice, &QWaylandInputDevice::keyReleaseEvent, this, &MyCompositor::handleKeyReleaseEvent);

        // Create the xdg shell
        m_xdgShell = new QWaylandXdgShellV5(this);

        // Connect signals for xdg shell events
        connect(m_xdgShell, &QWaylandXdgShellV5::surfaceCreated, this, &MyCompositor::handleXdgSurfaceCreated);
    }

protected:
    QWaylandSurface *createSurface(wl_client *client, uint32_t id) override
    {
        Q_UNUSED(client);
        Q_UNUSED(id);

        // Create a new surface
        QWaylandSurface *surface = new QWaylandSurface(this);

        // Return the new surface
        return surface;
    }

    QWaylandShellSurface *createShellSurface(QWaylandSurface *surface) override
    {
        // Create a new shell surface for the given surface
        QWaylandShellSurface *shellSurface = new QWaylandShellSurface(surface);

        // Return the new shell surface
        return shellSurface;
    }

    QWaylandShellSurface *createXdgShellSurface(QWaylandSurface *surface) override
    {
        // Create a new xdg shell surface for the given surface
        QWaylandShellSurface *shellSurface = new QWaylandShellSurface(surface);

        // Return the new shell surface
        return shellSurface;
    }

private:
    QWaylandInputDevice *m_inputDevice;
    QWaylandXdgShellV5 *m_xdgShell;
    QMap<QWaylandSurface*, QPoint> m_positions;
    QMap<QWaylandSurface*, QPoint> m_dragStarts;

    void handleMousePressEvent(QWaylandInputDevice *device, uint32_t time, Qt::MouseButton button, const QPointF &localPos)
    {
        Q_UNUSED(time);

        // Find the topmost surface at the given position
        QWaylandSurface *surface = surfaceAt(localPos.toPoint());

        // If no surface was found, return
        if (!surface)
            return;

        // Save the drag start position
        m_dragStarts.insert(surface, localPos.toPoint());

        // Send the focus event to the surface
        surface->sendMousePressEvent(device, button, localPos.toPoint());
    }

    void handleMouseMoveEvent(QWaylandInputDevice *device, uint32_t time, const QPointF &localPos)
    {
        Q_UNUSED(time);

        // Find the topmost surface at the given position
        QWaylandSurface *surface = surfaceAt(localPos.toPoint());

        // If no surface was found, return
        if (!surface)
            return;

        // Calculate the drag delta
        QPoint delta = localPos.toPoint() - m_dragStarts.value(surface);

        // Move the surface by the drag delta
        QPoint position = m_positions.value(surface) + delta;
        m_positions.insert(surface, position);

        // Send the motion event to the surface
        surface->sendMouseMoveEvent(device, localPos.toPoint());
    }

    void handleMouseReleaseEvent(QWaylandInputDevice *device, uint32_t time, Qt::MouseButton button, const QPointF &localPos)
    {
        Q_UNUSED(time);

        // Find the topmost surface at the given position
        QWaylandSurface *surface = surfaceAt(localPos.toPoint());

        // If no surface was found, return
        if (!surface)
            return;

        //```
