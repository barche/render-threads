#include "fborender.h"

#include <QOpenGLFramebufferObject>
#include <QSGNode>
#include <QSGSimpleTextureNode>

class FBORender::Renderer : public QQuickFramebufferObject::Renderer
{
public:
	Renderer()
	{
	}

	void render()
	{
		// Must call render function on the main thread
		qWarning() << "start render call";
		QMetaObject::invokeMethod(m_vp, "render", Qt::BlockingQueuedConnection);
		qWarning() << "finished render call";
	}

	void synchronize(QQuickFramebufferObject *item)
	{
		m_vp = dynamic_cast<FBORender*>(item);
	}

	QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
	{
		QOpenGLFramebufferObjectFormat format;
		format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
		format.setSamples(4);
		return new QOpenGLFramebufferObject(size, format);
	}
private:
	FBORender* m_vp;
};

FBORender::FBORender(QQuickItem *parent) : QQuickFramebufferObject(parent)
{
	QObject::connect(this, &FBORender::renderFunctionChanged, this, &FBORender::update);
	QObject::connect(this, &FBORender::renderArgumentsChanged, this, &FBORender::update);
}

void FBORender::render()
{
	qWarning() << "rendering";
}

QQuickFramebufferObject::Renderer* FBORender::createRenderer() const
{
	return new Renderer();
}
