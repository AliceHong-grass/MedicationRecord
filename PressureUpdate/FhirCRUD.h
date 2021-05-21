#pragma once
#ifndef FHIRCRUD_H
#define FHIRCRUD_H

#include <QObject>

#include <QtCore>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class FhirCRUD : public QObject
{
	Q_OBJECT
		QNetworkAccessManager *manager;
private slots:
	QString replyFinished(QNetworkReply *);
public:
	QString Get(QString url, QString resource, QString id);
	QString Post(QString url, QString resource, QByteArray json);
	QString Put(QString url, QString resource, QString id, QByteArray json);
	QString Delete(QString url, QString resource, QString id);
	QString Search(QString url, QString resource, QString condition);
};



#endif // NET_H