#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "fborender.h"

int main(int argc, char *argv[])
{
	qmlRegisterType<FBORender>("fborender", 1, 0, "FBORender");

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
